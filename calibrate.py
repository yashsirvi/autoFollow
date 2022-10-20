import numpy as np
import cv2
import glob

cb_width = 10
cb_height = 10
cv_sqare_size = 10

criteria =  (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

cb_3D_points = np.zeros((cb_width*cb_height, 3), np.float32)
cb_3D_points[:,:2] = np.mgrid[0:cb_width, 0:cb_height).T.reshape(-1, 2)*cb_sqare_size

list_cb_3d_points = []
list_cb_2d_img_points = []

list_images = glob.glob("./images/*.jpg")

for frame_name in list_images:
    img = cv.imread(frame_name)
    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

    ret, corners = cv.findChessboardCorners(gray, (9,6), None)

    if ret == True:
        list_cb_3d_points.append(cb_3d_points)

        corners2 = cv.cornerSubPix(gray, corners, (11,11), (-1,-1), criteria)
        list_cb_2d_img_points.append(corners)

        cv.drawChessboardCorners(img ,(cb_width, cb_height), corners2, ret)
        cv.imshow('img', img)
        cv.waitKey(500)

cv.destroyAllWindows()

ret, mtx, dist, revcs, tvecs = cv.calibrateCamera(list_cb_3d_points, list_cb_2d_img_points, gray.shape[:: -1 ], None, None)

print("Camera matrix : \n")
print(mtx)
print("dist : \n")
print(dist)
print("rvecs : \n")
print(rvecs)
print("tvecs : \n")
print(tvecs)
