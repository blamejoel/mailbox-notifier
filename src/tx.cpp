#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs-232/rs232.h"

int main() {
    int i = 0, 
        cport_nr = 0, 
        bdrate = 9600;

    char mode[]={'8', 'N', '1', 0},
        str[2][512];

    strcpy(str[0], "test\n");
    strcpy(str[1], "testing\n");

    if (RS232_OpenComport(cport_nr, bdrate, mode)) {
        printf("Unable to open comport\n");

        return 0;
    }

    while(1) {
        RS232_cputs(cport_nr, str[i]);
        printf("sent: %s\n", str[i]);

#ifdef _WIN32
    Sleep(100);
#else
    usleep(100000);
#endif

        i++;
        i %= 2;

    }

return 0;
}
