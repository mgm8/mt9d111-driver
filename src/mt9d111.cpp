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
#include <string>

#include "mt9d111.h"
#include "mt9d111_pins.h"
#include "mt9d111_reg.h"
#include "mt9d111_config.h"
#include "mt9d111_driver.h"

using namespace std;

MT9D111::MT9D111()
{
    this->is_open = false;

    this->debug = new Debug("MT9D111");

    this->debug->WriteEvent("Object created!");
    this->debug->NewLine();
}

MT9D111::MT9D111(const char *dev_adr)
{
    this->debug = new Debug("MT9D111");

    this->debug->WriteEvent("Initializing...");
    this->debug->NewLine();

    this->Open(dev_adr);
}

MT9D111::~MT9D111()
{
    this->debug->WriteEvent("Destroying object...");
    this->debug->NewLine();

    if (this->is_open)
    {
        delete this->i2c;
    }

    this->is_open = false;

    delete debug;
}

bool MT9D111::Open(const char *dev_adr)
{
    this->debug->WriteEvent(string("Opening device \"") + string(dev_adr) + string("\"..."));

    this->i2c     = new I2C;
    this->reset   = new GPIO;
    this->standby = new GPIO;

    if (i2c->Setup(dev_adr, MT9D111_CONFIG_I2C_ID) and
       reset->Open(MT9D111_GPIO_RESET, GPIO_DIR_OUTPUT) and
       standby->Open(MT9D111_GPIO_STANDBY, GPIO_DIR_OUTPUT))
    {
        this->debug->WriteMsg("SUCCESS!");
        this->debug->NewLine();

        if (this->HardReset())
        {
            this->is_open = true;

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        this->debug->WriteMsg("FAILURE!");
        this->debug->NewLine();

        this->is_open = false;

        return false;
    }
}

bool MT9D111::Close()
{
    this->debug->WriteEvent("Closing device...");
    this->debug->NewLine();

    delete this->i2c;
    delete this->reset;
    delete this->standby;

    this->is_open = false;

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
    this->debug->WriteEvent("Executing hard reset...");
    this->debug->NewLine();

    if (!this->standby->Set(false))
    {
        this->debug->WriteEvent("Error during hard reset!");
        this->debug->NewLine();

        return false;
    }

    if (!this->reset->Set(false))
    {
        this->debug->WriteEvent("Error during hard reset!");
        this->debug->NewLine();

        return false;
    }

    usleep(100);    // 100 us

    if (!this->reset->Set(true))
    {
        this->debug->WriteEvent("Error during hard reset!");
        this->debug->NewLine();

        return false;
    }

    return true;
}

bool MT9D111::SoftReset()
{
    this->debug->WriteEvent("Executing soft reset...");
    this->debug->NewLine();

    // Bypass the PLL
    if (!this->WriteAndCheckReg(MT9D111_REG_CLOCK_CONTROL, 0xA000))
    {
        this->debug->WriteEvent("Error during soft reset!");
        this->debug->NewLine();

        return false;
    }

    // Perform MCU reset
    if (!this->WriteReg(MT9D111_REG_ASSERT_STROBE_T3, 0x0501))
    {
        this->debug->WriteEvent("Error during soft reset!");
        this->debug->NewLine();

        return false;
    }

    // Enable soft reset
    if (!this->WriteReg(MT9D111_REG_RESET, 0x0021))
    {
        this->debug->WriteEvent("Error during soft reset!");
        this->debug->NewLine();

        return false;
    }

    // Disable soft reset
    if (!this->WriteReg(MT9D111_REG_RESET, 0x0000))
    {
        this->debug->WriteEvent("Error during soft reset!");
        this->debug->NewLine();

        return false;
    }

    return true;
}

bool MT9D111::HardStandby(bool s)
{
    if (s)
    {
        this->debug->WriteEvent("Enabling hard standby...");
    }
    else
    {
        this->debug->WriteEvent("Disabling hard standby...");
    }

    this->debug->NewLine();

    if (!this->standby->Set(s))
    {
        this->debug->WriteEvent("Error during hard standby!");
        this->debug->NewLine();

        return false;
    }

    return true;
}

bool MT9D111::SoftStandby(bool s)
{
    if (s)
    {
        this->debug->WriteEvent("Enabling soft standby...");
    }
    else
    {
        this->debug->WriteEvent("Disabling soft standby...");
    }

    this->debug->NewLine();

    // Changing the STANDBY bit state
    if (!this->WriteRegBit(MT9D111_REG_RESET, 2, s))
    {
        this->debug->WriteEvent("Error during soft standby!");
        this->debug->NewLine();

        return false;
    }

    return true;
}

bool MT9D111::EnablePLL(uint16_t val_1, uint16_t val_2)
{
    this->debug->WriteEvent("Enabling PLL with ");
    this->debug->WriteHex(val_1);
    this->debug->WriteMsg(" and ");
    this->debug->WriteHex(val_2);
    this->debug->WriteMsg("...");
    this->debug->NewLine();

    this->SetRegisterPage(MT9D111_REG_PAGE_0);

    // Program PLL frequency settings
    if (!this->WriteAndCheckReg(MT9D111_REG_PLL_CONTROL_1, val_1))
    {
        this->debug->WriteEvent("Error enabling the PLL!");
        this->debug->NewLine();

        return false;
    }

    if (!this->WriteAndCheckReg(MT9D111_REG_PLL_CONTROL_2, val_2))
    {
        this->debug->WriteEvent("Error enabling the PLL!");
        this->debug->NewLine();

        return false;
    }

    // Power up PLL
    if (!this->WriteRegBit(MT9D111_REG_CLOCK_CONTROL, 14, false))
    {
        this->debug->WriteEvent("Error enabling the PLL!");
        this->debug->NewLine();

        return false;
    }

    // Wait for PLL settling time (> 150 us)
    usleep(500);

    // Turn off PLL bypass
    if (!this->WriteRegBit(MT9D111_REG_CLOCK_CONTROL, 15, false))
    {
        this->debug->WriteEvent("Error enabling the PLL!");
        this->debug->NewLine();

        return false;
    }

    return true;
}

bool MT9D111::SetRegisterPage(uint16_t page)
{
    if (this->WriteAndCheckReg(MT9D111_REG_PAGE_REGISTER, page))
    {
        return true;
    }
    else
    {
        this->debug->WriteEvent("Error configuring register page to ");
        this->debug->WriteDec(page);
        this->debug->WriteMsg("!");
        this->debug->NewLine();

        return false;
    }
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
    this->debug->WriteEvent("Loading configuration parameters from \"Register Wizard\"...");
    this->debug->NewLine();

    for(uint8_t i=0; i<(sizeof(reg_default_vals)/sizeof(Register)); i++)
    {
        if (!this->WriteAndCheckReg(reg_default_vals[i].address, reg_default_vals[i].value))
        {
            this->debug->WriteEvent("Error loading configuration parameters!");
            this->debug->NewLine();

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
    if (this->is_open)
    {
        uint16_t reg_val = this->i2c->ReadReg16(adr);

        reg_val = ((reg_val & 0xFF00) >> 8) + ((reg_val & 0x00FF) << 8);

        *val = reg_val;

        return true;
    }
    else
    {
        return false;
    }
}

bool MT9D111::CheckReg(uint8_t adr, uint16_t val)
{
    uint16_t reg_val = 0xFFFF;

    if (this->ReadReg(adr, &reg_val))
    {
        if (reg_val == val)
        {
            return true;
        }
        else
        {
            this->debug->WriteEvent("Error checking register ");
            this->debug->WriteHex(adr);
            this->debug->WriteMsg("! (read=");
            this->debug->WriteHex(reg_val);
            this->debug->WriteMsg(", expected=");
            this->debug->WriteHex(val);
            this->debug->WriteMsg(")");
            this->debug->NewLine();

            return false;
        }
    }
    else
    {
        return false;
    }
}

bool MT9D111::WriteReg(uint8_t adr, uint16_t val)
{
    if (this->is_open)
    {
        val = ((val & 0xFF00) >> 8) + ((val & 0x00FF) << 8);

        return this->i2c->WriteReg16(adr, val);
    }
    else
    {
        return false;
    }
}

bool MT9D111::WriteAndCheckReg(uint8_t adr, uint16_t val, unsigned int attempts)
{
    for(unsigned int i=0; i<attempts; i++)
    {
        if (this->WriteReg(adr, val))
        {
            if (this->CheckReg(adr, val))
            {
                return true;
            }
            else
            {
                this->debug->WriteEvent("Error writing ");
                this->debug->WriteHex(val);
                this->debug->WriteMsg(" to address ");
                this->debug->WriteHex(adr);
                this->debug->WriteMsg("! Trying again (");
                this->debug->WriteDec(i+1);
                this->debug->WriteMsg(" of ");
                this->debug->WriteDec(attempts);
                this->debug->WriteMsg(")");
                this->debug->NewLine();
            }
        }
        else
        {
            return false;
        }
    }

    return false;
}

bool MT9D111::CheckDevice()
{
    this->debug->WriteEvent("Checking device...");

    if (this->is_open)
    {
        uint16_t reg_val;

        if (!this->ReadReg(MT9D111_REG_RESERVED, &reg_val))
        {
            this->debug->WriteMsg("FAILURE!");
            this->debug->NewLine();

            return false;
        }

        if (reg_val == MT9D111_ID_CODE)
        {
            this->debug->WriteMsg("SUCCESS!");
            this->debug->NewLine();

            return true;
        }
        else
        {
            this->debug->WriteMsg("FAILURE!");
            this->debug->NewLine();

            this->debug->WriteEvent("Wrong device ID! (read=");
            this->debug->WriteHex(reg_val);
            this->debug->WriteMsg(", expected=");
            this->debug->WriteHex(MT9D111_ID_CODE);
            this->debug->WriteMsg(")");
            this->debug->NewLine();

            return false;
        }
    }
    else
    {
        this->debug->WriteMsg("FAILURE!");
        this->debug->NewLine();

        this->debug->WriteEvent("Communication bus not opened!");
        this->debug->NewLine();

        return false;
    }
}

bool MT9D111::SetMode(uint8_t mode)
{
    this->debug->WriteEvent("Configuring mode to ");

    switch(mode)
    {
        case MT9D111_MODE_PREVIEW:
            this->debug->WriteMsg("PREVIEW...");

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_SEQUENCER |
                                                                         MT9D111_DRIVER_VAR_SEQUENCER_CAPTURE_PARAMS_MODE);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, 1);

            this->SequencerCmd(MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_PREVIEW);

            break;
        case MT9D111_MODE_CAPTURE:
            this->debug->WriteMsg("PREVIEW...");

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_SEQUENCER |
                                                                         MT9D111_DRIVER_VAR_SEQUENCER_CAPTURE_PARAMS_MODE);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, 0);

            this->SequencerCmd(MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_CAPTURE);

            break;
        default:
            this->debug->WriteMsg("UNKNOWN!");
            this->debug->NewLine();

            return false;
    }

    if (this->GetMode() == mode)
    {
        this->debug->WriteMsg("SUCCESS!");
        this->debug->NewLine();

        return true;
    }
    else
    {
        this->debug->WriteMsg("FAILURE!");
        this->debug->NewLine();

        return false;
    }
}

