#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs-232/rs232.h"
#include <iostream>
#include <fstream>

using namespace std;

ofstream outputFile;

int main() {
    int i, n,
        cport_nr=24,
        bdrate=9600;

    unsigned char buf[4096];
    unsigned char CONFIRM = 0xEF;
	
    char mode[]={'8', 'N', '1', 0};

    outputFile.open("log");

    if (RS232_OpenComport(cport_nr, bdrate, mode)) {
        printf("Unable to open comport\n");

        return 0;
    }

    while(1) {
        n = RS232_PollComport(cport_nr, buf, 4095);

        if (n > 0) {
            buf[n] = '\0';         //adding null char to indicate end of input

            for(i = 0; i < n; i++) {
                if (buf[i] < 32) {      //replace unreadable chars by dots
                    buf[i] = '.';
                }
            }
            char test = buf[0];
            if (test == 16) {
                printf("package received!");
				outputFile << "Package received!" << endl;
                RS232_SendByte(cport_nr, CONFIRM);
            }
            /*else if (test == 0x1A) {
                printf("package stolen!");
                RS232_SendByte(cport_nr, CONFIRM);
            }
             printf("You have mail!"); */
            /* printf("received %i bytes: %s\n", n, (char*)buf); */
            printf("You have mail!\n");
			outputFile << "Package received!" << endl;
        }


time_t timev;
#ifdef _WIN32
    Sleep(100);
	outputFile << "Date: " << time(&timev) << endl;	//output date to the log file
#else
    usleep(100000);
	outputFile << "Date: " << time(&timev) << endl; //output date to the log file

#endif

    outputFile.close();
    }

return 0;
}
