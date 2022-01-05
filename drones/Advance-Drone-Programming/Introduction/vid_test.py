from djitellopy import tello
import cv2

drone = tello.Tello()
drone.connect()
print('[SUCCESS] connected to drone')

drone.streamon()
print('[SUCCESS] steam enabled')

cv2.namedWindow('drone')
c = drone.get_frame_read()

while True:
    f = c.frame
    f = cv2.resize(f, (320, 240))
    cv2.imshow('stream', f)
    cv2.waitKey(1)
