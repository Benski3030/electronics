from djitellopy import tello
import time

me = tello.Tello()
me.connect()
print(me.get_battery())

me.takeoff()

# Move using Distance
me.send_rc_control(0, 0, 5, 0)
time.sleep(0)
# Move using Speed
me.send_rc_control(0, 0, 0, -20)
time.sleep(1)
#me.send_rc_control(0, 0, 0, 0)
print('[INFO] run complete')
me.land()