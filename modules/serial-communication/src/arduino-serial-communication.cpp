/** 
 *  @file   write_to_arduino.cpp
 *  @brief  Arduino serial communication.
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include "arduino-serial-communication.hpp"

struct termios tio;
struct termios stdio;
int tty_fd; //!< Serial port
unsigned char c='D'; //!< Message to send

/**
 *  Writes message to Arduino board through serial.
 *
 *  @brief  Arduino serial communication.
 *  @author Jimmy Deng
 *  @param 	message Message to send to Arduino board.
 *  @date   2018-01-22
 */
std::string writeSerial(const char *message)
{
    tty_fd=open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK);

    cfsetospeed(&tio,B9600);            // 9600 baud
    cfsetispeed(&tio,B9600);            // 9600 baud

    tcsetattr(tty_fd,TCSANOW,&tio);

    const char *str = message;

    write(tty_fd, str, strlen(str));

    std::string retval = "";

    if (read(tty_fd,&c,1)>0)
    {
        retval += c;
        //write(STDOUT_FILENO,&c,1);
    }

    while (c!='\n')
    {
        if (read(tty_fd,&c,1)>0)
        {
            if (c != '\n')
                retval += c;
            //write(STDOUT_FILENO,&c,1); // if new data is available on the serial port, print it out
        }

        if (read(STDIN_FILENO,&c,1)>0)
        {
            if(c!='q')
            {
                write(tty_fd,&c,1);        // if new data is available on the console, send it to the serial port
            }
        }
    }

    close(tty_fd);

    usleep(100000);

    return retval;
}

/**
 *  Setup function for Arduino serial communication.
 *
 *  @brief  Setup function
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
void setup()
{
    fd_set rdset;

    memset(&stdio,0,sizeof(stdio));

    stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=1;
    stdio.c_cc[VTIME]=0;

    //tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    //tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;
}

/**
 *  Writes a set of messages to an Arduino board with a 100ms (100000us) delay between each message.
 *
 *  @brief  Testing function
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
void test()
{
    setup();

    for (int i = 0; i <= 999; i += 82)
    {
        std::ostringstream strm;
        strm << i;
        std::string s = strm.str();
        s = "a" + s;
        s += "\n";
        const char *c = {s.c_str()};
        setup();
        std::cout << writeSerial(c) << std::endl;
        usleep(100000);
    }
    writeSerial(" ");
}

int main()
{
    test();

    return 0;
}