#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "../include/prep_terminal.h"

#define EXIT_KEY 'q'

int main(){
    enableRawMode();
    
    while (1){
        char c = '\0'; // \0 == NULL
        if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN){ //EAGAIN is to help Cygwin
            die("READ");
        } // Read from stdin, into c, 1 byte each time
        if(iscntrl(c)){
            printf("%d\r\n",c);
        }
        else{
            printf("%d ('%c')\r\n",c,c);
        }
        if(c == EXIT_KEY){
            break;
        }
    }
    return 0;
}



