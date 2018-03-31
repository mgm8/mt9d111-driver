/*
 * mt9d111.h
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
 * \file mt9d111.h
 * 
 * \brief MT9D111 driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 02/03/2018
 * 
 * \defgroup mt9d111 MT9D111
 * \{
 */

#ifndef MT9D111_H_
#define MT9D111_H_

#include <stdint.h>

#include "i2c.h"
#include "gpio.h"

// I2C addresses
#define MT9D111_CONFIG_I2C_ADR_LOW      0x48
#define MT9D111_CONFIG_I2C_ADR_HIGH     0xBA

#define MT9D111_CONFIG_I2C_ID           MT9D111_CONFIG_I2C_ADR_LOW

// Reset types
#define MT9D111_RESET_HARD              0
#define MT9D111_RESET_SOFT              1

/**
 * \class MT9D111
 *
 * \brief Class to implement the Micron MT9D111 image sensor.
 */
class MT9D111
{
    private:
        I2C *i2c;       /**< I2C device. */
        bool is_open;   /**< Flag to indicate if the I2C communication is open or not. */
        GPIO *reset;    /**< RESET pin. */
        GPIO *standby;  /**< STANDBY pin. */
        /**
         * \brief Hard resets the sensor.
         *
         * After power-up, a hard reset is required. Assuming all supplies are stable,
         * the assertion of RESET_BAR (active LOW) will set the device in reset mode.
         * The clock is required to be active when RESET_BAR is released. Hence, leaving
         * the input clock running during the reset duration is recommended. After 24
         * clock cycles (EXTCLK), the two-wire serial interface is ready to accept
         * commands on the two-wire serial interface.
         *
         * Note: Reset should not be activated while STANDBY is asserted.
         *
         * To activate a hard reset sequence to the camera:
         *     - 1) Wait for all supplies to be stable.
         *     - 2) Assert RESET_BAR (active LOW) for at least 1 us.
         *     - 3) De-assert RESET_BAR (input clock must be running).
         *     - 4) Wait 24 clock cycles before using the two-wire serial interface.
         *     .
         *
         * Reference: MT9D131 Developer Guide. Hard Reset Sequence. Page 12.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool HardReset();
        /**
         * \brief Soft resets the sensor.
         *
         * To activate a soft reset to the camera:
         *     - 1) Bypass the PLL, R0x65:0 = 0xA000, if it is currently used.
         *     - 2) Perform MCU reset by setting R0xC3:1 = 0x0501.
         *     - 3) Enable soft reset by setting R0x0D:0 = 0x0021. Bit 0 is used for the
         *          sensor core reset while bit 5 refers to SOC reset.
         *     - 4) Disable soft reset by setting R0x0D:0 = 0x0000.
         *     - 5) Wait 24 clock cycles before using the two-wire serial interface.
         *     .
         *
         * Note: No access to the MT9D131 registers (both page 1 and page 2) is possible
         * during softreset.
         *
         * Reference: MT9D131 Developer Guide. Soft Reset Sequence. Page 12.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool SoftReset();
    public:
        /**
         * \brief Constructor without parameters.
         *
         * \return None
         */
        MT9D111();
        /**
         * \brief Constructor with I2C communication configuration.
         *
         * With this constructor, the I2C communication is enable and the device becomes ready to work.
         *
         * \param dev_adr is the I2C device address.
         *
         * \return None
         */
        MT9D111(const char *dev_adr);
        /**
         * \brief Destructor.
         *
         * \return None
         */
        ~MT9D111();
        /**
         * \brief Opens the communication with the sensor.
         *
         * \param dev_adr is the I2C device address.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool Open(const char *dev_adr);
        /**
         * \brief Closes the communication with the sensor.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool Close();
        /**
         * \brief Resets the device.
         *
         * \param type is the type of reset (hard or soft).
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool Reset(uint8_t type=MT9D111_RESET_HARD);
        /**
         * \brief Load the configuration parameters into the sensor.
         *
         * \return TRUE/FALSE if the configuration process was successful or not.
         */
        bool Config();
        /**
         * \brief Reads the value of a register of the device.
         *
         * \param adr is the address of the register.
         * \param val is a pointer to store the value of the register.
         *
         * \return TRUE/FALSE if the reading was successful or not.
         */
        bool ReadReg(uint8_t adr, uint16_t *val);
        /**
         * \brief Writes a value to a register of the device.
         *
         * \param adr is the address of the register.
         * \param val is the value to write into the register.
         *
         * \return TRUE/FALSE if the writing was successful or not.
         */
        bool WriteReg(uint8_t adr, uint16_t val);
        /**
         * \brief Checks if the sensor is connected and/or working.
         *
         * This function reads the first reserved register (MT9D111_REG_RESERVED or 0x00), who must return the value 0x1519.
         *
         * \return TRUE/FALSE if the device is connected/working or not. 
         */
        bool CheckDevice();
};

#endif // MT9D111_H_

//! \} End of mt9d111 group
