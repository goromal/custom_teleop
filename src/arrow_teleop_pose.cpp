# include "arrow_teleop_pose.h"

ArrowTeleopPose::ArrowTeleopPose() {
  // Set default values
  pub_topic_ = DEFAULT_PUB_TOPIC;
  rate_ = DEFAULT_LOOP_RATE;
  queue_size_ = DEFAULT_QUEUE_SIZE;

  geometry_msgs::Pose pose;
  pose.orientation.w = 1.0;
  std::string topic_name;
  double rate;

  ros::NodeHandle nh_private_("~");
  nh_private_.param<std::string>("topic_name", topic_name, DEFAULT_PUB_TOPIC);
  nh_private_.param<double>("rate", rate, DEFAULT_LOOP_RATE);
  memset(&pose, 0, sizeof(pose));

  setMessage(pose);
  setTopicName(topic_name);
  setRate(rate);

  loop();
}

void ArrowTeleopPose::setRate(double rate) {
  rate_ = rate;
}

void ArrowTeleopPose::setMessage(geometry_msgs::Pose initial_msg) {
  msg_ = initial_msg;
}

void ArrowTeleopPose::setTopicName(std::string pub_topic) {
  pub_topic_ = pub_topic;
}

void ArrowTeleopPose::setQueueSize(int queue_size) {
  queue_size_ = queue_size;
}

void ArrowTeleopPose::setNodeHandle(ros::NodeHandle nh) {
  nh_ = nh;
}

void ArrowTeleopPose::loop() {
  int key = KEY_PRESS_EMPTY;
  ros::Rate loop_rate(rate_);
  ros::Publisher msg_pub = nh_.advertise<geometry_msgs::Pose>(pub_topic_, queue_size_);

  while (ros::ok() && key != KEY_PRESS_KILL) {
    key = linux_keyboard::getch();
    updateMessage(key, msg_);
    msg_pub.publish(msg_);
    loop_rate.sleep();
  }
}

void ArrowTeleopPose::updateMessage(int key, geometry_msgs::Pose &msg) {
  switch(key) {
    case KEY_PRESS_RIGHT: msg.position.x += 0.1; break;
    case KEY_PRESS_LEFT: msg.position.x -= 0.1; break;
    case KEY_PRESS_UP: msg.position.y += 0.1; break;
    case KEY_PRESS_DOWN: msg.position.y -= 0.1; break;
    case KEY_PRESS_E: msg.position.z += 0.1; break;
    case KEY_PRESS_D: msg.position.z -= 0.1; break;
  }
}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "arrow_teleop_pose");
  ArrowTeleopPose atp;
  ros::spin();
  return 0;
}
