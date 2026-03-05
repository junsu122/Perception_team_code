#!/usr/bin/env python3

import cv2
import numpy as np  

def mouse_callback(event, x, y, flags, param): 
    print("mouse event, x:", x ," y:", y) 

img = cv2.imread("/home/junsu/1.cam/src/fusion/fusion/captured_image4.jpg")

cv2.namedWindow('image')  
cv2.setMouseCallback('image', mouse_callback)

while(True):

    cv2.imshow('image', img)

    k = cv2.waitKey(1) & 0xFF
    if k == 27:  
        print("ESC")
        break
cv2.destroyAllWindows()