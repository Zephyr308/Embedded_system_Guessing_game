/**************************************************
file: test.c
purpose: simple demo that tests UART connection with
mbed
exit the program by pressing Ctrl-C
compile with the command: gcc demo_tx.c rs232.c -Wall -Wextra -o2 -o test_tx
**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "rs232.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main()
{
    int i=0 , n = 0,
    cport_nr=14, /* /dev/ttyS0 (COM1 on windows) */
    bdrate=9600; /* 9600 baud */
    char mode[]={'8','N','1',0},
    str[2][512];
    unsigned char buf[256] = {'0'};
    strcpy(str[0], "Waiting for ARM mbed!!!\n");
    //strcpy(str[1], "Hi mbed!!!\n");
    if(RS232_OpenComport(cport_nr, bdrate, mode, 0))
    {
    printf("Can not open comport\n");
    return(0);
    }
    while(1){
        printf("Host: %s", str[0]);
        while(n==0){
               n = RS232_PollComport(cport_nr, buf, 256);
        }
        printf("Received: %d bytes\n",n);
        printf("mbed: %s",(char *)buf);

        // input own test program for mbed
        printf("\nWould you like to play? (y or n): \n");
        scanf("%s",str[1]);
        strcat(str[1], "\n"); // the idea is for the pc terminal to return user input if desire to play the game, that's all.

        RS232_cputs(cport_nr, str[1]);
        printf("Sending: %s\n", str[1]);
    }
RS232_CloseComport(cport_nr); //close the port

    return(0);
}

