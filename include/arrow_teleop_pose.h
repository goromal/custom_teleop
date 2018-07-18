#ifndef KEYBOARD_TELEOP_H_
#define KEYBOARD_TELEOP_H_

#include "lib/keyboard_definitions.h"
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>

#define DEFAULT_PUB_TOPIC "keyboard_teleop"
#define DEFAULT_LOOP_RATE 10.0
#define DEFAULT_QUEUE_SIZE 1

class ArrowTeleopPose {
public:
  ArrowTeleopPose();
  ~ArrowTeleopPose() {}

private:
  void setRate(double rate);
  void setMessage(geometry_msgs::Pose initial_msg);
  void setTopicName(std::string pub_topic);
  void setQueueSize(int queue_size);
  void setNodeHandle(ros::NodeHandle nh);
  void loop();
  void updateMessage(int key, geometry_msgs::Pose &msg);

  ros::NodeHandle nh_;
  std::string pub_topic_;
  double rate_;
  int queue_size_;
  geometry_msgs::Pose msg_;
};

#endif
