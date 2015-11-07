#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs-232/rs232.h"

#define COM     24          //comport 24=ttyACM0
#define BAUD    9600

using namespace std;

int main(int argc, char* argv[]) {
    /* int i = 0, */ 
    int cport_nr = COM, 
        bdrate = BAUD;

    char mode[]={'8', 'N', '1', 0};

    if (RS232_OpenComport(cport_nr, bdrate, mode)) {
        //exit if failed to open serial port!
        printf("Arduino not detected! Aborting.\n");
        return 0;
    }

    int command;
    if (strcmp(argv[1], "30") == 0) {
        command = 48;
    }
    else if (strcmp(argv[1], "31") == 0) {
        command = 49;
    }
    else {
        command = 0;
    }

    int error;
    if (command != 0) {
        error = RS232_SendByte(COM, (char)command);
        if (error) {
            printf("%s %s", "Unable to send", argv[1]);
        }
    }
    string result;
    if (command == 48) {
        result = "Monitoring Enabled!";
    }
    else if (command == 49) {
        result = "Monitoring Disabled!";
    }
    else {
        result = "Invalid command!";
    }
    printf("%s\n", result.c_str());

// manual entry
    /* while(1) { */
    /*     RS232_cputs(cport_nr, str[i]); */
    /*     printf("sent: %s\n", str[i]); */

/* #ifdef _WIN32 */
    /* Sleep(100); */
/* #else */
    /* usleep(100000); */
/* #endif */

    /*     i++; */
    /*     i %= 2; */

    /* } */

return 0;
}
