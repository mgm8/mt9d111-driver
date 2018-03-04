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
