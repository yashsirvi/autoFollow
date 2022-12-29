from smbus import SMBus  # import SMBus module of I2C
from geometry_msgs.msg import Point, Twist  # Twist is a message type
import rospy
import numpy as np

addr = 0x8  # bus address
bus = SMBus(1)  # indicates /dev/ic2-1
dia = 5.9  # wheel diameter in cm
numb = 1

vel_x, w_z = 0, 0  # linear.x, angular.z
w1, w2, w3, w4 = 0, 0, 0, 0  # wheel speeds


def callBack(data):
    vel_x = data.linear.x
    vel_y = data.linear.y
    w_z = data.angular.z
    # calculate wheel speeds
    w1 = (-np.sqrt(2) * vel_x + np.sqrt(2) * vel_y + 0.5 * dia * w_z) / 4
    w2 = (-np.sqrt(2) * vel_x - np.sqrt(2) * vel_y + 0.5 * dia * w_z) / 4
    w3 = (np.sqrt(2) * vel_x - np.sqrt(2) * vel_y + 0.5 * dia * w_z) / 4
    w4 = (np.sqrt(2) * vel_x + np.sqrt(2) * vel_y + 0.5 * dia * w_z) / 4
    bus.write_i2c_block_data(addr, 1, [w1, w2, w3, w4])  # write data to arduino
    print(f"wheel velocities: {w1}, {w2}, {w3}, {w4}\n")


rospy.init_node("raspi_to_arduino", anonymous=True)
sub = rospy.Subscriber("/cmd_vel", Twist, callBack)
