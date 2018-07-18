#ifndef KEYBOARD_TELEOP_H_
#define KEYBOARD_TELEOP_H_

#include "lib/keyboard_definitions.h"
#include <ros/ros.h>

// #include <geometry_msgs/Twist.h> // ------------------------------

#define DEFAULT_PUB_TOPIC "keyboard_teleop"
#define DEFAULT_LOOP_RATE 5.0
#define DEFAULT_QUEUE_SIZE 1

// namespace custom_teleop {

template<class T>
class KeyboardTeleop {
public:
  KeyboardTeleop();
  ~KeyboardTeleop() {}

protected:
  void setRate(double rate);
  void setMessage(T initial_msg);
  // void setMessage(geometry_msgs::Twist initial_msg);
  void setTopicName(std::string pub_topic);
  void setQueueSize(int queue_size);
  void setNodeHandle(ros::NodeHandle nh);

  void loop();

  virtual void updateMessage(int key, T &msg) = 0;
  // virtual void updateMessage(int key, geometry_msgs::Twist &msg) = 0;

private:
  ros::NodeHandle nh_;
  std::string pub_topic_;
  double rate_;
  int queue_size_;
  T msg_;
  // geometry_msgs::Twist msg_;
};

// } // end namespace custom_teleop

#endif
