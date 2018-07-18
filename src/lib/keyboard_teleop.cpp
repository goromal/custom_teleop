# include "lib/keyboard_teleop.h"

// namespace custom_teleop {

template <class T>
KeyboardTeleop<T>::KeyboardTeleop() {
// KeyboardTeleop::KeyboardTeleop() {
  // Set default values
  pub_topic_ = DEFAULT_PUB_TOPIC;
  rate_ = DEFAULT_LOOP_RATE;
  queue_size_ = DEFAULT_QUEUE_SIZE;
}

template <class T>
void KeyboardTeleop<T>::setRate(double rate) {
// void KeyboardTeleop::setRate(double rate) {
  rate_ = rate;
}

template <class T>
void KeyboardTeleop<T>::setMessage(T initial_msg) {
// void KeyboardTeleop::setMessage(geometry_msgs::Twist initial_msg) {
  msg_ = initial_msg;
}

template <class T>
void KeyboardTeleop<T>::setTopicName(std::string pub_topic) {
// void KeyboardTeleop::setTopicName(std::string pub_topic) {
  pub_topic_ = pub_topic;
}

template <class T>
void KeyboardTeleop<T>::setQueueSize(int queue_size) {
// void KeyboardTeleop::setQueueSize(int queue_size) {
  queue_size_ = queue_size;
}

template <class T>
void KeyboardTeleop<T>::setNodeHandle(ros::NodeHandle nh) {
// void KeyboardTeleop::setNodeHandle(ros::NodeHandle nh) {
  nh_ = nh;
}

template <class T>
void KeyboardTeleop<T>::loop() {
// void KeyboardTeleop::loop() {
  int key = KEY_PRESS_EMPTY;
  ros::Rate loop_rate(rate_);
  ros::Publisher msg_pub = nh_.advertise<T>(pub_topic_, queue_size_);
  // ros::Publisher msg_pub = nh_.advertise<geometry_msgs::Twist>(pub_topic_, queue_size_);

  while (ros::ok() && key != KEY_PRESS_KILL) {
    key = linux_keyboard::getch();
    updateMessage(key, msg_);
    msg_pub.publish(msg_);
    loop_rate.sleep();
  }
}

// } // end namespace custom_teleop
