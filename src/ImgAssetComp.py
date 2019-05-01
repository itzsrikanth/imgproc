#!/anaconda3/bin/python

########## Requirements ############
# 1) Pickle images
# 2) Image transformation for matching like JPG to PNG
# 3) Using Numba
# 4) File size
# 5) cmd colouring & process percentage status
####################################


import os
import re
import argparse

import json
# from functools import reduce
import math, operator

import cv2
import numpy as np
from skimage.measure import compare_ssim as ssim
from PIL import Image, ImageChops
from resizeimage import resizeimage

# tolerance = 5
# diffPercent = 7

parser = argparse.ArgumentParser(
     description="Image comparison within listed director(y | ies)",
     prog="image_comparison",
     epilog="Packages used: Pillow & python-resize-image")
parser.add_argument('--dir',
    help="list of directories for image comparison",
    required=True,
    nargs="*")
parser.add_argument('--tolerance',
    help="set the value to be considered as zero for difference between two images",
    required=False,
    type=float,
    default=5.0)
parser.add_argument('--diffpc',
    help="set the threshold / match percentage of images",
    required=False,
    type=float,
    default=7.0)
args = parser.parse_args()
# when we get the pixel RGB value difference between two images,
# the result is black(0) if they have same values
# When we resize an image, we deploy some algorithm which results in some +/- value in RGB
# Hence, we cannot expect perfect zero everytime
# So we consider any subtracted value below tolerence to be zero
tolerance = args.tolerance
diffPercent = args.diffpc

images = {}
for dir in args.dir:
    for root, dirs, files in os.walk(dir):
        for file in files:
            if re.search(r'\.(?:jpg|png)$', file) is not None:
                currImg = Image.open(os.path.join(root, file))
                for img in images.keys():
                    # only images with similar aspect ratio(AR) will be same,
                    # so we try to match images only if they have similar AR
                    if (images[img].size[0] / images[img].size[1]) == (currImg.size[0] / currImg.size[1]):
                        # converting the higher resolution image to lower one using best algorithm
                        if images[img].size[0] < currImg.size[0]:
                            tmp2 = currImg.resize(images[img].size, Image.ANTIALIAS)
                            tmp1 = images[img]
                        else:
                            tmp1 = images[img].resize(currImg.size, Image.ANTIALIAS)
                            tmp2 = currImg
                        # now we compare the images
                        absdiff = cv2.absdiff(
                            cv2.cvtColor(np.asarray(tmp1.convert('RGB')), cv2.COLOR_BGR2GRAY),
                            cv2.cvtColor(np.asarray(tmp2.convert('RGB')), cv2.COLOR_BGR2GRAY)
                        )
                        # holder = np.zeros(absdiff.shape[:2])
                        # for i in range(absdiff.shape[0]):
                        #     for j in range(absdiff.shape[1]):
                        #         lessThan = False
                        #         for k in range(absdiff.shape[2]):
                        #             if absdiff[i][j][k] < tolerance:
                        #                 lessThan = True
                        #         if not lessThan:
                        #             holder[i][j] = 1
                        
                        pc = (np.count_nonzero(absdiff > tolerance) * 100) / (absdiff.shape[0] * absdiff.shape[1])
                        if pc < diffPercent:
                            print("%0.2f" % pc, '%\n' + os.path.join(root, file) + '\n' + img + '\n')
                images[root + '/' + file] = currImg

