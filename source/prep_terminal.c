#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/error_constants.h"
#include "../include/prep_terminal.h"

struct termios original_values;


// -----------ENTERING RAW MODE-------------------- //

/*
    Termial attributes can be altered by using tcgetattr().
    1- Read original values to a struct
    2- Alter values within the struct
    3- Send the altered struct back to the system with tcsetattr().
*/

void die(const char *s){
    perror(s);
    exit(1);
}

void disableRawMode(){
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_values) == -1){
        die(TCGETATTR_ERR);
    }
}

void enableRawMode(){
    if(tcgetattr(STDIN_FILENO, &original_values) == -1){ //Get the terminal values
        die(TCGETATTR_ERR);
    }
    atexit(disableRawMode); // Register a function to execute when returning 0 or exit() is invoked

    struct termios raw = original_values;


    /*
    Disabling: 
        -> Echo on terminal
        -> Canonical terminal mode 
        -> ISIG (CTRL + Z/C)
        -> IXON (CTRL + S/Q) ==> I: input, XOFF, XON
        -> IEXTEN (CTRL + V)
        -> ICRNL (CTRL + M) ==> turns 13,\r into 10,\n
        -> OPOST Output post processing: Turns \n's into \r\n's
    */
    raw.c_iflag &= ~(IXON | ICRNL);
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

    /*
        Control characters (c_cc)
        VMIN -> Min. # of bytes before read() returns. 0 => return as soon as there is any input to read
        VTIME -> Max. time to wait before read() returns. In tenths if a sec. 1 => 100ms. Returns 0 when timed out.
        By default read() returns the number of bytes read.
    */
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    
    
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1){
        die(TCSETATTR_ERR);
    } // TCSAFLUSH decides when the changes to the terminal attributes take effect
    // And how to handle i/o data that are currently in queue
}