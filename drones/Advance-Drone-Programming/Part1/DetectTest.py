import cv2
from cvzone.FaceDetectionModule import FaceDetector

# open up a open cv video stream
cap = cv2.VideoCapture(0)

# create a face detector
detector = FaceDetector(0.75)

# run the loop and detect faces
while True:
    ret, image = cap.read()
    img, bboxs = detector.findFaces(image, draw=True)
    cv2.imshow('Image', img)
    if cv2.waitKey(5) & 0xFF == ord('q'):
        break

# close down open cv
cv2.destroyAllWindows()
