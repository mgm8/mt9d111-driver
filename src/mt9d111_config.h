/*
 * mt9d111_config.h
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
 * \file mt9d111_config.h
 * 
 * \brief MT9D111 general configuration parameters.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 03/03/2018
 * 
 * \addtogroup mt9d111
 * \{
 */

#ifndef MT9D111_CONFIG_H_
#define MT9D111_CONFIG_H_

#define MT9D111_CONFIG_I2C_ADR_LOW      0x90
#define MT9D111_CONFIG_I2C_ADR_HIGH     0xBA

#define MT9D111_CONFIG_I2C_ID           MT9D111_CONFIG_I2C_ADR_LOW

/**
 * \struct RegisterConfig
 * 
 * \brief Struct to store an register address and its value.
 * 
 */
struct RegisterConfig
{
    uint8_t     address;    /**< Register address. */
    uint16_t    value;      /**< Register value. */
};

/**
 * \var reg_values
 * 
 * \brief Pre-defined sensor registers values.
 */
const RegisterConfig reg_values[] = 
{
    {MT9D111_REG_ROW_START,                     0x001C},
    {MT9D111_REG_COLUMN_START,                  0x003C},
    {MT9D111_REG_ROW_WIDTH,                     0x04B0},
    {MT9D111_REG_COL_WIDTH,                     0x0640},
    {MT9D111_REG_HORIZONTAL_BLANKING_B,         0x0204},
    {MT9D111_REG_VERTICAL_BLANKING_B,           0x002F},
    {MT9D111_REG_HORIZONTAL_BLANKING_A,         0x00FE},
    {MT9D111_REG_VERTICAL_BLANKING_A,           0x000C},
    {MT9D111_REG_SHUTTER_WIDTH,                 0x04D0},
    {MT9D111_REG_ROW_SPEED,                     0x0001},
    {MT9D111_REG_EXTRA_DELAY,                   0x0000},
    {MT9D111_REG_SHUTTER_DELAY,                 0x0000},
    {MT9D111_REG_RESET,                         0x0000},
    {MT9D111_REG_FRAME_VALID_CONTROL,           0x0000},
    {MT9D111_REG_READ_MODE_B,                   0x0300},
    {MT9D111_REG_READ_MODE_A,                   0x8400},
    {MT9D111_REG_DARK_COL_ROWS,                 0x010F},
    {MT9D111_REG_FLASH,                         0x0608},
    {MT9D111_REG_EXTRA_RESET,                   0x8000},
    {MT9D111_REG_LINE_VALID_CONTROL,            0x0000},
    {MT9D111_REG_BOTTOM_DARK_ROWS,              0x0007},
    {MT9D111_REG_GREEN_1_GAIN,                  0x0020},
    {MT9D111_REG_BLUE_GAIN,                     0x0020},
    {MT9D111_REG_RED_GAIN,                      0x0020},
    {MT9D111_REG_GREEN_2_GAIN,                  0x0020},
    {MT9D111_REG_GLOBAL_GAIN,                   0x0020},
    {MT9D111_REG_ROW_NOISE,                     0x042A},
    {MT9D111_REG_BLACK_ROWS,                    0x00FF},
    {MT9D111_REG_DARK_G1_AVERAGE,               0x0000},
    {MT9D111_REG_DARK_B_AVERAGE,                0x0000},
    {MT9D111_REG_DARK_R_AVERAGE,                0x0000},
    {MT9D111_REG_DARK_G2_AVERAGE,               0x0000},
    {MT9D111_REG_CALIB_THRESHOLD,               0x231D},
    {MT9D111_REG_CALIB_CONTROL,                 0x0080},
    {MT9D111_REG_CALIB_GREEN_1,                 0x0000},
    {MT9D111_REG_CALIB_BLUE,                    0x0000},
    {MT9D111_REG_CALIB_RED,                     0x0000},
    {MT9D111_REG_CALIB_GREEN_2,                 0x0000},
    {MT9D111_REG_CLOCK_CONTROL,                 0xE000},
    {MT9D111_REG_PLL_CONTROL_1,                 0x1000},
    {MT9D111_REG_PLL_CONTROL_2,                 0x0500},
    {MT9D111_REG_GLOBAL_SHUTTER_CONTROL,        0x0000},
    {MT9D111_REG_START_INTEGRATION_T1,          0x0064},
    {MT9D111_REG_START_READOUT_T2,              0x0064},
    {MT9D111_REG_ASSERT_STROBE_T3,              0x0096},
    {MT9D111_REG_DEASSERT_STROBE_T4,            0x00C8},
    {MT9D111_REG_ASSERT_FLASH,                  0x0064},
    {MT9D111_REG_DEASSERT_FLASH,                0x0078},
    {MT9D111_REG_EXTERNAL_SAMPLE_1,             0x0000},
    {MT9D111_REG_EXTERNAL_SAMPLE_2,             0x0000},
    {MT9D111_REG_EXTERNAL_SAMPLE_3,             0x0000},
    {MT9D111_REG_EXTERNAL_SAMPLING_CONTROL,     0x0000},
    {MT9D111_REG_PAGE_REGISTER,                 0x0000},
    {MT9D111_REG_BYTEWISE_ADDRESS,              0x0000},
    {MT9D111_REG_CONTEXT_CONTROL,               0x0000}
};

#endif // MT9D111_CONFIG_H_

//! \} End of mt9d111 group
