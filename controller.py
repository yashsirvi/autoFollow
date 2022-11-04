import rospy
from tf.transformations import euler_from_quaternion
from geometry_msgs.msg import Point, Twist
import numpy as np


x = 0.0
y = 0.0
z = 0.0
theta = 0.0
goal = Point()


def callBack(data):
    global x, y, theta, goal
    goal = data
    x = goal.x
    y = goal.y
    z = goal.z
    theta = np.arcsin(x / z)


rospy.init_node("speed_controller", anonymous=True)
sub = rospy.Subscriber("/goal", Point, callBack)
pub = rospy.PublisherI("/cmd_vel", Twist, queue_size=1)
velocity = Twist()
r = rospy.Rate(10)

while not rospy.is_shutdown():
    if abs(theta) > 0.1:
        velocity.linear.x = 0.0
        velocity.angular.z = 0.3
    else:
        speed.linear.x = 0.5
        speed.angular.z = 0.0
    pub.publish(velocity)
    r.sleep()
