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

bool MT9D111::ReadRegBit(uint8_t adr, uint8_t bit, bool *state)
{
    uint16_t reg_val;
    if (!this->ReadReg(adr, &reg_val))
    {
        return false;
    }

    uint16_t comp = 0;
    comp |= 1 << bit;

    *state = (reg_val & comp)? true:false;

    return true;
}

bool MT9D111::WriteRegBit(uint8_t adr, uint8_t bit, bool state)
{
    uint16_t reg_val;
    if (!this->ReadReg(adr, &reg_val))
    {
        return false;
    }

    if (state)
    {
        reg_val |= 1 << bit;
    }
    else
    {
        reg_val &= (1 << bit);
    }

    return this->WriteReg(adr, reg_val);
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

bool MT9D111::HardStandby(bool s)
{
    return standby->Set(s);
}

bool MT9D111::SoftStandby(bool s)
{
    // Changing the STANDBY bit state
    return this->WriteRegBit(MT9D111_REG_RESET, 2, s);
}

bool MT9D111::EnablePLL()
{
    // Program PLL frequency settings
    if (!(this->WriteReg(MT9D111_REG_PLL_CONTROL_1, MT9D111_REG_PLL_CONTROL_1_VAL) and
        this->WriteReg(MT9D111_REG_PLL_CONTROL_2, MT9D111_REG_PLL_CONTROL_2_VAL)))
    {
        return false;
    }

    // Power up PLL
    if (!this->WriteRegBit(MT9D111_REG_CLOCK_CONTROL, 14, false))
    {
        return false;
    }

    // Wait for PLL settling time
    usleep(500);

    // Turn off PLL bypass
    if (!this->WriteRegBit(MT9D111_REG_CLOCK_CONTROL, 15, false))
    {
        return false;
    }

    return true;
}

bool MT9D111::SetRegisterPage(uint16_t page)
{
    return this->WriteReg(MT9D111_REG_PAGE_REGISTER, page);
}

bool MT9D111::GetRegisterPage(uint16_t *page)
{
    return this->ReadReg(MT9D111_REG_PAGE_REGISTER, page);
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

bool MT9D111::EnterStandby(uint8_t type)
{
    switch(type)
    {
        case MT9D111_STANDBY_HARD:
            return this->HardStandby(true);
        case MT9D111_STANDBY_SOFT:
            return this->SoftStandby(true);
        default:
            return this->HardStandby(true);
    }
}

bool MT9D111::LeaveStandby(uint8_t type)
{
    switch(type)
    {
        case MT9D111_STANDBY_HARD:
            return this->HardStandby(false);
        case MT9D111_STANDBY_SOFT:
            return this->SoftStandby(false);
        default:
            return this->HardStandby(false);
    }
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

bool MT9D111::SetMode(uint8_t mode)
{
    switch(mode)
    {
        case MT9D111_MODE_PREVIEW:
            if (this->WriteReg(MT9D111_REG_CONTEXT_CONTROL, 0x0000) and
                this->WriteReg(MT9D111_REG_HORIZONTAL_BLANKING_A, 0x00AE) and
                this->WriteReg(MT9D111_REG_VERTICAL_BLANKING_A, 0x0010) and
                this->WriteReg(MT9D111_REG_READ_MODE_A, 0x0490))
            {
                return true;
            }
            else
            {
                return true;
            }
        case MT9D111_MODE_CAPTURE:
            if (this->WriteReg(MT9D111_REG_CONTEXT_CONTROL, 0x000B) and
                this->WriteReg(MT9D111_REG_HORIZONTAL_BLANKING_B, 0x015C) and
                this->WriteReg(MT9D111_REG_VERTICAL_BLANKING_B, 0x0020) and
                this->WriteReg(MT9D111_REG_READ_MODE_B, 0x0000))
            {
                return true;
            }
            else
            {
                return false;
            }
        default:
            return false;
    }
}

bool MT9D111::SetOutputFormat(uint8_t format)
{
    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    switch(format)
    {
        case MT9D111_OUTPUT_FORMAT_YCbCr:
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x01);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_CONFIGURATION, 0x00);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x00);
            break;
        case MT9D111_OUTPUT_FORMAT_RGB565:
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x01);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_CONFIGURATION, 0x20);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x00);
            break;
        case MT9D111_OUTPUT_FORMAT_RGB555:
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x01);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_CONFIGURATION, 0x60);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x00);
            break;
        case MT9D111_OUTPUT_FORMAT_RGB444x:
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x01);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_CONFIGURATION, 0xA0);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x00);
            break;
        case MT9D111_OUTPUT_FORMAT_RGBx444:
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x01);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_CONFIGURATION, 0xE0);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x00);
            break;
        case MT9D111_OUTPUT_FORMAT_JPEG:
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x02);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x00);
            break;
        case MT9D111_OUTPUT_FORMAT_RAW_8:
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_BOOT_MODE, 0x01);
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x00);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x00);
            break;
        case MT9D111_OUTPUT_FORMAT_RAW_10:
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_BOOT_MODE, 0x01);
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x01);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x40);
            break;
        default:
            return false;
    }

    this->SetRegisterPage(MT9D111_REG_PAGE_0);

    return true;
}

bool MT9D111::SetResolution(uint8_t mode, uint16_t width, uint16_t height)
{
    if ((width > MT9D111_OUTPUT_MAX_WIDTH) or (height > MT9D111_OUTPUT_MAX_HEIGHT))
    {
        return false;
    }

    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    switch(mode)
    {
        case MT9D111_MODE_PREVIEW:
            // Output width
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, 0x2703);
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, width);

            // Output height
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, 0x2705);
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, height);
            break;
        case MT9D111_MODE_CAPTURE:
            // Output width
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, 0x2707);
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, width);

            // Output height
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, 0x2709);
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, height);
            break;
        default:
            return false;
    }

    // Sequence command
    this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, 0xA103);
    this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, 5);

    this->SetRegisterPage(MT9D111_REG_PAGE_0);

    return true;
}

bool MT9D111::SetSpecialEffects(uint8_t effect)
{
    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    switch(effect)
    {
        case MT9D111_SPECIAL_EFFECTS_DISABLED:
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_DISABLED | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_MONOCHROME:
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_MONOCHROME | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_SEPIA:
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_SEPIA | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_NEGATIVE:
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_NEGATIVE | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UNMODIFIED_UV:
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UNMODIFIED_UV | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UV:
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UV | (1 << 6));
            break;
        default:
            return false;
    }

    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    return true;
}

//! \} End of mt9d111 group
