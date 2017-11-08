#include <iostream>
#include "framerate.hpp"

using std::cout;
using std::endl;

int main()
{
    Framerate f;

    for (int i = 0; i < 10; ++i)
    {
        sleep(1);
        f.printFramerate();
    }
}
