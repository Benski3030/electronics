import time
import board
import busio
import digitalio
from adafruit_esp32spi import adafruit_esp32spi_socket as socket
from adafruit_esp32spi import adafruit_esp32spi
import adafruit_requests as requests
from adafruit_pyportal import PyPortal
from adafruit_bitmap_font import bitmap_font
from adafruit_display_text.Label import Label

try:
    from secrets import secrets
except ImportError:
    print("""WiFi settings are kept in secrets.py, please add them there!
the secrets dictionary must contain 'ssid' and 'password' at a minimum""")
    raise

def timeConvert(miliTime, gmt_offset):
    '''help function for conversion from military time to civilian
    also includes GMT offset for CDT'''

    hours, minutes = miliTime.split(":")
    hours, minutes = int(hours), int(minutes)

    hours = hours + gmt_offset
    if hours > 24:
        hours = hours - 24

    setting = "AM"
    if hours > 12:
        setting = "PM"
        hours -= 12
    return str("%02d:%02d" + setting) % (hours, minutes)


# Label colors
LABEL_DAY_COLOR = 0xFFFFFF
LABEL_TIME_COLOR = 0x2a8eba

# the current working directory (where this file is)
cwd = ("/"+__file__).rsplit('/', 1)[0]

# un-comment to set background image
background = cwd+"/countdown_event.bmp"

# configure board and spi specifics
esp32_cs = digitalio.DigitalInOut(board.ESP_CS)
esp32_ready = digitalio.DigitalInOut(board.ESP_BUSY)
esp32_reset = digitalio.DigitalInOut(board.ESP_RESET)
spi = busio.SPI(board.SCK, board.MOSI, board.MISO)
esp = adafruit_esp32spi.ESP_SPIcontrol(spi, esp32_cs, esp32_ready, esp32_reset, debug=False)
requests.set_socket(socket, esp)

# configure fonts and splash screens
big_font = bitmap_font.load_font(cwd+"/fonts/Arial-12.bdf")
big_font.load_glyphs(b'0123456789') # pre-load glyphs for fast printing
syk_background = cwd+"/stryker_logo.bmp"
clock_background = cwd+"/stryker_offices.bmp"
# initialize pyportal

'''
something has changed... you now need three arguments for it to work
these include the esp and external_spi ones.
'''

pyportal = PyPortal(esp=esp,
                    external_spi=spi,
                    default_bg=clock_background, 
                    text_color=(0xFFFFFF))


# set clock positions for each location
kal_time = (40, 30)
mahwah_time = (200, 30)
sj_time = (40, 90)
vancouver_time = (200, 90)
freiburg_time = (40, 144)
amsterdam_time = (200, 144)
manchester_time = (40, 204)
dehli_time = (200, 204)
text_color = 0xFFFFFF

# configure text zones on the screen
text_areas = []
for pos in (kal_time, mahwah_time, sj_time, vancouver_time, freiburg_time, amsterdam_time, manchester_time, dehli_time):
    textarea = Label(big_font, max_glyphs=9)
    textarea.x = pos[0]
    textarea.y = pos[1]
    textarea.color = text_color
    pyportal.splash.append(textarea)
    text_areas.append(textarea)

# run the loop to fetch TN time and convert to offset for office local times
# not sure how DST will impact this... probably will.
refresh_time = None
while True:
    # only query the online time once per hour (and on first run)
    if (not refresh_time) or (time.monotonic() - refresh_time) > 60:
        try:
            print("Getting time from internet!")
            pyportal.get_local_time(secrets['timezone'])
            refresh_time = time.monotonic()
        except RuntimeError as e:
            print("Some error occured, retrying! -", e)
            continue

    # populate the time data
    now = time.localtime()
    text_areas[0].text = timeConvert(str('{}:{}').format(now.tm_hour, now.tm_min), 1)  # kalamazoo
    text_areas[1].text = timeConvert(str('{}:{}').format(now.tm_hour, now.tm_min), 1)  # mahwah
    text_areas[2].text = timeConvert(str('{}:{}').format(now.tm_hour, now.tm_min), -2)  # san jose
    text_areas[3].text = timeConvert(str('{}:{}').format(now.tm_hour, now.tm_min), -2)  # vancouver
    text_areas[4].text = timeConvert(str('{}:{}').format(now.tm_hour, now.tm_min), 7)  # freiburg
    text_areas[5].text = timeConvert(str('{}:{}').format(now.tm_hour, now.tm_min), 7)  # amsertdam
    text_areas[6].text = timeConvert(str('{}:{}').format(now.tm_hour, now.tm_min), 6)  # manchester
    text_areas[7].text = timeConvert(str('{}:{}').format(now.tm_hour, now.tm_min), 12)  # new dehli
 
    # update every 10 seconds
    time.sleep(60)
