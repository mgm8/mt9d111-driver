/*
 * mt9d111_reg.h
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
 * \file mt9d111_reg.h
 * 
 * \brief MT9D111 registers addresses.
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

#ifndef MT9D111_REG_H_
#define MT9D111_REG_H_

/**
 * \brief Sensor Core Registers Addresses.
 *
 * Reference: Table 5: Sensor Register Description; "MT9D111 - 1/3.2-Inch 2-Megapixel SOC Digital Image Sensor Registers".
 *
 * \{
 */
#define MT9D111_REG_RESERVED                        0x00    /**< Reserved register (Default value: 0x1519). */
#define MT9D111_REG_ROW_START                       0x01    /**< The first row to be read out, excluding any dark rows that may be read. To window the image down, set this register to the starting Y value. Setting a value less than 20 is not recommended because the dark rows should be read using R0x22:0. */
#define MT9D111_REG_COLUMN_START                    0x02    /**< The first column to be read out, excluding dark columns that may be read. To window the image down, set this register to the starting X value. Setting a value below 52 is not recommended because readout of dark columns should be controlled by R0x22:0. */
#define MT9D111_REG_ROW_WIDTH                       0x03    /**< Number of rows in the image to be read out, excluding any dark rows or border rows that may be read. The minimum supported value is 2. */
#define MT9D111_REG_COL_WIDTH                       0x04    /**< Number of columns in image to be read out, excluding any dark columns or border columns that may be read. The minimum supported value is 9 in 1 ADC mode and 17 in 2 ADC mode. */
#define MT9D111_REG_HORIZONTAL_BLANKING_B           0x05    /**< Number of blank columns in a row when context B is selected (R0xF2:0[0] = 1). The extra columns are added at the beginning of a row. See “Frame Rate Control” on page 128 for more information on supported register values. */
#define MT9D111_REG_VERTICAL_BLANKING_B             0x06    /**< Number of blank rows in a frame when context B is selected (R0xF2:0[1] = 1). The minimum supported value is (4 + R0x22:0[2:0]). The actual vertical blanking time may be controlled by the shutter width (R0x09:0). See “Raw Data Timing” on page 119. */
#define MT9D111_REG_HORIZONTAL_BLANKING_A           0x07    /**< Number of blank columns in a row when context A is selected (R0xF2:0[0] = 0). The extra columns are added at the beginning of a row. See “Frame Rate Control” on page 128 for more information on supported register values. */
#define MT9D111_REG_VERTICAL_BLANKING_A             0x08    /**< Number of blank rows in a frame when context A is chosen (R0xF2:0[1] = 1). The minimum supported value is (4 + R0x22:0[2:0]). The actual vertical blanking time may be controlled by the shutter width (R0x9:0). See “Raw Data Timing” on page 119. */
#define MT9D111_REG_SHUTTER_WIDTH                   0x09    /**< Integration time in number of rows. The integration time is also influenced by the shutter delay (R0x0C:0) and the overhead time. */
#define MT9D111_REG_ROW_SPEED                       0x0A    /**< . */
#define MT9D111_REG_EXTRA_DELAY                     0x0B    /**< Extra blanking inserted between frames. A programmed value of N increases the vertical blanking time by N pixel clock periods. Can be used to get a more exact frame rate. It may affect the integration times of parts of the image when the integration time is less than one frame. */
#define MT9D111_REG_SHUTTER_DELAY                   0x0C    /**< The amount of time from the end of the sampling sequence to the beginning of the pixel reset sequence. If the value in this register exceeds the row time, the reset of the row does not complete before the associated row is sampled, and the sensor does not generate an image. A programmed value of N reduces the integration time by (N/2) pixel clock periods in 1 ADC mode and by N pixel clock periods in 2 ADC mode. */
#define MT9D111_REG_RESET                           0x0D    /**< . */
#define MT9D111_REG_FRAME_VALID_CONTROL             0x1F    /**< . */
#define MT9D111_REG_READ_MODE_B                     0x20    /**< . */
#define MT9D111_REG_READ_MODE_A                     0x21    /**< . */
#define MT9D111_REG_DARK_COL_ROWS                   0x22    /**< . */
#define MT9D111_REG_FLASH                           0x23    /**< . */
#define MT9D111_REG_EXTRA_RESET                     0x24    /**< . */
#define MT9D111_REG_LINE_VALID_CONTROL              0x25    /**< . */
#define MT9D111_REG_BOTTOM_DARK_ROWS                0x26    /**< . */
#define MT9D111_REG_GREEN_1_GAIN                    0x2B    /**< . */
#define MT9D111_REG_BLUE_GAIN                       0x2C    /**< . */
#define MT9D111_REG_RED_GAIN                        0x2D    /**< . */
#define MT9D111_REG_GREEN_2_GAIN                    0x2E    /**< . */
#define MT9D111_REG_GLOBAL_GAIN                     0x2F    /**< This register can be used to simultaneously set all 4 gains. When read, it returns the value stored in R0x2B:0. */
#define MT9D111_REG_ROW_NOISE                       0x30    /**< . */
#define MT9D111_REG_BLACK_ROWS                      0x59    /**< For each bit set, the corresponding dark row (rows 0–7) are used in the black level algorithm. For this to occur, the reading of those rows must be enabled by the settings in R0x22:0. */
#define MT9D111_REG_DARK_G1_AVERAGE                 0x5B    /**< . */
#define MT9D111_REG_DARK_B_AVERAGE                  0x5C    /**< . */
#define MT9D111_REG_DARK_R_AVERAGE                  0x5D    /**< . */
#define MT9D111_REG_DARK_G2_AVERAGE                 0x5E    /**< . */
#define MT9D111_REG_CALIB_THRESHOLD                 0x5F    /**< . */
#define MT9D111_REG_CALIB_CONTROL                   0x60    /**< . */
#define MT9D111_REG_CALIB_GREEN_1                   0x61    /**< Analog calibration offset for green1 pixels, represented as a two’s complement signed 8-bit value (if bit 8 is clear, the offset is positive and the magnitude is given by bits 7:0. If bit 8 is set, the offset is negative and the magnitude is given by not ([7:0]) + 1). If R0x60:0[0] = 0, this register is R/O and returns the current value computed by the black level calibration algorithm. If R0x60:0[0] = 1, this register is R/W and can be used to set the calibration offset manually. Green1 pixels share rows with red pixels. */
#define MT9D111_REG_CALIB_BLUE                      0x62    /**< Analog calibration offset for blue pixels, represented as a two’s complement signed 8-bit value (if bit 8 is clear, the offset is positive and the magnitude is given by bits 7:0. If bit 8 is set, the offset is negative and the magnitude is given by Not ([7:0]) + 1). If R0x60:0[0] = 0, this register is R/O and returns the current value computed by the black level calibration algorithm. If R0x60:0[0] = 1, this register is R/W and can be used to set the calibration offset manually. */
#define MT9D111_REG_CALIB_RED                       0x63    /**< Analog calibration offset for red pixels, represented as a two’s complement signed 8-bit value (if bit 8 is clear, the offset is positive and the magnitude is given by bits 7:0. If bit 8 is set, the offset is negative and the magnitude is given by Not ([7:0]) + 1). If R0x60:0[0] = 0, this register is R/O and returns the current value computed by the black level calibration algorithm. If R0x60:0[0] = 1, this register is R/W and can be used to manually set the calibration offset. */
#define MT9D111_REG_CALIB_GREEN_2                   0x64    /**< Analog calibration offset for green2 pixels, represented as a two’s complement signed 8-bit value (if bit 8 is clear, the offset is positive and the magnitude is given by bits 7:0. If bit 8 is set, the offset is negative and the magnitude is given by Not ([7:0]) + 1.) If R0x60:0[0] = 0, this register is R/O and returns the current value computed by the black level calibration algorithm. If R0x60:0[0] = 1, this register is R/W and can be used to manually set the calibration offset. Green2 pixels share rows with blue pixels. */
#define MT9D111_REG_CLOCK_CONTROL                   0x65    /**< . */
#define MT9D111_REG_PLL_CONTROL_1                   0x66    /**< . */
#define MT9D111_REG_PLL_CONTROL_2                   0x67    /**< . */
#define MT9D111_REG_GLOBAL_SHUTTER_CONTROL          0xC0    /**< . */
#define MT9D111_REG_START_INTEGRATION_T1            0xC1    /**< These 16 bits are compared to the upper bits of a 24-bit counter, which starts counting master clocks when global reset starts. When this value is reached, global reset is de-asserted, and integration time starts. There is a minimum time period for which global reset is always held. This time is defined by the physical properties of the boost circuit. */
#define MT9D111_REG_START_READOUT_T2                0xC2    /**< These 16 bits are added to R0xC1:0 (start integration time) and compared to the 24-bit counter mentioned for R0xC1:0. The value defines the time from when integration time starts to when it is guaranteed to end. Readout then commences. */
#define MT9D111_REG_ASSERT_STROBE_T3                0xC3    /**< These 16 bits are compared to the upper bits of a 24-bit counter, which starts counting master clocks when global reset starts. When this value is reached, the strobe is asserted. */
#define MT9D111_REG_DEASSERT_STROBE_T4              0xC4    /**< These 16 bits are compared to the upper bits of a 24-bit counter, which starts counting master clocks when global reset starts. When this value is reached, the strobe is de-asserted if strobe control is “0” (R0xC0:0[1]). */
#define MT9D111_REG_ASSERT_FLASH                    0xC5    /**< These 16 bits are compared to the upper bits of a 24-bit counter, which starts counting master clocks when global reset starts. When this value is reached, the flash is asserted. */
#define MT9D111_REG_DEASSERT_FLASH                  0xC6    /**< These 16 bits are compared to the upper bits of a 24-bit Time counter, which starts counting master clocks when global reset starts. When this value is reached, the flash is de-asserted if flash control is “0” (R0xC0:0[2]). */
#define MT9D111_REG_EXTERNAL_SAMPLE_1               0xE0    /**< Contains sample of AIN3 if external signal sampling is enabled (R0xE3:0[15] = 1). See “Analog Inputs AIN1–AIN3” on page 134. */
#define MT9D111_REG_EXTERNAL_SAMPLE_2               0xE1    /**< Contains sample of AIN2 if external signal sampling is enabled (R0xE3:0[15] = 1). */
#define MT9D111_REG_EXTERNAL_SAMPLE_3               0xE2    /**< Contains sample of AIN1 if external signal sampling is enabled (R0xE3:0[15] = 1). */
#define MT9D111_REG_EXTERNAL_SAMPLING_CONTROL       0xE3    /**< . */
#define MT9D111_REG_PAGE_REGISTER                   0xF0    /**< Must be kept at “0” to be able to write/read from sensor. Used in SOC to access other pages with registers. */
#define MT9D111_REG_BYTEWISE_ADDRESS                0xF1    /**< Special address to perform 16-bit reads and writes to the sensor in 8-bit chunks. See “8-Bit Write Sequence” on page 183. */
#define MT9D111_REG_CONTEXT_CONTROL                 0xF2    /**< . */
#define MT9D111_REG_RESERVED_2                      0xFF    /**< Reserved register (Default value: 0x1519). */
//! \}

#endif // MT9D111_REG_H_

//! \} End of mt9d111 group
