/*
 * mt9d111.cpp
 * 
 * Copyright (C) 2018, Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * This file is part of MT9D111-Driver.
 * 
 * MT9D111-Driver is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MT9D111-Driver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with MT9D111-Driver. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \file mt9d111.cpp
 * 
 * \brief MT9D111 driver definition implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 02/03/2018
 * 
 * \addtogroup mt9d111
 * \{
 */

#include "mt9d111.h"
#include "mt9d111_reg.h"
#include "mt9d111_config.h"

MT9D111::MT9D111()
{
    is_open = false;
}

MT9D111::MT9D111(const char *dev_adr)
{
    this->Open(dev_adr);
}

MT9D111::~MT9D111()
{
    if (is_open)
    {
        delete i2c;
    }

    is_open = false;
}

bool MT9D111::Open(const char *dev_adr)
{
    i2c = new I2C;

    if (i2c->Setup(dev_adr, MT9D111_CONFIG_I2C_ID))
    {
        is_open = true;

        return true;
    }
    else
    {
        is_open = false;

        return false;
    }
}

bool MT9D111::Close()
{
    delete i2c;

    is_open = false;

    return true;
}

bool MT9D111::Config()
{
    return true;
}

bool MT9D111::ReadReg(uint8_t adr, uint16_t *val)
{
    if (is_open)
    {
        uint16_t reg_val = i2c->ReadReg16(adr);

        *val = reg_val;

        return true;
    }
    else
    {
        return true;
    }
}

bool MT9D111::WriteReg(uint8_t adr, uint16_t val)
{
    if (is_open)
    {
        return i2c->WriteReg16(adr, val);
    }
    else
    {
        return false;
    }
}

bool MT9D111::CheckDevice()
{
    if (is_open)
    {
        uint16_t reg_val;

        if (!this->ReadReg(MT9D111_REG_RESERVED, &reg_val))
        {
            return false;
        }

        if (reg_val == 0x1519)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

//! \} End of mt9d111 group
