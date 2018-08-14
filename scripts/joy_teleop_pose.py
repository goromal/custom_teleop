#!/usr/bin/python

import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Pose
from tf.transformations import quaternion_from_euler as euler2quat

class teleop(object):

    def __init__(self):

        self.joy_sub = rospy.Subscriber('joy', Joy, self.joyCallback, queue_size=1)
        self.pose_pub = rospy.Publisher('pose_command', Pose, queue_size=1)

        self.sensitivity = rospy.get_param('~sensitivity', 0.05)

        self.cmd = Pose()
        self.cmd.position.x = rospy.get_param('initial_mav_x', 0.0)
        self.cmd.position.y = rospy.get_param('initial_mav_y', 0.0)
        self.cmd.position.z = rospy.get_param('initial_mav_z', 0.0)
        self.cmd.orientation.x = 0.0
        self.cmd.orientation.y = 0.0
        self.cmd.orientation.z = 0.0
        self.cmd.orientation.w = 1.0

        self.yaw = 0.0

    def joyCallback(self, msg):

        self.cmd.position.x += self.sensitivity * msg.axes[0] * -1.0
        self.cmd.position.y += self.sensitivity * msg.axes[1]
        self.cmd.position.z += self.sensitivity * msg.axes[3]

        self.yaw += 2 * self.sensitivity * msg.axes[2]

        quaternion = euler2quat(0.0, 0.0, self.yaw)

        self.cmd.orientation.x = quaternion[0]
        self.cmd.orientation.y = quaternion[1]
        self.cmd.orientation.z = quaternion[2]
        self.cmd.orientation.w = quaternion[3]

        self.pose_pub.publish(self.cmd)

if __name__ == "__main__":

    rospy.init_node('teleop_command', anonymous=True)
    tel = teleop()
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print 'Shutting down teleop command node.'
