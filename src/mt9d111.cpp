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
    this->debug->WriteEvent("Hard reset...");
    this->debug->NewLine();

    if (!this->standby->Set(false))
    {
        return false;
    }

    if (!this->reset->Set(false))
    {
        return false;
    }

    usleep(100);    // 100 us

    if (!this->reset->Set(true))
    {
        return false;
    }

    return true;
}

bool MT9D111::SoftReset()
{
    this->debug->WriteEvent("Soft reset...");
    this->debug->NewLine();

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
    this->debug->WriteEvent("Hard standby...");
    this->debug->NewLine();

    return this->standby->Set(s);
}

bool MT9D111::SoftStandby(bool s)
{
    this->debug->WriteEvent("Soft standby...");
    this->debug->NewLine();

    // Changing the STANDBY bit state
    return this->WriteRegBit(MT9D111_REG_RESET, 2, s);
}

bool MT9D111::EnablePLL(uint16_t val_1, uint16_t val_2)
{
    this->debug->WriteEvent("Enabling PLL with: ");
    this->debug->WriteHex(val_1);
    this->debug->WriteMsg(" and ");
    this->debug->WriteHex(val_2);
    this->debug->WriteMsg("...");
    this->debug->NewLine();

    this->SetRegisterPage(MT9D111_REG_PAGE_0);

    // Program PLL frequency settings
    if (!(this->WriteReg(MT9D111_REG_PLL_CONTROL_1, val_1) and
        this->WriteReg(MT9D111_REG_PLL_CONTROL_2, val_2)))
    {
        return false;
    }

    // Power up PLL
    if (!this->WriteRegBit(MT9D111_REG_CLOCK_CONTROL, 14, false))
    {
        return false;
    }

    // Wait for PLL settling time (> 150 us)
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
    this->debug->WriteEvent("Loading configuration parameters from \"Register Wizard\"...");
    this->debug->NewLine();

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
    if (this->is_open)
    {
        uint16_t reg_val = this->i2c->ReadReg16(adr);

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

        if (reg_val == 0x1519)
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
            this->debug->WriteHex(0x1519);
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
    this->debug->WriteEvent("Set mode to ");

    switch(mode)
    {
        case MT9D111_MODE_PREVIEW:
            this->debug->WriteMsg("PREVIEW...");

            if (this->WriteReg(MT9D111_REG_CONTEXT_CONTROL, 0x0000) and
                this->WriteReg(MT9D111_REG_HORIZONTAL_BLANKING_A, 0x00AE) and
                this->WriteReg(MT9D111_REG_VERTICAL_BLANKING_A, 0x0010) and
                this->WriteReg(MT9D111_REG_READ_MODE_A, 0x0490))
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
        case MT9D111_MODE_CAPTURE:
            this->debug->WriteMsg("PREVIEW...");

            if (this->WriteReg(MT9D111_REG_CONTEXT_CONTROL, 0x000B) and
                this->WriteReg(MT9D111_REG_HORIZONTAL_BLANKING_B, 0x015C) and
                this->WriteReg(MT9D111_REG_VERTICAL_BLANKING_B, 0x0020) and
                this->WriteReg(MT9D111_REG_READ_MODE_B, 0x0000))
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
        default:
            this->debug->WriteMsg("UNKNOWN!");
            this->debug->NewLine();

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

    if (format != MT9D111_OUTPUT_FORMAT_JPEG)
    {
        this->SetRegisterPage(MT9D111_REG_PAGE_2);

        this->WriteReg(MT9D111_REG_JPEG_ENCODER_BYPASS, 0);
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
            return false;
    }

    // Sequencer command
    this->SequencerCmd(MT9D111_DRIVER_VAR_SEQUENCER_CMD_REFRESH);

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

bool MT9D111::SetAutoExposure(uint8_t state, uint8_t config)
{
    this->SetRegisterPage(MT9D111_REG_PAGE_1);

    uint16_t seq_state;

    switch(state)
    {
        case MT9D111_STATE_PREVIEW_ENTER:
            seq_state = MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_0_AE;
            break;
        case MT9D111_STATE_PREVIEW:
            seq_state = MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_1_AE;
            break;
        case MT9D111_STATE_PREVIEW_LEAVE:
            seq_state = MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_2_AE;
            break;
        case MT9D111_STATE_CAPTURE_ENTER:
            seq_state = MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_3_AE;
            break;
        default:
            return false;
    }

    this->WriteReg(MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS, MT9D111_DRIVER_VARIABLE_8_BIT_ACCESS |
                                                                 MT9D111_DRIVER_PHYSICAL_ACCESS_ADDRESS_LOGICAL |
                                                                 MT9D111_DRIVER_ID_SEQUENCER |
                                                                 seq_state);

    switch(config)
    {
        case MT9D111_AUTO_EXPOSURE_OFF:                             break;
        case MT9D111_AUTO_EXPOSURE_FAST_SETTLING:                   break;
        case MT9D111_AUTO_EXPOSURE_MANUAL:                          break;
        case MT9D111_AUTO_EXPOSURE_CONTINUOUS:                      break;
        case MT9D111_AUTO_EXPOSURE_FAST_SETTLING_PLUS_METERING:     break;
        default:                                                    return false;
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
    // Checking if the cmd is valid
    switch(cmd)
    {
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_RUN:              break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_PREVIEW:       break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_CAPTURE:       break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_STANDBY:       break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_DO_LOCK:          break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_REFRESH:          break;
        case MT9D111_DRIVER_VAR_SEQUENCER_CMD_REFRESH_MODE:     break;
        default:                                                return false;
    }

    this->SetRegisterPage(MT9D111_REG_PAGE_1);

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
    switch(context)
    {
        case MT9D111_MODE_PREVIEW:
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
            return false;
    }

    return true;
}

//! \} End of mt9d111 group