uint8_t MT9D111::GetMode()
{
    this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                 MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                 MT9D111_DRIVER_ID_MODE |
                                                                 MT9D111_DRIVER_VAR_MODE_CONTEXT);

    uint16_t mode = 0xFF;
    this->ReadReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, &mode);

    return (uint8_t)(mode);
}

bool MT9D111::SetOutputFormat(uint8_t format)
{
    this->debug->WriteEvent("Configuring output format as ");

    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    switch(format)
    {
        case MT9D111_OUTPUT_FORMAT_YCbCr:
            this->debug->WriteMsg("YCbCr...");
            this->debug->NewLine();

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_A);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, 0);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_B);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, 0);

            break;
        case MT9D111_OUTPUT_FORMAT_RGB565:
            this->debug->WriteMsg("RGB565...");
            this->debug->NewLine();

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_A);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, (1 << 5));

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_B);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, (1 << 5));

            break;
        case MT9D111_OUTPUT_FORMAT_RGB555:
            this->debug->WriteMsg("RGB555...");
            this->debug->NewLine();

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_A);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, (1 << 5) | (1 << 6));

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_B);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, (1 << 5) | (1 << 6));

            break;
        case MT9D111_OUTPUT_FORMAT_RGB444x:
            this->debug->WriteMsg("RGB444x...");
            this->debug->NewLine();

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_A);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_B);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, (1 << 5) | (1 << 7));

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, (1 << 5) | (1 << 7));

            break;
        case MT9D111_OUTPUT_FORMAT_RGBx444:
            this->debug->WriteMsg("RGBx444...");
            this->debug->NewLine();

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_A);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, (1 << 5) | (1 << 6) | (1 << 7));

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_B);

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, (1 << 5) | (1 << 6) | (1 << 7));

            break;
        case MT9D111_OUTPUT_FORMAT_JPEG:
            this->debug->WriteMsg("JPEG...");
            this->debug->NewLine();

            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x02);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x00);
            break;
        case MT9D111_OUTPUT_FORMAT_RAW_8:
            this->debug->WriteMsg("RAW8...");
            this->debug->NewLine();

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_BOOT_MODE, 0x01);
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x00);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, 0x00);
            break;
        case MT9D111_OUTPUT_FORMAT_RAW_10:
            this->debug->WriteMsg("RAW10...");
            this->debug->NewLine();

            this->WriteReg(MT9D111_REG_MICROCONTROLLER_BOOT_MODE, 0x01);
            this->WriteReg(MT9D111_REG_FACTORY_BYPASS, 0x01);
            this->WriteReg(MT9D111_REG_OUTPUT_FORMAT_TEST, (1 << 6));
            break;
        default:
            this->debug->WriteMsg("UNKNOWN...");
            this->debug->NewLine();

            return false;
    }

    if (format != MT9D111_OUTPUT_FORMAT_JPEG)
    {
        this->SetRegisterPage(MT9D111_REG_PAGE_2);

        this->WriteReg(MT9D111_REG_JPEG_ENCODER_BYPASS, 0);
    }

    this->SequencerCmd(MT9D111_DRIVER_VAR_SEQUENCER_CMD_REFRESH);

    return true;
}

