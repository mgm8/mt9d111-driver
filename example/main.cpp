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

        return -1;
    }

    cout << "Reseting the sensor..." << endl;
    mt9d111.Reset(MT9D111_RESET_SOFT);

    cout << "Loading configuration...";
    if (mt9d111.Config())
    {
        mt9d111.EnablePLL(0x1000, 0x0500);  // ref = 10 MHz, output = 80 MHz
        mt9d111.SetOutputFormat(MT9D111_OUTPUT_FORMAT_RAW_8);
        mt9d111.SetResolution(MT9D111_MODE_PREVIEW, 640, 480);

        cout << "SUCCESS!" << endl;
    }
    else
    {
        cout << "FAILURE!" << endl;
    }

    mt9d111.Close();

    return 0;
}
