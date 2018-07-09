/*
 * gpio.cpp
 * 
 * Copyright (c) 2018, Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * This file is part of MT9D111-Driver.
 * 
 * MT9D111-Driver is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * MT9D111-Driver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with MT9D111-Driver; if not, see <http://www.gnu.org/licenses/>
 * 
 */

/**
 * \brief GPIO Raspberry Pi driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 30/03/2018
 * 
 * \addtogroup gpio
 * \{
 */

#include <fstream>
#include <sstream>
#include <string>

#include "gpio.h"

using namespace std;

GPIO::GPIO()
{

}

GPIO::GPIO(uint8_t p, bool d)
{
    this->Open(p, d);
}

GPIO::~GPIO()
{
    this->Close();
}

bool GPIO::Open(uint8_t p, bool d)
{
    this->pin = p;

    if (this->Export() and this->SetDir(d) and this->Set(false))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GPIO::Close()
{
    return (this->Set(false) and this->Unexport());
}

bool GPIO::Export()
{
    // Open "export" file. Convert C++ string to C string. Required for all Linux pathnames
    ofstream export_gpio("/sys/class/gpio/export");
    if (!export_gpio.is_open())
    {
        return false;
    }

    // Write GPIO number to export
    export_gpio << to_string(this->pin);

    // Close export file
    export_gpio.close(); 
    
    return true;
}

bool GPIO::Unexport()
{
    // Open unexport file
    ofstream unexport("/sys/class/gpio/unexport");
    if (!unexport.is_open())
    {
        return false;
    }
    
    // Write GPIO number to unexport
    unexport << to_string(this->pin);
    
    // Close unexport file
    unexport.close();

    return true;
}

bool GPIO::SetDir(bool d)
{
    // Open direction file for gpio
    ofstream setdir(string("/sys/class/gpio/gpio" + to_string(this->pin) + "/direction").c_str());
    if (!setdir.is_open())
    {
        return false;
    }

    this->dir = d;
    
    // Write direction to direction file
    switch(d)
    {
        case GPIO_DIR_OUTPUT:
            setdir << "out";
            break;
        case GPIO_DIR_INPUT:
            setdir << "in";
            break;
    }
    
    // Close direction file
    setdir.close();
    
    return true;
}

bool GPIO::Set(bool s)
{
    if (this->dir == GPIO_DIR_OUTPUT)
    {
        // Open value file for gpio
        ofstream setval(string("/sys/class/gpio/gpio" + to_string(this->pin) + "/value").c_str());
        if (!setval.is_open())
        {
            return false;
        }

        // Write value to value file
        if (s)
        {
            state = true;
            setval << "1";
        }
        else
        {
            state = false;
            setval << "0";
        }

        // Close value file
        setval.close();
        
        return true;
    }
    else
    {
        return false;
    }
}

bool GPIO::Toggle()
{
    if (this->state)
    {
        return this->Set(false);
    }
    else
    {
        return this->Set(true);
    }
}

bool GPIO::Get(bool &s)
{
    if (this->dir == GPIO_DIR_INPUT)
    {
        // Open value file for gpio
        ifstream getval(string("/sys/class/gpio/gpio" + to_string(this->pin) + "/value").c_str());
        if (!getval.is_open())
        {
            return false;
        }

        // Read gpio value
        string val;
        getval >> val;

        if (val != "0")
        {
            s = true;
        }
        else
        {
            s = false;
        }

        // Close the value file
        getval.close();

        return true;
    }
    else
    {
        return false;
    }
}

uint8_t GPIO::GetPinNumber()
{
    return this->pin;
}

bool GPIO::GetDir()
{
    return this->dir;
}

//! \} End of gpio group
