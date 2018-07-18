#include "lib/keyboard_definitions.h"

namespace linux_keyboard {

  static int non_canonical_kybd(void) {
    int ret_val;
    ret_val = tcgetattr(fd, &initial);
    if (-1 == ret_val) {
      return ret_val;
    }

    current = initial;
    current.c_lflag &= ~ICANON;
    current.c_lflag &= ~ISIG;
    current.c_lflag &= ~ECHO;
    current.c_cc[VMIN] = 0;
    current.c_cc[VTIME] = 0;

    ret_val = tcsetattr(fd, TCSANOW, &current);
    if (-1 == ret_val) {
      return ret_val;
    }

    tcflush(fd, TCIFLUSH);
    return 0;
  }

  /* restores keyboard to it's starting state. Can be used as a signal
   * handler in case the progam terminates unexpectedly.
   */
  void restore_kybd(void) {

    int ret_val;

    current = initial;

    ret_val = tcsetattr(fd, TCSANOW, &current);
    if (-1 == ret_val) {
      // perror( "tcsetattr()" );
      exit(EXIT_FAILURE);
    }

    tcflush(fd, TCIFLUSH);
    return;
  }

  int read_char(int filen, fd_set keyboard, timeval timeout) {
    int sel_ret_val;
    int s_set = filen + 1;
    ssize_t n_read;

    int ch = 0;

    if ((sel_ret_val = select(s_set, &keyboard, NULL, NULL, &timeout)) < 0)
      return -1;

    if (FD_ISSET(fd, &keyboard)) {
      n_read = read(fd, &ch, 1);

      if (n_read < 0)
        return -1;
    }
    return ch;
  }

  int getch(void) {
    fd_set keyboard;
    struct timeval timeout;

    timeout.tv_sec = DEFAULT_TIMEOUT_SECS;
    timeout.tv_usec = DEFAULT_TIMEOUT_USECS;

    if (0 != non_canonical_kybd())
      return 0;

    FD_ZERO(&keyboard);
    FD_SET(fd, &keyboard);

    int ch = read_char(fd, keyboard, timeout);

    if (ch == '\033') {
      read_char(fd, keyboard, timeout);
      switch (read_char(fd, keyboard, timeout)) {
      case 'A':
        ch = KEY_PRESS_UP + 'a';
        break;
      case 'B':
        ch = KEY_PRESS_DOWN + 'a';
        break;
      case 'C':
        ch = KEY_PRESS_RIGHT + 'a';
        break;
      case 'D':
        ch = KEY_PRESS_LEFT + 'a';
        break;
      }
    }

    restore_kybd();
    return ch - 'a';
  }

} // end namespace linux_keyboard
