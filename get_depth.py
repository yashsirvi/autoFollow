import numpy as np
import cv2, PIL
from cv2 import aruco
import matplotlib.pyplot as plt
import matplotlib as mpl
import pandas as p

aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_250)
arucoParams = aruco.DetectorParameters_create()

vid = cv2.VideoCapture(0)

mtx = np.array([[1430, 0, 480], [0, 1430, 620], [0, 0, 1]])
distCoeff = np.array([0.253336, 0.102445, 0, 0, 0])
goals = []
while True:
    ret, frame = vid.read()
    corners, ids, rejected = aruco.detectMarkers(
        frame, aruco_dict, parameters=arucoParams
    )
    if len(corners) == 1:
        markerSize = 0.07
        rvec, tvec, _ = aruco.estimatePoseSingleMarkers(
            corners, markerSize, mtx, distCoeff
        )
        x, y, z = tvec[0, 0]
        goal = [x, y]
        goals.append(goal)
        distance = np.sqrt(x**2 + y**2)
        print(f"Goal: {goal}     Distance:  {distance}")
    cv2.imshow("frame", frame)
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break
plt.plot(goals)
plt.show()
vid.release()
cv2.destroyAllWindows()

