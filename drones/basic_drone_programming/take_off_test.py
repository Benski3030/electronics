from djitellopy import tello
from time import sleep

# create tello object
me = tello.Tello()

# connect to drone
me.connect()

# display battery info
print(me.get_battery())

# take off the drone
me.takeoff()
me.send_rc_control(0, 25, 0, 0)

# make a loop
for i in range(-100, 101, 10):
    sleep(0.5)
    me.send_rc_control(0, 0, 0, i)

sleep(2)

# try a more advanced move - flip
me.flip_back()

me.send_rc_control(0, 0, 0, 0)

# land the drone
me.land()

print('[SUCCESS] take off test complete')