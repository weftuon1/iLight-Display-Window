import time
import os
import datetime

import numpy as np
import argparse
import cv2

while True:
    d1 = time.strftime("%Y_%m_%d-%H_%M_%S")
    action = "fswebcam -r 480x360 -S 10 --no-banner -d /dev/video0 " + "./images/" + "test" + ".jpg"
    os.system(action)

    # construct the argument parse and parse the arguments
    ap = argparse.ArgumentParser()
    #ap.add_argument("-i", "--image", help = "path to the image file")
    #ap.add_argument("-r", "--radius", type = int, help = "radius of Gaussian blur; must be odd")
    args = vars(ap.parse_args())

    args["radius"] = 41
    # load the image and convert it to grayscale
    #image = cv2.imread(args["image"])
    image = cv2.imread("./images/test.jpg")
    orig = image.copy()
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # apply a Gaussian blur to the image then find the brightest
    # region
    gray = cv2.GaussianBlur(gray, (args["radius"], args["radius"]), 0)
    (minVal, maxVal, minLoc, maxLoc) = cv2.minMaxLoc(gray)
    image = orig.copy()
    cv2.circle(image, minLoc, args["radius"], (255, 0, 0), 2)

    # display the results of our newly improved method
    #cv2.imshow("Robust", image)
    #cv2.waitKey(0)
    cv2.imwrite("./images/test2.jpg", image)

    print("minLoc: ", minLoc)
    print("Finished finding darkest area.")

    time.sleep(1*20)
