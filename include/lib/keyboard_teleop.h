#ifndef KEYBOARD_TELEOP_H_
#define KEYBOARD_TELEOP_H_

// Linux Keyboard Input
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

// ROS
#include <ros/ros.h>

namespace custom_teleop {

class KeyboardTeleop {
public:
  KeyboardTeleop();
  KeyboardTeleop(double rate = 20.0);
  ~KeyboardTeleop();
protected:

private:

};

} // end namespace custom_teleop

#endif
