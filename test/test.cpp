#include <iostream>
#include "opencv2/opencv.hpp"
#include "sample.hpp"

using std::cout;
using std::endl;
using std::cin;

int main()
{
    cout << "test" << endl;
    cout << "opencv version: " << CV_VERSION << endl;
    sample::sample_function();

    return 0;
}
