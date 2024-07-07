#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/prep_terminal.h"

int main(){
    enableRawMode();
    
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
        if(iscntrl(c)){
            printf("%d\r\n",c);
        }
        else{
            printf("%d ('%c')\r\n",c,c);
        }
    }
    return 0;
}



