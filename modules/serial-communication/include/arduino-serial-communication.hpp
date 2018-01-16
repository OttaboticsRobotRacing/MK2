#ifndef ARDUINO_SERIAL_COMM_H
#define ARDUINO_SERIAL_COMM_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <sstream>
#include <string>

std::string writeSerial(const char *message);

void setup();


#endif