bool MT9D111::SetResolution(uint8_t mode, uint16_t width, uint16_t height)
{
    this->debug->WriteEvent("Configuring resolution as ");
    this->debug->WriteDec(width);
    this->debug->WriteMsg("x");
    this->debug->WriteDec(height);

    if ((width > MT9D111_OUTPUT_MAX_WIDTH) or (height > MT9D111_OUTPUT_MAX_HEIGHT))
    {
        return false;
    }

    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    this->debug->WriteMsg(" for ");

    switch(mode)
    {
        case MT9D111_MODE_PREVIEW:
            this->debug->WriteMsg("PREVIEW mode...");
            this->debug->NewLine();

            // Output width
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_16_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUTPUT_WIDTH_A);
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, width);

            // Output height
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_16_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUTPUT_HEIGHT_A);
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, height);

            break;
        case MT9D111_MODE_CAPTURE:
            this->debug->WriteMsg("CAPTURE mode...");
            this->debug->NewLine();

            // Output width
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_16_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUTPUT_WIDTH_B);
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, width);

            // Output height
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_16_BIT_ACCESS |
                                                                         MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                         MT9D111_DRIVER_ID_MODE |
                                                                         MT9D111_DRIVER_VAR_MODE_OUTPUT_HEIGHT_B);
            this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, height);

            break;
        default:
            this->debug->WriteMsg("UNKNONW mode");
            this->debug->NewLine();

            return false;
    }

    // Sequencer command
    this->SequencerCmd(MT9D111_DRIVER_VAR_SEQUENCER_CMD_REFRESH);

    return true;
}

