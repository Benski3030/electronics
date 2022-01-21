# detect AruCo Markers via the drone
import cv2
import apriltag
import djitellopy
import time

# initialize the drone
me = djitellopy.Tello()
me.connect()
print(me.get_battery())
me.streamoff()
me.streamon()
me.takeoff()

# define the AprilTags detector options
# in the input image
print("[INFO] detecting AprilTags...")
options = apriltag.DetectorOptions(families="tag36h11")
detector = apriltag.Detector(options)

# loop over the frames from the video stream and detect the AprilTags
while True:
	# grab the current frame
	image = me.get_frame_read().frame
	image = cv2.resize(image, (320, 240))
	# convert to gray scale 
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	# detect the AprilTags in the image
	result = detector.detect(gray)
	print("[INFO] {} total AprilTags detected".format(len(result)))

	if len(result) > 0:
		for r in result:

			(ptA, ptB, ptC, ptD) = r.corners
			ptB = (int(ptB[0]), int(ptB[1]))
			ptC = (int(ptC[0]), int(ptC[1]))
			ptD = (int(ptD[0]), int(ptD[1]))
			ptA = (int(ptA[0]), int(ptA[1]))

			# draw the bounding box of the AprilTag detection
			cv2.line(image, ptA, ptB, (0, 255, 0), 2)
			cv2.line(image, ptB, ptC, (0, 255, 0), 2)
			cv2.line(image, ptC, ptD, (0, 255, 0), 2)
			cv2.line(image, ptD, ptA, (0, 255, 0), 2)

			# draw the center (x, y)-coordinates of the AprilTag
			(cX, cY) = (int(r.center[0]), int(r.center[1]))
			cv2.circle(image, (cX, cY), 5, (0, 0, 255), -1)

			# draw the tag family on the image
			tagFamily = r.tag_family.decode("utf-8")
			cv2.putText(image, tagFamily, (ptA[0], ptA[1] - 15),
				cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
			print("[INFO] tag family: {}".format(tagFamily))

			# do a backflip!
			if r.tag_id == 0:
				me.flip_back()
				print("[INFO] backflip!")
				time.sleep(3)
			

		# show the output image after AprilTag detection
	cv2.imshow('Image', image)
	if cv2.waitKey(5) & 0xFF == ord('q'):
		break

# close everything
cv2.destroyAllWindows()