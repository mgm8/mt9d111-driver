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

#include "mt9d111_reg.h"

// PLL values
#define MT9D111_REG_PLL_CONTROL_1_VAL           0x1000
#define MT9D111_REG_PLL_CONTROL_2_VAL           0x0500

/**
 * \var reg_default_vals
 * 
 * \brief Default registers values (Values after boot).
 */
const Register reg_default_vals[] = 
{
    {MT9D111_REG_ROW_START,                     MT9D111_REG_PAGE_0,             0x001C},
    {MT9D111_REG_COLUMN_START,                  MT9D111_REG_PAGE_0,             0x003C},
    {MT9D111_REG_ROW_WIDTH,                     MT9D111_REG_PAGE_0,             0x04B0},
    {MT9D111_REG_COL_WIDTH,                     MT9D111_REG_PAGE_0,             0x0640},
    {MT9D111_REG_HORIZONTAL_BLANKING_B,         MT9D111_REG_PAGE_0,             0x0204},
    {MT9D111_REG_VERTICAL_BLANKING_B,           MT9D111_REG_PAGE_0,             0x002F},
    {MT9D111_REG_HORIZONTAL_BLANKING_A,         MT9D111_REG_PAGE_0,             0x00FE},
    {MT9D111_REG_VERTICAL_BLANKING_A,           MT9D111_REG_PAGE_0,             0x000C},
    {MT9D111_REG_SHUTTER_WIDTH,                 MT9D111_REG_PAGE_0,             0x04D0},
    {MT9D111_REG_ROW_SPEED,                     MT9D111_REG_PAGE_0,             0x0001},
    {MT9D111_REG_EXTRA_DELAY,                   MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_SHUTTER_DELAY,                 MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_RESET,                         MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_FRAME_VALID_CONTROL,           MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_READ_MODE_B,                   MT9D111_REG_PAGE_0,             0x0300},
    {MT9D111_REG_READ_MODE_A,                   MT9D111_REG_PAGE_0,             0x8400},
    {MT9D111_REG_DARK_COL_ROWS,                 MT9D111_REG_PAGE_0,             0x010F},
    {MT9D111_REG_FLASH,                         MT9D111_REG_PAGE_0,             0x0608},
    {MT9D111_REG_EXTRA_RESET,                   MT9D111_REG_PAGE_0,             0x8000},
    {MT9D111_REG_LINE_VALID_CONTROL,            MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_BOTTOM_DARK_ROWS,              MT9D111_REG_PAGE_0,             0x0007},
    {MT9D111_REG_GREEN_1_GAIN,                  MT9D111_REG_PAGE_0,             0x0020},
    {MT9D111_REG_BLUE_GAIN,                     MT9D111_REG_PAGE_0,             0x0020},
    {MT9D111_REG_RED_GAIN,                      MT9D111_REG_PAGE_0,             0x0020},
    {MT9D111_REG_GREEN_2_GAIN,                  MT9D111_REG_PAGE_0,             0x0020},
    {MT9D111_REG_GLOBAL_GAIN,                   MT9D111_REG_PAGE_0,             0x0020},
    {MT9D111_REG_ROW_NOISE,                     MT9D111_REG_PAGE_0,             0x042A},
    {MT9D111_REG_BLACK_ROWS,                    MT9D111_REG_PAGE_0,             0x00FF},
    {MT9D111_REG_DARK_G1_AVERAGE,               MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_DARK_B_AVERAGE,                MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_DARK_R_AVERAGE,                MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_DARK_G2_AVERAGE,               MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_CALIB_THRESHOLD,               MT9D111_REG_PAGE_0,             0x231D},
    {MT9D111_REG_CALIB_CONTROL,                 MT9D111_REG_PAGE_0,             0x0080},
    {MT9D111_REG_CALIB_GREEN_1,                 MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_CALIB_BLUE,                    MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_CALIB_RED,                     MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_CALIB_GREEN_2,                 MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_CLOCK_CONTROL,                 MT9D111_REG_PAGE_0,             0xE000},
    {MT9D111_REG_PLL_CONTROL_1,                 MT9D111_REG_PAGE_0,             0x1000},
    {MT9D111_REG_PLL_CONTROL_2,                 MT9D111_REG_PAGE_0,             0x0500},
    {MT9D111_REG_GLOBAL_SHUTTER_CONTROL,        MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_START_INTEGRATION_T1,          MT9D111_REG_PAGE_0,             0x0064},
    {MT9D111_REG_START_READOUT_T2,              MT9D111_REG_PAGE_0,             0x0064},
    {MT9D111_REG_ASSERT_STROBE_T3,              MT9D111_REG_PAGE_0,             0x0096},
    {MT9D111_REG_DEASSERT_STROBE_T4,            MT9D111_REG_PAGE_0,             0x00C8},
    {MT9D111_REG_ASSERT_FLASH,                  MT9D111_REG_PAGE_0,             0x0064},
    {MT9D111_REG_DEASSERT_FLASH,                MT9D111_REG_PAGE_0,             0x0078},
    {MT9D111_REG_EXTERNAL_SAMPLE_1,             MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_EXTERNAL_SAMPLE_2,             MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_EXTERNAL_SAMPLE_3,             MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_EXTERNAL_SAMPLING_CONTROL,     MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_PAGE_REGISTER,                 MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_BYTEWISE_ADDRESS,              MT9D111_REG_PAGE_0,             0x0000},
    {MT9D111_REG_CONTEXT_CONTROL,               MT9D111_REG_PAGE_0,             0x0000}
};

#endif // MT9D111_CONFIG_H_

//! \} End of mt9d111 group
