#ifndef ARROW_TELEOP_TWIST_H_
#define ARROW_TELEOP_TWIST_H_

#include "lib/keyboard_teleop.h"
#include <geometry_msgs/Twist.h>

template<class T>
class ArrowTeleopTwist : public KeyboardTeleop<T>
{

};

template<>
class ArrowTeleopTwist<geometry_msgs::Twist>
  // : public KeyboardTeleop {
  : public KeyboardTeleop<geometry_msgs::Twist> {
public:
  ArrowTeleopTwist(): KeyboardTeleop<geometry_msgs::Twist>() {
  geometry_msgs::Twist twist;
  std::string topic_name;
  double rate;

  ros::NodeHandle nh_private_("~");
  nh_private_.param<std::string>("topic_name", topic_name, DEFAULT_PUB_TOPIC);
  nh_private_.param<double>("rate", rate, DEFAULT_LOOP_RATE);
  memset(&twist, 0, sizeof(twist));

  setMessage(twist);
  setTopicName(topic_name);
  setRate(rate);

  loop();
}
private:
  void updateMessage(int key, geometry_msgs::Twist &msg) {
    switch(key) {
      case KEY_PRESS_RIGHT: msg.linear.x += 0.1; break;
      case KEY_PRESS_LEFT: msg.linear.x -= 0.1; break;
      case KEY_PRESS_UP: msg.linear.y += 0.1; break;
      case KEY_PRESS_DOWN: msg.linear.y -= 0.1; break;
    }
  }
};

#endif
