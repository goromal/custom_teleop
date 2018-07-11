/* these functions control the behavior of the keyboard. */

#define _XOPEN_SOURCE
#include <sys/types.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* static file scope variables. */
static struct termios initial;
static struct termios current;
static int fd = STDIN_FILENO;

#ifdef USE_TIMEOUT
#define DEFAULT_TIMEOUT  10.0  /*for p_getch() */
#endif

/* functions */
static int non_canonical_kybd( void )
{
    int ret_val;
    ret_val = tcgetattr( fd, &initial );
    if( -1 == ret_val ) {
        perror( "tcgetattr()" );
        return ret_val;
    }

    current = initial;
    current.c_lflag &= ~ICANON;
    current.c_lflag &= ~ISIG;
    current.c_cc[VMIN] = 0;
    current.c_cc[VTIME] = 0;

    ret_val = tcsetattr( fd, TCSANOW, &current );
    if( -1 == ret_val ) {
         perror( "tcsetattr()" );
         return ret_val;
    }

    tcflush( fd, TCIFLUSH );
    return 0;
}

/* restores keyboard to it's starting state. Can be used as a signal 
 * handler in case the progam terminates unexpectedly.
 */
void restore_kybd( void )
{

    int ret_val;

    current = initial;

    ret_val = tcsetattr( fd, TCSANOW, &current );
    if( -1 == ret_val ) {
         perror( "tcsetattr()" );
         exit( EXIT_FAILURE );
    }

    tcflush( fd, TCIFLUSH );
    return;

}

/* Paul's getch() function. */

/* p_getch() detects that a key has been pressed and returns the character
 * which has been pressed.  If no key has been pressed within the timeout,
 * 0 is returned.
 */

int p_getch( void )
{
    int sel_ret_val;
    int s_set = fd + 1;
    ssize_t n_read;

    int ch = 0;
   
    fd_set  keyboard;
    struct timeval timeout;

#ifdef USE_TIMEOUT
    timeout.tv_sec = DEFAULT_TIMEOUT; 
    timeout.tv_usec = 0;
#endif

    if( 0 != non_canonical_kybd() ) 
        return ch;

    FD_ZERO( &keyboard );
    FD_SET( fd, &keyboard );

    
#ifdef USE_TIMEOUT
    if( (sel_ret_val = select(s_set, &keyboard, NULL, NULL, &timeout)) < 0 )

#else  /* wait forever for user user input */
    if( (sel_ret_val = select(s_set, &keyboard, NULL, NULL, NULL)) < 0 )
#endif
         perror( "select()" );

    if( FD_ISSET(fd, &keyboard) ) {
        n_read = read( fd, &ch, 1 );

        if( n_read < 0 ) 
            perror( "read()" );
   
    }
    restore_kybd();
    return ch;
}