bool MT9D111::SetSpecialEffects(uint8_t effect)
{
    this->debug->WriteEvent("Configuring special effects as ");

    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    switch(effect)
    {
        case MT9D111_SPECIAL_EFFECTS_DISABLED:
            this->debug->WriteMsg("DISABLED");
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_DISABLED | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_MONOCHROME:
            this->debug->WriteMsg("MONOCHROME");
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_MONOCHROME | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_SEPIA:
            this->debug->WriteMsg("SEPIA");
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_SEPIA | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_NEGATIVE:
            this->debug->WriteMsg("NEGATIVE");
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_NEGATIVE | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UNMODIFIED_UV:
            this->debug->WriteMsg("SOLARIZATION WITH UNMODIFIED UV");
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UNMODIFIED_UV | (1 << 6));
            break;
        case MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UV:
            this->debug->WriteMsg("SOLARIZATION WITH UV");
            this->WriteReg(MT9D111_REG_SPECIAL_EFFECTS, MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UV | (1 << 6));
            break;
        default:
            this->debug->WriteMsg("UNKNOWN");
            return false;
    }

    this->debug->WriteMsg("...");
    this->debug->NewLine();

    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    return true;
}

bool MT9D111::SetAutoExposure(uint8_t state, uint8_t config)
{
    this->debug->WriteEvent("Configuring auto-exposure for ");

    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    uint16_t seq_state;

    switch(state)
    {
        case MT9D111_STATE_PREVIEW_ENTER:
            this->debug->WriteMsg("PREVIEW ENTER state as ");
            seq_state = MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_0_AE;
            break;
        case MT9D111_STATE_PREVIEW:
            this->debug->WriteMsg("PREVIEW state as ");
            seq_state = MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_1_AE;
            break;
        case MT9D111_STATE_PREVIEW_LEAVE:
            this->debug->WriteMsg("PREVIEW LEAVE state as ");
            seq_state = MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_2_AE;
            break;
        case MT9D111_STATE_CAPTURE_ENTER:
            this->debug->WriteMsg("PREVIEW ENTER state as ");
            seq_state = MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_3_AE;
            break;
        default:
            this->debug->WriteMsg("UNKNOWN state as ");
            return false;
    }

    this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                 MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                 MT9D111_DRIVER_ID_SEQUENCER |
                                                                 seq_state);

    switch(config)
    {
        case MT9D111_AUTO_EXPOSURE_OFF:
            this->debug->WriteMsg("OFF...");
            break;
        case MT9D111_AUTO_EXPOSURE_FAST_SETTLING:
            this->debug->WriteMsg("FAST SETTLING...");
            break;
        case MT9D111_AUTO_EXPOSURE_MANUAL:
            this->debug->WriteMsg("MANUAL...");
            break;
        case MT9D111_AUTO_EXPOSURE_CONTINUOUS:
            this->debug->WriteMsg("CONTINUOUS...");
            break;
        case MT9D111_AUTO_EXPOSURE_FAST_SETTLING_PLUS_METERING:
            this->debug->WriteMsg("FAST SETTLING + METERING...");
            break;
        default:
            this->debug->WriteMsg("UNKNOWN...");
            return false;
    }

    this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, config);

    // Sequencer command
    this->SequencerCmd(MT9D111_DRIVER_VAR_SEQUENCER_CMD_REFRESH);

    return true;
}

