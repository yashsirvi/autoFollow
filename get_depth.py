import numpy as np
import cv2, PIL
from cv2 import aruco
import rospy
from geometry_msgs.msg import Point

aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_250)
arucoParams = aruco.DetectorParameters_create()

vid = cv2.VideoCapture("/dev/video0", cv2.CAP_V4L)

mtx = [
    [601.84426834, 0.0, 314.74648445],
    [0.0, 601.45312377, 244.07136337],
    [0.0, 0.0, 1.0],
]
distCoeff = [[0.08850378, -0.67093912, 0.00148015, -0.00494215, 1.0822998]]

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
vid.release()
cv2.destroyAllWindows()


def talker():
    pub = rospy.Publisher("goal", Point, queue_size=1)
    rospy.init_node("goal_finder", anonymous=True)
    rate = rospy.Rate(5)
    while not rospy.is_shutdown():
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
            goal = Point()
            goal.x, goal.y, goal.z = x, y, z
            distance = np.sqrt(x**2 + y**2)
            print(f"Goal: {goal}     Distance:  {distance}")
            rospy.loginfo(goal)
            pub.publish(goal)
            rate.sleep()


if __name__ == "__main__":
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
