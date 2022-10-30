import numpy as np
import cv2, time

cv2.namedWindow("Camera")
cap = cv2.VideoCapture(0)

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
cap.set(cv2.CAP_PROP_FPS, 40)

prev_frame_time = time.time()

cal_image_count = 0
frame_count = 0

while True:
	ret, frame = cap.read()

	frame_count +=1

	if frame_count == 30:
		cv2.imwrite("./images/cal_image_" + str(cal_image_count)+".jpg", frame)
		cal_image_count += 1
		frame_count = 0

	now_frame_time = time.time()
	fps = 1/(now_frame_time - prev_frame_time)
	prev_frame_time = now_frame_time
	cv2.putText(frame, "FPS" + str(int(fps)), (10,40),cv2.FONT_HERSHEY_PLAIN, 3, (100, 2))

	cv2.imshow("Camera", frame)

	key = cv2.waitKey(1) & 0xFF
	if key == ord("q"): 
		break

cap.release()
cv2.destroyAllWindows()