bool MT9D111::SetFIFO(bool en, bool spoof)
{
    this->SetRegisterPage(MT9D111_REG_PAGE_2);

    if (en)
    {
        this->WriteReg(MT9D111_REG_JPEG_ENCODER_BYPASS, 1);
    }
    else
    {
        this->WriteReg(MT9D111_REG_JPEG_ENCODER_BYPASS, 0);
    }

    this->SetSpoofFrames(spoof);

    return true;
}

bool MT9D111::SetSpoofFrames(bool en, uint16_t width, uint16_t height)
{
    this->SetRegisterPage(MT9D111_REG_PAGE_2);

    if (en)
    {
        this->WriteRegBit(MT9D111_REG_OUTPUT_CONFIG, 0, true);
        this->WriteReg(MT9D111_REG_SPOOF_FRAME_WIDTH, width);
        this->WriteReg(MT9D111_REG_SPOOF_FRAME_HEIGHT, height);
    }
    else
    {
        this->WriteRegBit(MT9D111_REG_OUTPUT_CONFIG, 0, false);
    }

    return true;
}

bool MT9D111::SequencerCmd(uint8_t cmd)
{
    this->debug->WriteEvent("Executing sequencer command ");

    // Checking if the cmd is valid
    switch(cmd)
    {
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_RUN:
            this->debug->WriteMsg("RUN");
            break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_PREVIEW:
            this->debug->WriteMsg("DO PREVIEW");
            break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_CAPTURE:
            this->debug->WriteMsg("DO CAPTURE");
            break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_STANDBY:
            this->debug->WriteMsg("DO STANDBY");
            break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_LOCK:
            this->debug->WriteMsg("DO LOCK");
            break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_REFRESH:
            this->debug->WriteMsg("REFRESH");
            break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_REFRESH_MODE:
            this->debug->WriteMsg("REFRESH MODE");
            break;
        default:
            this->debug->WriteMsg("UNKNOWN");
            return false;
    }

    this->debug->WriteMsg("...");
    this->debug->NewLine();

    this->SetRegisterPage(MT9D111_REG_PAGE_0);

    // Driver variable address
    this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                 MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                 MT9D111_DRIVER_ID_SEQUENCER |
                                                                 MT9D111_DRIVER_VAR_SEQUENCER_CMD);

    // Driver variable data
    this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA, cmd);

    return true;
}

