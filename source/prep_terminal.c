#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/prep_terminal.h"

struct termios original_values;

// -----------ENTERING RAW MODE-------------------- //

/*
    Termial attributes can be altered by using tcgetattr().
    1- Read original values to a struct
    2- Alter values within the struct
    3- Send the altered struct back to the system with tcsetattr().
*/

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_values);
}

void enableRawMode(){
    tcgetattr(STDIN_FILENO, &original_values); //Get the terminal values
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
    
    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // TCSAFLUSH decides when the changes to the terminal attributes take effect
    // And how to handle i/o data that are currently in queue
}