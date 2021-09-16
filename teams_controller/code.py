import time
import board
import busio
from adafruit_hid.mouse import Mouse
from adafruit_neokey.neokey1x4 import NeoKey1x4
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode

# use STEMMA I2C bus on RP2040 QT Py
i2c_bus = busio.I2C(board.SCL1, board.SDA1)

# set up a dummy mouse button
mouse = Mouse(usb_hid.devices)

# last time we moved the mouse
LAST_MOVE_TIME = -1
# How long we want to wait for the new mouse movement
MOVE_OFF_DURATION = 0.25
MOVE_ON_DURATION = 0.25
# wether or not it's time to move
TO_MOVE = True

# Create a NeoKey object
neokey = NeoKey1x4(i2c_bus, addr=0x30)

#  create a keyboard object
keyboard = Keyboard(usb_hid.devices)

print("MS Teams Controller")

# states for key presses
key_0_state = False
key_1_state = False
key_2_state = False
key_3_state = False

num_pixels = [0,1,2,3]

for pxl in num_pixels:
    neokey.pixels[pxl] = 0x0
    time.sleep(0.25)
for pxl in num_pixels:
    neokey.pixels[pxl] = 0x00FF00
    time.sleep(0.25)
for pxl in num_pixels:
    neokey.pixels[pxl] = 0x0
    time.sleep(0.25)
for pxl in num_pixels:
    neokey.pixels[pxl] = 0x00B0FF
# run circuit loop
while True:
    # multitask the mouse movement
    # the sneakery, keep mouse moving
    now = time.monotonic()
    if not TO_MOVE:
        # Is it time to move the mouse?
        if now >= LAST_MOVE_TIME + MOVE_OFF_DURATION:
            mouse.move(x=0.5)
            TO_MOVE = True

            LAST_MOVE_TIME = now
    if TO_MOVE:
        # Is it time to NOT move the mouse?
        if now >= LAST_MOVE_TIME + MOVE_ON_DURATION:
            TO_MOVE = False
            LAST_MOVE_TIME = now

    #  if 1st neokey is pressed...
    if neokey[0] and not key_0_state:
        print("Button A State 1")
        # turn on NeoPixel.
        neokey.pixels[0] = 0xFF0000
        # raise hand
        keyboard.send(Keycode.ALT, Keycode.F4)
        # update key state
        time.sleep(0.25)
        key_0_state = True
    elif neokey[0] and key_0_state:
        print("Button A State 2")
        # turn on NeoPixel.
        neokey.pixels[0] = 0x00B0FF
        # raise hand
        keyboard.send(Keycode.ALT, Keycode.F4)
        # update key state
        time.sleep(0.25)
        key_0_state = False

    #  if 2nd neokey is pressed...
    if neokey[1] and not key_1_state:
        print("Button B State 1")
        # turn on NeoPixel.
        neokey.pixels[1] = 0xFF0000
        # raise hand
        keyboard.send(Keycode.CONTROL, Keycode.SHIFT, Keycode.B)
        # update key state
        time.sleep(0.25)
        key_1_state = True
    elif neokey[1] and key_1_state:
        print("Button B State 2")
        # turn on NeoPixel.
        neokey.pixels[1] = 0x00B0FF
        # raise hand
        keyboard.send(Keycode.CONTROL, Keycode.SHIFT, Keycode.B)
        # update key state
        time.sleep(0.25)
        key_1_state = False

     #  if 3rd neokey is pressed...
    if neokey[2] and not key_2_state:
        print("Button C State 1")
        # turn on NeoPixel.
        neokey.pixels[2] = 0xFF0000
        # raise hand
        keyboard.send(Keycode.CONTROL, Keycode.SHIFT, Keycode.O)
        # update key state
        time.sleep(0.25)
        key_2_state = True
    elif neokey[2] and key_2_state:
        print("Button C State 2")
        # turn on NeoPixel.
        neokey.pixels[2] = 0x00B0FF
        # raise hand
        keyboard.send(Keycode.CONTROL, Keycode.SHIFT, Keycode.O)
        # update key state
        time.sleep(0.25)
        key_2_state = False

    #  if 4th neokey is pressed...
    if neokey[3] and not key_3_state:
        print("Button D State 1")
        print(key_3_state)
        # turn on NeoPixel.
        neokey.pixels[3] = 0xFF0000
        # ABORT
        keyboard.send(Keycode.CONTROL, Keycode.SHIFT, Keycode.M)
        # update key state
        time.sleep(0.25)
        key_3_state = True
    elif neokey[3] and key_3_state:
        print("Button D State 2")
        print(key_3_state)
        # turn on NeoPixel.
        neokey.pixels[3] = 0x00B0FF
        # ABORT
        keyboard.send(Keycode.CONTROL, Keycode.SHIFT, Keycode.M)
        # update key state
        time.sleep(0.25)
        key_3_state = False
