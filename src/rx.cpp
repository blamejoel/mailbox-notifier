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

string space_replace(string &text) {
    int size = text.size();
    for (int i = 0; i < size; i++) {
        if (text[i] == ' ') {
            text[i] = '_';
        }
    }
    return text;
}

string exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

int main(int argc, char* argv[]) {
    int i, n,
        cport_nr=24,
        bdrate=9600;

    unsigned char buf[4096];
    unsigned char mail = '1';
    unsigned char nomail = '0';
	
    char mode[]={'8', 'N', '1', 0};

    if (argc > 1) {
        string log = "log/";
        string s = exec("date");
        log += s;
        log.erase(log.size() - 1);
        space_replace(log);
        outputFile.open(log.c_str());
        printf("You have mail!\n");
        outputFile << "Package received!" << endl;
        outputFile << s << endl;
        outputFile.close();
        outputFile.open("src/web/mail");
        outputFile << "YOU HAVE MAIL!" << endl;
        outputFile.close();
    }

    if (RS232_OpenComport(cport_nr, bdrate, mode)) {
        printf("Unable to find Arduino.\n");

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

            if (buf[0] == mail) {
                string log = "log/";
                string s = exec("date");
                log += s;
                log.erase(log.size() - 1);
                space_replace(log);
                outputFile.open(log.c_str());
                printf("You have mail!\n");
                outputFile << "Package received!" << endl;
                outputFile << s << endl;
                outputFile.close();
                outputFile.open("src/web/mail");
                outputFile << "YOU HAVE MAIL!" << endl;
                outputFile.close();
            }
            else if (buf[0] == nomail) {
                exec("rm src/web/mail");
            }

        }


#ifdef _WIN32
    Sleep(100);
#else
    usleep(100000);
#endif

    }

return 0;
}
