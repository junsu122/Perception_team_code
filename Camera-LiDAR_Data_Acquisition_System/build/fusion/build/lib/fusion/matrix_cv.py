#!/usr/bin/env python3

#import cv2
#import numpy as np

#cameraMatrix = np.array([(484.112610, 0.000000,302.908797),(0.000000, 488.804047, 268.598022),(0.000000,0.000000,1.000000)])

#k1 = 0.137207
#k2 = -0.265805
#p1 = -0.003122
#p2 = -0.003723

#distCoeffs = np.array([k1, k2, p1, p2])
# distCoeffs = np.zeros((4,1))

#objectPoints = np.array([(2.5158231258392334,1.816877841949463,0.06869816035032272),
#                         (2.286688804626465,2.0423879623413086,0.07331167906522751),
#                         (2.272894859313965 ,2.03302264213562, -0.10999060422182083),
#                         (4.860964298248291,3.564927577972412,-0.3856508433818817)
#], dtype=np.float64)
#imagePoints = np.array([[392,356],[335,354],[334,393],[392,395]],dtype=np.float64)

#flags = cv2.SOLVEPNP_P3P
#retval, rvec, tvec = cv2.solveP3P(objectPoints, imagePoints, cameraMatrix, distCoeffs, flags=flags)

#R,_ = cv2.Rodrigues(rvec)
#T = tvec


#print("hi")
#print(R)

import cv2
import numpy as np

img = cv2.imread("/home/dandan/colcon_ws/captured_image4.jpg")
size = img.shape

#2차원 영상좌표
points_2D = np.array([
                        (11 , 347),  #좌 상단
                        (8 , 369),  #좌 하단
                        (235 , 335),  #우 상단
                        (237 , 356), #우 하단
                        (114 , 342), #상 중심 좌
                        (139 , 340) #상 중심 우

                      ], dtype="double")
                      
#3차원 월드좌표
points_3D = np.array([
                      ( 1.841947078704834, 1.0209932327270508, 0.04918324947357178),
                      (1.832424283027649, 1.009969711303711, -0.02333700656890869),
                      (1.9867222309112549, 0.38691413402557373, 0.05093801021575928),
                      (1.9704375267028809, 0.37005913257598877,  -0.0076122283935546875),
                      (1.898102879524231, 0.7541316151618958, 0.0618138313293457),
                      ( 2.0140669345855713, 0.6213726997375488, -0.0585477352142334)
                      ], dtype="double")


# camera 내부 파라미터 
cameraMatrix = np.array([(484.112610, 0.000000,302.908797),(0.000000, 488.804047, 268.598022),(0.000000,0.000000,1.000000)])

#distcoeffs는 카메라의 왜곡을 무시하기 때문에 null값 전달
#dist_coeffs = np.zeros((4,1))

k1 = 0.137207
k2 = -0.265805
p1 = -0.003122
p2 = -0.003723

distCoeffs = np.array([k1, k2, p1, p2])
#distCoeffs = np.zeros((4,1))

#solvePnp 함수적용
retval, rvec, tvec = cv2.solvePnP(points_3D, points_2D, cameraMatrix, distCoeffs, rvec=None, tvec=None, useExtrinsicGuess=None, flags=None)

r = cv2.Rodrigues(rvec)
t= tvec

# print(r)
print("\n")
print(t)
