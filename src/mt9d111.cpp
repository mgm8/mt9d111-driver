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

#include <unistd.h>

#include "mt9d111.h"
#include "mt9d111_pins.h"
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
    i2c     = new I2C;
    reset   = new GPIO;
    standby = new GPIO;

    if (i2c->Setup(dev_adr, MT9D111_CONFIG_I2C_ID) and
       reset->Open(MT9D111_GPIO_RESET, GPIO_DIR_OUTPUT) and
       standby->Open(MT9D111_GPIO_STANDBY, GPIO_DIR_OUTPUT))
    {
        if (this->HardReset())
        {
            is_open = true;

            return true;
        }
        else
        {
            return false;
        }
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
    delete reset;
    delete standby;

    is_open = false;

    return true;
}

bool MT9D111::HardReset()
{
    if (!standby->Set(false))
    {
        return false;
    }

    if (!reset->Set(false))
    {
        return false;
    }

    usleep(100);    // 100 us

    if (!reset->Set(true))
    {
        return false;
    }

    return true;
}

bool MT9D111::SoftReset()
{
    // Bypass the PLL
    if (!this->WriteReg(MT9D111_REG_CLOCK_CONTROL, 0xA000))
    {
        return false;
    }

    // Perform MCU reset
    if (!this->WriteReg(MT9D111_REG_ASSERT_STROBE_T3, 0x0501))
    {
        return false;
    }

    // Enable soft reset
    if (!this->WriteReg(MT9D111_REG_RESET, 0x0021))
    {
        return false;
    }

    // Disable soft reset
    if (!this->WriteReg(MT9D111_REG_RESET, 0x0000))
    {
        return false;
    }

    return true;
}

bool MT9D111::Reset(uint8_t type)
{
    switch(type)
    {
        case MT9D111_RESET_HARD:
            return this->HardReset();
        case MT9D111_RESET_SOFT:
            return this->SoftReset();
        default:
            return this->HardReset();
    }
}

bool MT9D111::Config()
{
    for(uint8_t i=0; i<(sizeof(reg_default_vals)/sizeof(Register)); i++)
    {
        if (!this->WriteReg(reg_default_vals[i].address, reg_default_vals[i].value))
        {
            return false;
        }
    }

    return true;
}

bool MT9D111::ReadReg(uint8_t adr, uint16_t *val)
{
    if (is_open)
    {
        uint16_t reg_val = i2c->ReadReg16(adr);

        reg_val = ((reg_val & 0xFF00) >> 8) + ((reg_val & 0x00FF) << 8);

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
        val = ((val & 0xFF00) >> 8) + ((val & 0x00FF) << 8);

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
