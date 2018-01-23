#include <iostream>
#include "arduino-serial-communication.hpp"

int main()
{
    setup();

    for (int i = 32; i <= 60; ++i)
    {
        std::ostringstream strm;
        strm << i;
        std::string s = strm.str();
        s = "a" + s;
        s += "\n";
        const char *c = {s.c_str()};
        std::cout << writeSerial(c) << std::endl;
    }
    for (int i = 32; i <= 60; ++i)
    {
        std::ostringstream strm;
        strm << i;
        std::string s = strm.str();
        s = "s" + s;
        s += "\n";
        const char *c = {s.c_str()};
        std::cout << writeSerial(c) << std::endl;
    }

    return 0;
}
