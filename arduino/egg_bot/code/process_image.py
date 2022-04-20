# load a png image it and process it as gcode

# import the necessary packages
import numpy as np
import cv2


# load in a png image
#image = cv2.imread("./graphics/smash.png")

img = cv2.imread("./graphics/sonicegg.png", cv2.IMREAD_UNCHANGED)

# adjust with the transparent background
if img.shape[2] == 4:     # we have an alpha channel
  a1 = ~img[:,:,3]        # extract and invert that alpha
  img = cv2.add(cv2.merge([a1,a1,a1,a1]), img)   # add up values (with clipping)
  img = cv2.cvtColor(img, cv2.COLOR_RGBA2RGB)    # strip alpha channel

# convert image to grayscale
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# threshold the image
ret,thresh = cv2.threshold(gray, 200,255,0)
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL , cv2.CHAIN_APPROX_TC89_L1)

# display the countours
img_contours = np.zeros(img.shape)
c_img = cv2.drawContours(img_contours, contours, -1, (0, 255, 0), 1)
cv2.imshow('', c_img)
cv2.waitKey(0)
'''
# save it as a svg
c = max(contours, key=cv2.contourArea) #max contour
f = open('path.svg', 'w+')
f.write('<svg width="'+str(20)+'" height="'+str(80)+'" xmlns="http://www.w3.org/2000/svg">')
f.write('<path d="M')

for i in range(len(c)):
    #print(c[i][0])
    x, y = c[i][0]
    #print(x)
    f.write(str(x)+  ' ' + str(y)+' ')

f.write('"/>')
f.write('</svg>')
f.close()
'''