bool MT9D111::SetRowSkipping(uint8_t context, uint8_t skip)
{
    // Testing skip value
    switch(skip)
    {
        case MT9D111_SKIP_2X:   break;
        case MT9D111_SKIP_4X:   break;
        case MT9D111_SKIP_8X:   break;
        case MT9D111_SKIP_16X:  break;
        default:                return false;
    }

    switch(context)
    {
        case MT9D111_MODE_PREVIEW:
            // Enable row skip
            this->WriteRegBit(MT9D111_REG_READ_MODE_A, 4, true);

            switch(skip)
            {
                case MT9D111_SKIP_2X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 3, false);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 2, false);
                    break;
                case MT9D111_SKIP_4X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 3, false);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 2, true);
                    break;
                case MT9D111_SKIP_8X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 3, true);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 2, false);
                    break;
                case MT9D111_SKIP_16X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 3, true);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 2, true);
                    break;
            }

            break;
        case MT9D111_MODE_CAPTURE:
            // Enable row skip
            this->WriteRegBit(MT9D111_REG_READ_MODE_B, 4, true);

            switch(skip)
            {
                case MT9D111_SKIP_2X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 3, false);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 2, false);
                    break;
                case MT9D111_SKIP_4X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 3, false);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 2, true);
                    break;
                case MT9D111_SKIP_8X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 3, true);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 2, false);
                    break;
                case MT9D111_SKIP_16X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 3, true);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 2, true);
                    break;
            }

            break;
        defautl:
            return false;
    }

    return true;
}

bool MT9D111::SetColSkipping(uint8_t context, uint8_t skip)
{
    // Testing skip value
    switch(skip)
    {
        case MT9D111_SKIP_2X:   break;
        case MT9D111_SKIP_4X:   break;
        case MT9D111_SKIP_8X:   break;
        case MT9D111_SKIP_16X:  break;
        default:                return false;
    }

    switch(context)
    {
        case MT9D111_MODE_PREVIEW:
            // Enable row skip
            this->WriteRegBit(MT9D111_REG_READ_MODE_A, 7, true);

            switch(skip)
            {
                case MT9D111_SKIP_2X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 6, false);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 5, false);
                    break;
                case MT9D111_SKIP_4X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 6, false);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 5, true);
                    break;
                case MT9D111_SKIP_8X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 6, true);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 5, false);
                    break;
                case MT9D111_SKIP_16X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 6, true);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 5, true);
                    break;
            }

            break;
        case MT9D111_MODE_CAPTURE:
            // Enable row skip
            this->WriteRegBit(MT9D111_REG_READ_MODE_B, 7, true);

            switch(skip)
            {
                case MT9D111_SKIP_2X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 6, false);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 5, false);
                    break;
                case MT9D111_SKIP_4X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 6, false);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 5, true);
                    break;
                case MT9D111_SKIP_8X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 6, true);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 5, false);
                    break;
                case MT9D111_SKIP_16X:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 6, true);
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 5, true);
                    break;
            }

            break;
        defautl:
            return false;
    }

    return true;
}

bool MT9D111::SetNumberOfADCs(uint8_t context, uint8_t adcs)
{
    this->debug->WriteEvent("Configuring the number of ADCs for ");

    switch(context)
    {
        case MT9D111_MODE_PREVIEW:
            this->debug->WriteMsg("PREVIEW mode as ");
            this->debug->WriteDec(adcs);
            this->debug->WriteMsg("...");
            this->debug->NewLine();

            switch(adcs)
            {
                case 1:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 10, true);
                    break;
                case 2:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_A, 10, false);
                    break;
                default:
                    return false;
            }

            break;
        case MT9D111_MODE_CAPTURE:
            this->debug->WriteMsg("CAPTURE mode as ");
            this->debug->WriteDec(adcs);
            this->debug->WriteMsg("...");
            this->debug->NewLine();

            switch(adcs)
            {
                case 1:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 10, true);
                    break;
                case 2:
                    this->WriteRegBit(MT9D111_REG_READ_MODE_B, 10, false);
                    break;
                default:
                    return false;
            }

            break;
        default:
            this->debug->WriteMsg("UNKNOWN mode!");
            this->debug->NewLine();

            return false;
    }

    return true;
}

//! \} End of mt9d111 group
