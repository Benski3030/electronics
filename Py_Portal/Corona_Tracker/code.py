# covid 19 state and national tracker
# https://learn.adafruit.com/pyportal-nasa-image-of-the-day-viewer/code-pyportal-nasa-image-viewer
import sys
import time
import board
from adafruit_pyportal import PyPortal
import adafruit_requests as requests
import adafruit_esp32spi.adafruit_esp32spi_socket as socket
from adafruit_esp32spi import adafruit_esp32spi

cwd = ("/"+__file__).rsplit('/', 1)[0] # the current working directory (where this file is)
sys.path.append(cwd)

# Set up where we'll be fetching data from
DATA_SOURCE = 'http://192.168.1.107:5000/'
DATA_LOCATION1 = ['TN_tlt_case']
DATA_LOCATION2 = ['TN_tlt_deaths']
DATA_LOCATION3 = ['new_cases']
DATA_LOCATION4 = ['case_delta']
DATA_LOCATION5 = ['death_delta']
DATA_LOCATION6 = ['per_pop']
DATA_LOCATION7 = ['trend_st']
DATA_LOCATION8 = ['last_update:']
CAPTION = 'Tennessee'

# Initialize the pyportal object and let us know what data to fetch and where
# to display it
pyportal = PyPortal(url=DATA_SOURCE,
                    json_path=(DATA_LOCATION8, 
                               DATA_LOCATION1, 
                               DATA_LOCATION2,
                               DATA_LOCATION3,
                               DATA_LOCATION4,
                               DATA_LOCATION5,
                               DATA_LOCATION6,
                               DATA_LOCATION7),
                    default_bg='/icons/sarscov2.bmp',
                    text_font=cwd+"/fonts/Arial-12.bdf",
                    text_position=((100, 55), 
                                   (100, 71),
                                   (100, 87),
                                   (100, 102),
                                   (145, 120),
                                   (145, 135),
                                   (115, 153),
                                   (35, 190)),
                    text_color=(0xFFFFFF, 0xFFFFFF, 0xFFFFFF,0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF),
                    caption_text=(CAPTION),
                    caption_font=cwd+'/fonts/Arial-Bold-24.bdf',
                    caption_position=(25, 25),
                    caption_color=0xFFFFFF)

# Get wifi details and more from a secrets.py file
try:
    from secrets import secrets
except ImportError:
    print("WiFi secrets are kept in secrets.py, please add them there!")
    raise


# run covid tracker
localtile_refresh = None
weather_refresh = None

while True:
    # only query the online time once per day (and on first run)
    if (not localtile_refresh) or (time.monotonic() - localtile_refresh) > 86400:
        try:
            last_update, cases, deaths, case_delta, death_delta, pop_inf, record, trending = pyportal.fetch()
        except RuntimeError as e:
            print("Some error occured, retrying! -", e)

    time.sleep(5000)
