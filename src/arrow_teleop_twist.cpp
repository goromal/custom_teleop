#include "arrow_teleop_twist.h"

// template<>
// ArrowTeleopTwist<geometry_msgs::Twist>::ArrowTeleopTwist() //{
//   // : KeyboardTeleop() {
//   : KeyboardTeleop<geometry_msgs::Twist>() {
//   geometry_msgs::Twist twist;
//   std::string topic_name;
//   double rate;
//
//   ros::NodeHandle nh_private_("~");
//   nh_private_.param<std::string>("topic_name", topic_name, DEFAULT_PUB_TOPIC);
//   nh_private_.param<double>("rate", rate, DEFAULT_LOOP_RATE);
//   memset(&twist, 0, sizeof(twist));
//
//   setMessage(twist);
//   setTopicName(topic_name);
//   setRate(rate);
//
//   loop();
// }
//
// template<>
// void ArrowTeleopTwist<geometry_msgs::Twist>::updateMessage(int key, geometry_msgs::Twist &msg) {
//   switch(key) {
//     case KEY_PRESS_RIGHT: msg.linear.x += 0.1; break;
//     case KEY_PRESS_LEFT: msg.linear.x -= 0.1; break;
//     case KEY_PRESS_UP: msg.linear.y += 0.1; break;
//     case KEY_PRESS_DOWN: msg.linear.y -= 0.1; break;
//   }
// }

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "arrow_teleop_twist");
  ArrowTeleopTwist<geometry_msgs::Twist> att;
  ros::spin();
  return 0;
}
