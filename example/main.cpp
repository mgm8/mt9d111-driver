#include <iostream>
#include <mt9d111.h>

using namespace std;

int main()
{
    MT9D111 mt9d111("/dev/i2c-1");

    if (mt9d111.CheckDevice())
    {
        cout << "Device connected!" << endl;
    }
    else
    {
        cout << "Device disconnected!" << endl;
    }

    mt9d111.Close();

    return 0;
}
