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

#include <stdint.h>

/**
 * \struct Register
 * 
 * \brief Struct to store an register address and its value.
 */
struct Register
{
    uint8_t     address;    /**< Register address. */
    uint8_t     page;       /**< Register page number. */
    uint16_t    value;      /**< Register value. */
};

// Registers pages
#define MT9D111_REG_PAGE_0                          0   /**< Sensor core. */
#define MT9D111_REG_PAGE_1                          1   /**< IFP page 1. */
#define MT9D111_REG_PAGE_2                          2   /**< IFP page 2. */

/**
 * \brief Sensor Core Registers Addresses.
 *
 * Reference: Table 5: Sensor Register Description; "MT9D111 - 1/3.2-Inch 2-Megapixel SOC Digital Image Sensor Registers".
 *
 * \{
 */

/**
 * Bits 15:0 - Reserved: Reserved register (Default value: 0x1519).
 */
#define MT9D111_REG_RESERVED                        0x00

/**
 * Bits 10:0 - Row Start: The first row to be read out, excluding any dark rows that may be read. To window the image down, set
 * this register to the starting Y value. Setting a value less than 20 is not recommended because the dark rows should be read
 * using R0x22:0.
 */
#define MT9D111_REG_ROW_START                       0x01

/**
 * Bits 10:0 - Column Start: The first column to be read out, excluding dark columns that may be read. To window the image down,
 * set this register to the starting X value. Setting a value below 52 is not recommended because readout of dark columns should
 * be controlled by R0x22:0.
 */
#define MT9D111_REG_COLUMN_START                    0x02

/**
 * Bits 10:0 - Row Width: Number of rows in the image to be read out, excluding any dark rows or border rows that may be read.
 * The minimum supported value is 2.
 */
#define MT9D111_REG_ROW_WIDTH                       0x03

/**
 * Bits 10:0 - Columns Width: Number of columns in image to be read out, excluding any dark columns or border columns that may
 * be read. The minimum supported value is 9 in 1 ADC mode and 17 in 2 ADC mode.
 */
#define MT9D111_REG_COL_WIDTH                       0x04

/**
 * Bits 13:0 - Horizontal Blanking-Context B: Number of blank columns in a row when context B is selected (R0xF2:0[0] = 1).
 * The extra columns are added at the beginning of a row. See “Frame Rate Control” on page 128 for more information on supported
 * register values.
 */
#define MT9D111_REG_HORIZONTAL_BLANKING_B           0x05

/**
 * Bits 14:0 - Vertical Blanking Context B: Number of blank rows in a frame when context B is selected (R0xF2:0[1] = 1).
 * The minimum supported value is (4 + R0x22:0[2:0]). The actual vertical blanking time may be controlled by the shutter width (R0x09:0).
 * See “Raw Data Timing” on page 119.
 */
#define MT9D111_REG_VERTICAL_BLANKING_B             0x06

/**
 * Bits 13:0 - Horizontal Blanking-Context A: Number of blank columns in a row when context A is selected (R0xF2:0[0] = 0).
 * The extra columns are added at the beginning of a row. See “Frame Rate Control” on page 128 for more information on supported
 * register values.
 */
#define MT9D111_REG_HORIZONTAL_BLANKING_A           0x07

/**
 * Bits 14:0 - Vertical Blanking-Context A: Number of blank rows in a frame when context A is chosen (R0xF2:0[1] = 1).
 * The minimum supported value is (4 + R0x22:0[2:0]). The actual vertical blanking time may be controlled by the shutter width (R0x9:0).
 * See “Raw Data Timing” on page 119.
 */
#define MT9D111_REG_VERTICAL_BLANKING_A             0x08

/**
 * Bits 15:0 - Shutter Width: Integration time in number of rows. The integration time is also influenced by the shutter delay
 * (R0x0C:0) and the overhead time.
 */
#define MT9D111_REG_SHUTTER_WIDTH                   0x09

/**
 * Bits 15:14 - Reserved: Do not change from default value.
 *
 * Bit 13 - Reserved: Do not change from default value.
 *
 * Bit 8 - Invert Pixel Clock: Invert PIXCLK. When clear, FRAME_VALID, LINE_VALID, and D_OUT are set up relative to the delayed
 * rising edge of PIXCLK. When set, FRAME_VALID, LINE_VALID, and D_OUT are set up relative to the delayed falling edge of PIXCLK.
 *
 * Bit 7:4 - Delay Pixel Clock: Number of half master clock cycle increments to delay the rising edge of PIXCLK relative to
 * transitions on FRAME_VALID, LINE_VALID, and D_OUT.
 *
 * Bit 3 - Reserved: Do not change from default value.
 *
 * Bits 2:0 - Pixel Clock Speed: A programmed value of N gives a pixel clock period of N master clocks in 2 ADC mode and 2*N
 * master clocks in 1 ADC mode. A value of "0" is treated like (and reads back as) a value of "1".
 */
#define MT9D111_REG_ROW_SPEED                       0x0A

/**
 * Bits 13:0 - Extra Delay: Extra blanking inserted between frames. A programmed value of N increases the vertical blanking time
 * by N pixel clock periods. Can be used to get a more exact frame rate. It may affect the integration times of parts of the
 * image when the integration time is less than one frame.
 */
#define MT9D111_REG_EXTRA_DELAY                     0x0B

/**
 * Bits 13:0 - Shutter Delay: The amount of time from the end of the sampling sequence to the beginning of the pixel reset sequence.
 * If the value in this register exceeds the row time, the reset of the row does not complete before the associated row is sampled,
 * and the sensor does not generate an image. A programmed value of N reduces the integration time by (N/2) pixel clock periods in
 * 1 ADC mode and by N pixel clock periods in 2 ADC mode.
 */
#define MT9D111_REG_SHUTTER_DELAY                   0x0C

/**
 * Bit 15 - Synchronize Changes: By default, update of many registers are synchronized to frame start. Setting this bit inhibits
 * this update; register changes remain pending until this bit is returned to "0". When this bit is returned to “0,” all pending
 * register updates are made on the next frame start.
 *
 * Bit 10 - Toggle S_ADDR: By default, the sensor serial bus responds to addresses 0xBA and 0xBB. When this bit is set, the sensor
 * serial bus responds to addresses 0x90 and 0x91. WRITEs to this bit are ignored when STANDBY is asserted. See "Slave Address"
 * on page 181.
 *
 * Bit 9 - Restart Bad Frames: When set, a restart is forced to take place whenever a bad frame is detected. This can shorten the
 * delay when waiting for a good frame because the delay, when masking out a bad frame, is the integration time rather than the
 * full frame time.
 *
 * Bit 8 - Show Bad Frames: 1 - Output all frames (including bad frames).
 *                          0 - Only output good frames (default). A bad frame is defined as the first frame following a change to:
 *                          window size or position, horizontal blanking, pixel clock speed, zoom, row or column skip, binning,
 *                          mirroring, or use of border.
 *
 * Bits 7:6 - Inhibit Standby/Drive Pins: 00 or 01 - setting STANDBY high puts sensor into standby state with high-impedance outputs.
 *                                        10 - setting STANDBY high only puts the outputs in High-Z.
 *                                        11 - causes STANDBY to be ignored.
 *
 * Bit 5 - Reset SOC: When this bit is set to 1, SOC is put in reset state. It exits this state when the bit is set back to 0. Any
 * attempt to access SOC registers (IFP page 1 and 2) in the reset state results in a sensor hang-up. The sensor cannot recover
 * from it without a hard reset or power cycle.
 *
 * Bit 4 - Output Disable: Setting this bit to 1 puts the pin interface in a High-Z. See "Output Enable Control" on page 153.
 * If the D OUT *, PIXCLK, Frame_Valid, or Line_Valid is floating during STANDBY, this bit should be set to “0” to turn off the
 * input buffer, reducing standby current (see technical note TN0934 "Standby Sequence"). This bit must work together with bit 6
 * to take effect.
 *
 * Bit 3 - Reserved: Keep at default value.
 *
 * Bit 2 - Standby: Setting this bit to 1 places the sensor in a low-power state. Any attempt to access registers R[0xF7:0xFD]:0
 * in this state results in a sensor hang-up. The sensor cannot recover from it without a hard reset or power cycle.
 *
 * Bit 1 - Restart: Setting this bit causes the sensor to truncate the current frame and start resetting the first row.
 * The delay before the first valid frame is read out is equal to the integration time. This bit is write - 1 but always
 * reads back as 0.
 *
 * Bit 0 - Reset: Setting this bit puts the sensor in reset; the frame being generated is truncated and the pin interface goes
 * to an idle state. All internal registers (except for this bit) go to the default power-up state. Clearing this bit resumes
 * normal operation.
 */
#define MT9D111_REG_RESET                           0x0D

/**
 * Bit 15 - Enable early FRAME_VALID Fall: 1 - Enables the early disabling of FRAME_VALID as set in bits 14:8. LINE_VALID
 * is still generated for all active rows.
 *                                         0 - Default. FRAME_VALID goes low 6 pixel clocks after last LINE_VALID.
 *
 * Bits 14:8 - Early FRAME_VALID Fall: When enabled, the FRAME_VALID falling edge occurs within the programmed number of rows
 * before the end of the last LINE_VALID. (1 + bits 14:8)*row time + constant (constant = 3 in default mode) The value of this
 * field must not be larger than row width R0x03:0.
 *
 * Bit 7 - Enable Early FRAME_VALID Rise: 1 - Enables the early rise of FRAME_VALID as set in bits 6:0.
 *                                        0 - Default. FRAME_VALID goes HIGH 6 pixel clocks before first LINE_VALID.
 *
 * Bits 6:0 - Binning-Context B: When enabled, the FRAME_VALID rising edge is set HIGH the programmed number of rows before the first
 * LINE_VALID: (1 + bits 6:0)*row time + horizontal blank + constant (constant = 3 in default mode).
 */
#define MT9D111_REG_FRAME_VALID_CONTROL             0x1F

/**
 * Bit 15 - Binning-Context B: When read mode context B is selected (R0xF2:0[3] = 1):
 *                             0 - Normal operation.
 *                             1 - Binning enabled. See "Binning" on page 127 and See “Frame Rate Control” on page 128 for
 *                             a full description.
 * 
 * Bit 13 - Zoom Enable: 0 - Normal operation.
 *                       1 - Zoom is enabled, with zoom factor [zoom] defined in bits 12:11.
 *                       In zoom mode, the pixel data rate is slowed by a factor of [zoom]. This is achieved by outputting
 * [zoom - 1] blank rows between each output row. Setting this mode allowsthe user to fill a window that is [zoom] times larger with
 * interpolated data. The pixel clock speed is not affected by this operation, and the output data for each pixel is valid for
 * [zoom] pixel clocks. Every row is followed by [zoom - 1] blank rows (with their own LINE_VALID, but all data bits = 0) of equal time.
 * The combination of this register and an appropriate change to the window sizing registers allows the user to zoom to a region
 * of interest without affecting the frame rate.
 *
 * Bits 12:11 - Zoom: When zoom is enabled by bit 13, this field determines the zoom amount:
 *                    00 - Zoom 2x
 *                    01 - Zoom 4x
 *                    10 - Zoom 8x
 *                    11 - Zoom 16x
 *
 * Bit 10 - Use 1 ADC-Context B: When read mode context B is selected (bit 3, R0xF2:0 = 1):
 *                               0 - Use both ADCs to achieve maximum speed.
 *                               1 - Use 1 ADC to reduce power. Maximum readout frequency is now half the master clock frequency, and the
 *                               pixel clock is automatically adjusted as described for the pixel clock speed register.
 *
 * Bit 9 - Show Border: This bit indicates whether to show the border enabled by bit 8.
 *                      0 - Border is enabled but not shown; vertical blanking is increased by 8 rows and horizontal blanking is
 *                      increased by 8 pixels.
 *                      1 - border is enabled and shown; FRAME_VALID time is extended by 8 rows and LINE_VALID is extended by 8 pixels.
 *                      See “Pixel Border” on page 124.
 *
 * Bit 8 - Over Sized: 0 - Normal UXGA size.
 *                     1 - Adds a 4-pixel border around the active image array independent of readout mode (skip, zoom, mirror, etc.).
 *                     Setting this bit adds 8 to the number of rows and columns in the frame.
 *
 * Bit 7 - Column Skip Enable-Context B: When read mode context B is selected (R0xF2:0[3] = 1):
 *                                       1 - Enable column skip.
 *                                       0 - Normal readout.
 *
 * Bits 6:5 - Column Skip-Context B: When read mode context B is selected (R0xF2:0[3] = 1) and column skip is enabled (bit 7 = 1):
 *                                   00 - Column Skip 2x
 *                                   01 - Column Skip 4x
 *                                   10 - Column Skip 8x
 *                                   11 - Column Skip 16x
 *                                   See "Column and Row Skip" on page 125 for more information.
 *
 * Bit 4 - Row Skip Enable-Context B: When read mode context B is selected (R0xF2:0[3] = 1):
 *                                    1 - Enable row skip.
 *                                    0 - Normal readout.
 * 
 * Bits 3:2 - Row Skip-Context B: When read mode context B is selected (R0xF2:0[3] = 1) and Row skip is enabled (bit 4 = 1):
 *                                00 - Row Skip 2x
 *                                01 - Row Skip 4x
 *                                10 - Row Skip 8x
 *                                11 - Row Skip 16x
 *                                See "Column and Row Skip" on page 125 for more information.
 * 
 * Bit 1 - Mirror Columns: Read out columns from right to left (mirrored). When set, column readout starts from column (column
 * start + column size) and continues down to (column start + 1). When clear, readout starts at column start and continues to (column
 * start + column size - 1). This ensures that the starting color is maintained.
 *
 * Bit 0 - Mirror Rows: Read out rows from bottom to top (upside down). When set, row readout starts from row (row start + row size) and
 * continues down to (row start + 1). When clear, readout starts at row start and continues to (row start + row size -1).
 * This ensures that the starting color is maintained.
 */
#define MT9D111_REG_READ_MODE_B                     0x20

/**
 * Bit 15 - Binning-Context A: When read mode context A is selected (R0xF2:0[3] = 0):
 *                             0 - Normal operation.
 *                             1 - Binning enabled. See "Binning" on page 127.
 *
 * Bit 10 - Use 1 ADC-Context A: When read mode context A is selected (R0xF2:0[3] = 0):
 *                               0 - Use both ADCs to achieve maximum speed.
 *                               1 - Use one ADC to reduce power. Maximum readout frequency is now half of the master clock, and the pixel
 *                               clock is automatically adjusted as described for the pixel clock speed register.
 *
 * Bit 7 - Column Skip Enable-Context A: When read mode context A is selected (R0xF2:0[3] = 0):
 *                                       1 - Enable column skip.
 *                                       0 - Normal readout.
 *
 * Bits 6:5 - Columns Skip-Context A: When read mode context A is selected (R0xF2:0[3] = 0) and column skip is enabled (bit 7 = 1):
 *                                    00 - Column Skip 2x
 *                                    01 - Column Skip 4x
 *                                    10 - Column Skip 8x
 *                                    11 - Column Skip 16x
 *                                    See "Column and Row Skip" on page 125 for more information.
 *
 * Bit 4 - Row Skip Enalbe-Context A: When read mode context A is selected (R0xF2:0[3] = 0):
 *                                    1 - Enable row skip.
 *                                    0 - Normal readout.
 *
 * Bits 3:2 - Row Skip-Context A: When read mode context A is selected (R0xF2:0[3] = 0) and Row skip is enabled (bit 4 = 1):
 *                                00 - Row Skip 2x
 *                                01 - Row Skip 4x
 *                                10 - Row Skip 8x
 *                                11 - Row Skip 16x
 *                                See "Column and Row Skip" on page 125 for more information.
 *
 */
#define MT9D111_REG_READ_MODE_A                     0x21

/**
 * Bit 10 - Number of Dark Columns: The MT9D111 has 40 dark columns. 1 - Read out 36 dark columns (4-39). Ignored during binning,
 *                                  where all 40 dark columns are used. 0 - Read out 20 dark columns (4-23).
 *
 * Bit 9 - Show Dark Columns: When set, the 20/36 (dependent on bit 10) dark columns are output before the active pixels in a line.
 *                            There is an idle period of 2 pixels between readout of the dark columns and readout of the active image.
 *                            Therefore, when set, LINE_VALID is asserted 22 pixel times earlier than normal, and the horizontal blanking
 *                            time is decreased by the same amount.
 *
 * Bit 8 - Read Dark Columns: 1 - Enables the readout of dark columns for use in the row-wise noise correction algorithm. The number
 *                                of columns used are 40 in binning mode, and otherwise determined by bit 10.
 *
 * Bit 7 - Show Dark Rows: When set, the programmed dark rows is output before the active window. FRAME_VALID is thus asserted earlier than
 *                         normal. This has no effect on integration time or frame rate.
 *
 * Bit 6:4 - Dark Start Address: The start address for the dark rows within the 8 available rows (an offset of 4 is added to compensate
 *                               for the guard pixels). Must be set so all dark rows read out falls in the address space 0:7.
 * 
 * Bit 3 - Reserved: Do not change from default value.
 *
 * Bits 2:0 - Num Dark Rows: A value of N causes (n + 1) dark rows to be read out at the start of each frame when dark row readout is
 *                           enabled (bit 3).
 */
#define MT9D111_REG_DARK_COL_ROWS                   0x22

/**
 * Bit 15 - FLASH: Reflects the current state of FLASH output.
 *
 * Bit 14 - Triggered: Indicates that FLASH output is asserted for the current frame.
 *
 * Bit 13 - Xenon Flash: Enable Xenon flash. When set, FLASH output asserts for the programmed period (bits 7:0) during vertical blanking.
 *                       This is achieved by keeping the integration time equal to one frame, and the pulse width less than the vertical
 *                       blank time.
 *
 * Bits 12:11 - Frame Delay: Delay of the flash pulse measured in frames.
 *
 * Bit 10 - End of Reset: 1 - In Xenon mode the flash is triggered after the resetting of a frame.
 *                        0 - In Xenon mode the flash is triggered after the readout of a frame.
 *
 * Bit 9 - Every Frame: 1 - Flash should be enabled every frame.
 *                      0 - Flash should be enabled for one frame only.
 *
 * Bit 8 - LED Flash: Enable LED flash. When set, FLASH output asserts prior to the start of the resetting of a frame and remains asserted
 *                    until the end of the readout of the frame.
 *
 * Bits 7:0 - Xenon Count: Length of FLASH pulse when Xenon flash is enabled. The value specifies the length in units of 1024*PIXCLK cycle
 *                         increments. When the Xenon count is set to its maximum value (0xFF), the FLASH pulse is automatically truncated
 *                         prior to the readout of the first row, giving the longest pulse possible.
 */
#define MT9D111_REG_FLASH                           0x23

/**
 * Bit 15 - Extra Reset Enable: 0 - Only programmed window (set by R0x01:0 through R0x04:0) and black pixels are read.
 *                              1 - Two additional rows are read and reset above and below programmed window to prevent blooming to active
 *                              area.
 *
 * Bit 14 - Next Row Reset: When set, and the integration time is less than one frame time, row (n + 1) is reset immediately prior to
 *                          resetting row (n). This is intended to prevent blooming across rows under conditions of very high illumination.
 *
 * Bits 13:0 - Reserved: Do not change from default value.
 */
#define MT9D111_REG_EXTRA_RESET                     0x24

/**
 * Bit 15 - Xor LINE_VALID: 1 - LINE_VALID = "continuous" LINE_VALID XOR FRAME_VALID.
 *                          0 - Normal LINE_VALID (default, no XORing of LINE_VALID). Ineffective if continuous LINE_VALID is set.
 * 
 * Bit 14 - Continuous LINE_VALID: 1 - "Continuous" LINE_VALID (continue producing LINE_VALID during vertical blanking).
 *                                 0 - Normal LINE_VALID (default, no LINE_VALID during vertical blanking).
 */
#define MT9D111_REG_LINE_VALID_CONTROL              0x25

/**
 * Bit 7 - Show: The bottom dark rows are visible in the image if the bit is set.
 *
 * Bits 6:4 - Start Address: Defines the start address within the 8 bottom dark rows.
 *
 * Bit 3 - Enable Readout: Enable readout of the bottom dark rows.
 *
 * Bits 2:0 - Number of Dark Rows: Defines the number of bottom dark rows to be used. (The number of rows used is
 *                                 the specified value + 1.)
 */
#define MT9D111_REG_BOTTOM_DARK_ROWS                0x26

/**
 * Bits 11:9 - Digital Gain: Total gain = (bit 9 + 1)*(bit 10 + 1)*(bit 11 + 1)*analog gain (each bit gives 2x gain).
 *
 * Bits 8:7 - Analog Gain: Analog gain = (bit 8 + 1)*(bit 7 + 1)*initial gain (each bit gives 2x gain).
 *
 * Bits 6:0 - Initial Gain: Initial gain = bits 6:0*0.03125.
 */
#define MT9D111_REG_GREEN_1_GAIN                    0x2B

/**
 * Bits 11:9 - Digital Gain: Total gain = (bit 9 + 1)*(bit 10 + 1)*(bit 11 + 1)*analog gain (each bit gives 2x gain).
 *
 * Bits 8:7 - Analog Gain: Analog gain = (bit 8 + 1)*(bit 7 + 1)*initial gain (each bit gives 2x gain).
 *
 * Bits 6:0 - Initial Gain: Initial gain = bits [6:0]*0.03125.
 */
#define MT9D111_REG_BLUE_GAIN                       0x2C

/**
 * Bits 11:9 - Digital Gain: Total gain = (bit 9 + 1)*(bit 10] + 1)*(bit 11 + 1)*analog gain (each bit gives 2x gain).
 *
 * Bits 8:7 - Analog Gain: Analog gain = (bit 8 + 1)*(bit 7 + 1)*initial gain (each bit gives 2x gain).
 *
 * Bits 6:0 - Initial Gain: Initial gain = bits 6:0*0.03125.
 */
#define MT9D111_REG_RED_GAIN                        0x2D

/**
 * Bits 11:9 - Digital Gain: Total gain = (bit 9 + 1)*(bit 10 + 1)*(bit 11 + 1)*analog gain (each bit gives 2x gain).
 *
 * Bits 8:7 - Analog Gain: Analog gain = (bit 8 + 1)*(bit 7 + 1)*initial gain (each bit gives 2x gain).
 *
 * Bits 6:0 - Initial Gain: Initial gain = bits 6:0*0.03125.
 */
#define MT9D111_REG_GREEN_2_GAIN                    0x2E

/**
 * This register can be used to simultaneously set all 4 gains. When read, it returns the value stored in R0x2B:0.
 */
#define MT9D111_REG_GLOBAL_GAIN                     0x2F

/**
 * Bit 15 - Frame-wise Digital Correction: By default, the row noise is calculated and compensated for individually
 *                                         for each color of each row. When this bit is set, the row noise is calculated
 *                                         and applied for each color of each of the first two 2 (two pairs of values) and
 *                                         the same values are applied to each subsequent row, so that new values are
 *                                         calculated and applied once per frame.
 *
 * Bits 14:12 - Gain Threshold: When the upper analog gain bits are equal to or larger than this threshold, the dark
 *                              column average is used in the row noise correction algorithm. Otherwise, the subtracted
 *                              value is determined by bit 11. This check is independently performed for each color, and
 *                              is a means to turn off the black level algorithm for lower gains.
 *
 * Bit 11 - Use Black Level Average: 1 - Use black level frame average from the dark rows in the row noise correction
 *                                       algorithm for low gains. This frame average was taken before the last adjustment
 *                                       of the offset DAC for that frame, so it might be slightly off.
 *                                   0 - Use mean of black level programmed threshold in the row noise correction algorithm
 *                                       for low gains.
 *
 * Bit 10 - Enable Correction: 1 - Enable row noise cancellation algorithm. When this bit is set, the average value of the
 *                                 dark columns read out is used as a correction for the whole row. The dark average is
 *                                 subtracted from each pixel on the row, and then a constant is added (bits 9:0).
 *                             0 - Normal operation.
 *
 * Bits 9:0 - Row Noise Constant: Constant used in the row noise cancellation algorithm. It should be set to the dark level
 *                                targeted by the black level algorithm plus the noise expected between the averaged values
 *                                of the dark columns. The default constant is set to 42 LSB.
 */
#define MT9D111_REG_ROW_NOISE                       0x30

/**
 * For each bit set, the corresponding dark row (rows 0–7) are used in the black level algorithm.
 * For this to occur, the reading of those rows must be enabled by the settings in R0x22:0.
 */
#define MT9D111_REG_BLACK_ROWS                      0x59

/**
 * Bits 6:0 - Green1 Frame Average: The frame-averaged green1 black level that is used in the black level calibration algorithm.
 */
#define MT9D111_REG_DARK_G1_AVERAGE                 0x5B

/**
 * Bits 6:0 - Blue Frame Average: The frame-averaged blue black level that is used in the black level calibration algorithm.
 */
#define MT9D111_REG_DARK_B_AVERAGE                  0x5C

/**
 * Bits 6:0 - Red Frame Average: The frame-averaged red black level that is used in the black level calibration algorithm.
 */
#define MT9D111_REG_DARK_R_AVERAGE                  0x5D

/**
 * Bits 6:0 - Green2 Frame Average: The frame-averaged green2 black level that is used in the black level calibration algorithm.
 */
#define MT9D111_REG_DARK_G2_AVERAGE                 0x5E

/**
 * Bits 14:8 - Upper Threshold: Upper threshold for targeted black level in ADC LSBs.
 *
 * Bits 6:0 - Lower Threshold: Lower threshold for targeted black level in ADC LSBs.
 */
#define MT9D111_REG_CALIB_THRESHOLD                 0x5F

/**
 * Bit 15 - Disable Rapid Sweep Mode: Disables the rapid sweep mode in the black level algorithm. The averaging mode remains enabled.
 *
 * Bit 12 - Recalculate: When set, the rapid sweep mode is triggered if enabled, and the running frame average is reset to the
 *                       current frame average. This bit is write - 1, but always reads back as "0".
 *
 * Bit 10 - Limit Rapid Sweep: 1 - Dark rows 8–11 are not used for the black level algorithm controlling the calibration value.
 *                                 Instead, these rows are used to calculate dark averages that can be a starting point for the
 *                                 digital frame-wise black level algorithm.
 *                             0 - All dark rows can be used for the black level algorithm. This means that the internal average
 *                                 might not correspond to the calibration value used for the frame, so the dark row average should
 *                                 in this case not be used as the starting point for the frame-wise black level algorithm.
 *
 * Bit 9 - Freeze Calibration: When set, does not let the averaging mode of the black level algorithm change the calibration value.
 *                             Use this with the feature in the frame-wise black level algorithm that allows you to trigger the rapid
 *                             sweep mode when the dark column average gets away from the black level target.
 *
 * Bit 8 - Sweep Mode: When set, the calibration value is increased by one every frame, and all channels are the same. This can be
 *                     used to get a ramp input to the ADC from the calibration DACs.
 *
 * Bits 7:5 - Frames To Average Over: Two to the power of this value determines how many frames to average when the black level
 *                                    algorithm is in the averaging mode. In this mode, the running frame average is calculated from
 *                                    the following formula: Running frame ave = old running frame ave (old running frame ave)/2^n +
 *                                    (new frame ave)/ 2^n .
 *
 * Bit 4 - Step Size Forced To 1: When set, the step size is forced to 1 for the rapid sweep algorithm. Default operation (0) is to
 *                                start at a higher step size when in rapid sweep mode, to converge faster to the correct value
 *
 * Bit 3 - Switch Calibration Values: When set, the calibration values applied to the two channels are switched. This is not
 *                                    recommended and should not be used.
 *
 * Bit 2 - Same Red/Blue: When this bit is set, the same calibration value is used for red and blue pixels: Calib blue = calib red.
 *
 * Bit 1 - Same Green: When this bit is set, the same calibration value is used for all green pixels: Calib green2 = calib green1.
 *
 * Bit 0 - Manual Override: Manual override of black level correction.
 *                          1 - Override automatic black level correction with programmed values. (R0x61:0–R0x64:0).
 *                          0 - Normal operation (default).
 */
#define MT9D111_REG_CALIB_CONTROL                   0x60

/**
 * Analog calibration offset for green1 pixels, represented as a two’s complement signed 8-bit value (if bit 8 is clear,
 * the offset is positive and the magnitude is given by bits 7:0. If bit 8 is set, the offset is negative and the magnitude
 * is given by not ([7:0]) + 1). If R0x60:0[0] = 0, this register is R/O and returns the current value computed by the black
 * level calibration algorithm. If R0x60:0[0] = 1, this register is R/W and can be used to set the calibration offset manually.
 * Green1 pixels share rows with red pixels.
 */
#define MT9D111_REG_CALIB_GREEN_1                   0x61

/**
 * Analog calibration offset for blue pixels, represented as a two’s complement signed 8-bit value (if bit 8 is clear,
 * the offset is positive and the magnitude is given by bits 7:0. If bit 8 is set, the offset is negative and the magnitude
 * is given by Not ([7:0]) + 1). If R0x60:0[0] = 0, this register is R/O and returns the current value computed by the black
 * level calibration algorithm. If R0x60:0[0] = 1, this register is R/W and can be used to set the calibration offset manually.
 */
#define MT9D111_REG_CALIB_BLUE                      0x62

/**
 * Analog calibration offset for red pixels, represented as a two’s complement signed 8-bit value (if bit 8 is clear,
 * the offset is positive and the magnitude is given by bits 7:0. If bit 8 is set, the offset is negative and the magnitude
 * is given by Not ([7:0]) + 1). If R0x60:0[0] = 0, this register is R/O and returns the current value computed by the black
 * level calibration algorithm. If R0x60:0[0] = 1, this register is R/W and can be used to manually set the calibration offset.
 */
#define MT9D111_REG_CALIB_RED                       0x63

/**
 * Analog calibration offset for green2 pixels, represented as a two’s complement signed 8-bit value (if bit 8 is clear,
 * the offset is positive and the magnitude is given by bits 7:0. If bit 8 is set, the offset is negative and the magnitude
 * is given by Not ([7:0]) + 1.) If R0x60:0[0] = 0, this register is R/O and returns the current value computed by the black
 * level calibration algorithm. If R0x60:0[0] = 1, this register is R/W and can be used to manually set the calibration offset.
 * Green2 pixels share rows with blue pixels.
 */
#define MT9D111_REG_CALIB_GREEN_2                   0x64

/**
 * Bit 15 - PLL Bypass: 1 - Bypass the PLL. Use CLKIN input signal as master clock.
 *                      0 - Use clock produced by PLL as master clock.
 *
 * Bit 14 - PLL Power-Down: 1 - Keep PLL in power-down to save power (default).
 *                          0 - PLL powered-up.
 *
 * Bit 13 - Power-Down PLL During Standby: This register only has an effect when bit 14 = 0.
 *                                         1 - Turn off PLL (power-down) during standby to save power (default).
 *                                         0 - PLL powered-up during standby.
 *
 * Bit 2 - clk_newrow: Force clk_newrow to be on continuously.
 *
 * Bit 1 - clk_newframe: Force clk_newframe to be on continuously.
 *
 * Bit 0 - clk_ship: Force clk_ship to be on continuously.
 */
#define MT9D111_REG_CLOCK_CONTROL                   0x65

/**
 * Bits 15:8 - M: M value for PLL must be 16 or higher.
 *
 * Bits 5:0 - N: N value for PLL.
 */
#define MT9D111_REG_PLL_CONTROL_1                   0x66

/**
 * Bits 11:8 - Reserved: Do not change from default value.
 *
 * Bits 6:0 - P: P value for PLL.
 */
#define MT9D111_REG_PLL_CONTROL_2                   0x67

/**
 * Bit 15 - Global Reset Enable: Enter global reset. This bit is write - 1 only and is always read 0.
 *
 * Bit 2 - Global Reset Flash Control: 1 - Flash is de-asserted at end of readout.
 *                                     0 - Flash is de-asserted by R0xB6:0 (de-assert flash).
 *
 * Bit 1 - Global Reset Strobe Control: 1 - Strobe is de-asserted at end of readout.
 *                                      0 - Strobe is de-asserted by R0xC4:0 (de-assert strobe).
 *
 * Bit 0 - Global Reset Readout Control: 1 - Start of readout is controlled by falling edge of GRST_CTR.
 *                                       0 - Start of readout is controlled by R0xC2:0 (start readout time).
 */
#define MT9D111_REG_GLOBAL_SHUTTER_CONTROL          0xC0

/**
 * These 16 bits are compared to the upper bits of a 24-bit counter, which starts counting master clocks when global reset starts.
 * When this value is reached, global reset is de-asserted, and integration time starts. There is a minimum time period for which
 * global reset is always held. This time is defined by the physical properties of the boost circuit.
 */
#define MT9D111_REG_START_INTEGRATION_T1            0xC1

/**
 * These 16 bits are added to R0xC1:0 (start integration time) and compared to the 24-bit counter mentioned for R0xC1:0.
 * The value defines the time from when integration time starts to when it is guaranteed to end. Readout then commences.
 */
#define MT9D111_REG_START_READOUT_T2                0xC2

/**
 * These 16 bits are compared to the upper bits of a 24-bit counter, which starts counting master clocks when global reset starts.
 * When this value is reached, the strobe is asserted.
 */
#define MT9D111_REG_ASSERT_STROBE_T3                0xC3

/**
 * These 16 bits are compared to the upper bits of a 24-bit counter, which starts counting master clocks when global reset starts.
 * When this value is reached, the strobe is de-asserted if strobe control is "0" (R0xC0:0[1]).
 */
#define MT9D111_REG_DEASSERT_STROBE_T4              0xC4

/**
 * Bits 15:0 - Assert Flash Time: These 16 bits are compared to the upper bits of a 24-bit counter, which starts counting master
 * clocks when global reset starts. When this value is reached, the flash is asserted.
 */
#define MT9D111_REG_ASSERT_FLASH                    0xC5

/**
 * Bits 15:0 - De-assert Flash Time: These 16 bits are compared to the upper bits of a 24-bit Time counter, which starts counting
 * master clocks when global reset starts. When this value is reached, the flash is de-asserted if flash control is "0" (R0xC0:0[2]).
 */
#define MT9D111_REG_DEASSERT_FLASH                  0xC6

/**
 * Bit 9:0 - AIN3 Sample: Contains sample of AIN3 if external signal sampling is enabled (R0xE3:0[15] = 1).
 * See "Analog Inputs AIN1–AIN3" on page 134.
 */
#define MT9D111_REG_EXTERNAL_SAMPLE_1               0xE0

/**
 * Bits 9:0 - AIN2 Sample: Contains sample of AIN2 if external signal sampling is enabled (R0xE3:0[15] = 1).
 */
#define MT9D111_REG_EXTERNAL_SAMPLE_2               0xE1

/**
 * Bits 9:0 - AIN1 Sample: Contains sample of AIN1 if external signal sampling is enabled (R0xE3:0[15] = 1).
 */
#define MT9D111_REG_EXTERNAL_SAMPLE_3               0xE2

/**
 * Bit 15  - Enable Sampling: 1 - Enable external signal sampling.
 *                            0 - Disable external signal sampling.
 *
 * Bit 14 - Show Sample: If external sampling is enabled (R0xE3:0[15] = 1):
 *                       1 - Show external signal samples in the data stream after LINE_VALID goes LOW.
 *                       0 - Don’t show external signal samples in data stream.
 */
#define MT9D111_REG_EXTERNAL_SAMPLING_CONTROL       0xE3

/**
 * Bits 2:0 - Page Register: Must be kept at "0" to be able to write/read from sensor. Used in SOC to access other pages with
 * registers.
 */
#define MT9D111_REG_PAGE_REGISTER                   0xF0

/**
 * Bits 15:0 - Bytewise Address: Special address to perform 16-bit reads and writes to the sensor in 8-bit chunks.
 * See "8-Bit Write Sequence" on page 183.
 */
#define MT9D111_REG_BYTEWISE_ADDRESS                0xF1

/**
 * Bit 15 - Restart: Setting this bit causes the sensor to abandon the current frame and start resetting the first row.
 * Same physical register as R0x0D:0[1].
 *
 * Bit 7 - Xenon Flash Enable: Enable Xenon flash. Same physical register as R0x23:0[13].
 *
 * Bit 3 - Read Mode Select: 1 - Use read mode context B, R0x20:0.
 *                           0 - Use read mode context A, R0x21:0. Bits only found in read mode context B register are always
 *                           taken from that register.
 *
 * Bit 2 - LED Flash Enable: Enable LED flash. Same physical register as R0x23:0[8].
 *
 * Bit 1 - Vertical Blank Select: 1 - Use vertical blanking context B, R0x06:0.
 *                                0 - Use vertical blanking context A, R0x08:0.
 *
 * Bit 0 - Horizontal Blank Select: 1 - Use horizontal blanking context B, R0x05:0.
 *                                  0 - Use horizontal blanking context A, R0x07:0.
 */
#define MT9D111_REG_CONTEXT_CONTROL                 0xF2

/**
 * Bits 15:0 - Reserved: Reserved register (Default value: 0x1519).
 */
#define MT9D111_REG_RESERVED_2                      0xFF
//! \}

/**
 * \brief IFP Registers, Page 1.
 *
 * Reference: Table 6: IFP Registers, Page 1; "MT9D111 - 1/3.2-Inch 2-Megapixel SOC Digital Image Sensor Registers".
 * \{
 */

/**
 * Bit 0 - Toggles the assumption about Bayer CFA (vertical shift).
 *         0 - row containing Blue comes first.
 *         1 - row with Red comes first.
 *
 * Bit 1 - Toggles the assumption about Bayer CFA (horizontal shift).
 *         0 - Green comes first.
 *         1 - Red or Blue comes first.
 *
 * Bit 2 - 1 = enable lens shading correction.
 *
 * Bit 3 - 1 = enable on-the-fly defect correction.
 *
 * Bit 4 - 1 = enable 2D aperture correction.
 *
 * Bit 5 - 1 = enable color correction.
 *         0 = bypass color correction (unity color matrix).
 *
 * Bit 6 - 1 = invert output pixel clock (in all modes - JPEG, SOC, sensor).
 *
 * Bit 7 - 1 = enable gamma correction.
 *
 * Bit 8 - 1 = enable decimator.
 *
 * Bit 9 - 1 = enable minblank. Allows len generation 2 lines earlier. Also adds 4 pixels to the line size.
 *
 * Bit 10 - 1 = enable 1D aperture correction.
 */
#define MT9D111_REG_COLOR_PIPELINE_CONTROL                                                      0x08

/**
 * Bits 1:0 - Data output bypass. Selects data going to D OUT pads.
 *            00 = 10-bit sensor.
 *            01 = SOC.
 *            10 = JPEG and output FIFO (no bypass). Reg16 and Reg17 (Page 2) have to be set to the correct output frame size.
 *            11 = Reserved.
 *
 * Bit 2 - Reserved.
 *
 * Bits 4:3 - GPIO output bypass.
 *            00 = GPIO.
 *            01 = FLASH is output on GPIO11.
 *            10 = Reserved.
 *            11 = Reserved.
 */
#define MT9D111_REG_FACTORY_BYPASS                                                              0x09

/**
 * Bits 2:0 - In bypass mode (R9[1:0] = 2): slew rate for D OUT [7:0], PIXCLK, FRAME_VALID, and LINE_VALID.
 *            During normal operation, the slew of listed pads is set by JPEG configuration registers. Actual
 *            slew depends on load, temperature, and I/O voltage. Set this register based on customers' characterization
 *            results.
 *
 * Bit 3 - Unused.
 *
 * Bits 6:4 - Slew rate for GPIO[11:0]. Actual slew depends on load, temperature, and I/O voltage. Set this
 *            register based on customers’ characterization results.
 *
 * Bit 7 - 1 = enable I/O pad input clamp during standby.That prevents elevated standby current if pad input
 *         floating. The pads are GPIO[11:0], D OUT [7:0], FRAME_VALID, LINE_VALID, PIXCLK.
 *         0 = disable I/O pad input clamp. Set this bit to “1” before going to soft/hard standby to reduce the 
 *         leakage current. When coming out of standby, set this bit back to “0.” If none of the GPIOs are used
 *         as inputs, this bit can be left at “1.”
 *
 * Bits 10:8 - Slew rate for S DATA . 7 = fastest slew; 0 = slowest. Actual slew depends on load, temperature,
 *             and I/O voltage. Actual slew depends on load, temperature, and I/O voltage. Set this register
 *             based on customers’ characterization results.
 */
#define MT9D111_REG_PAD_SLEW                                                                    0x0A

/**
 * Bit 0 - Reserved.
 *
 * Bit 1 - Reserved.
 *
 * Bit 2 - Reserved.
 *
 * Bit 3 - 1 = enable output FIFO clock.
 *
 * Bit 4 - 1 = enable JPEG clock.
 *
 * Bit 5 - Reserved.
 *
 * Bit 6 - Reserved.
 *
 * Bit 7 - 1 = enable GPIO clock.
 *
 * Bit 8 - Reserved.
 */
#define MT9D111_REG_INTERNAL_CLOCK_CONTROL                                                      0x0B

/**
 * Bits 10:0 - Use the crop window for pan and zoom. Crop coordinates are updated synchronously with frame
 *             enable, unless freeze is enabled. In preview mode crop coordinates are automatically divided by
 *             X skip factor. Coordinates are specified as (X0, Y0) and (X1, Y1), where X0 < X1 and Y0 < Y1.
 *             Value is overwritten by mode driver (ID = 7).
 */
#define MT9D111_REG_X0_COORDINATE_FOR_CROP_WINDOW                                               0x11

/**
 * Bits 10:0 - See R17:1. Value is overwritten by mode driver (ID = 7).
 */
#define MT9D111_REG_X1_COORDINATE_FOR_CROP_WINDOW_1                                             0x12

/**
 * Bits 10:0 - See R17:1. Value is overwritten by mode driver (ID = 7).
 */
#define MT9D111_REG_Y0_COORDINATE_FOR_CROP_WINDOW                                               0x13

/**
 * Bits 10:0 - See R17:1. Value is overwritten by mode driver (ID = 7).
 */
#define MT9D111_REG_Y1_COORDINATE_FOR_CROP_WINDOW_1                                             0x14

/**
 * \brief This register controls operation of the decimator. Value is overwritten by mode driver (ID=7).
 *
 * Bit 0 - Reserved.
 *
 * Bit 1 - Reserved.
 *
 * Bit 2 - High precision mode. Additional bits for result are stored. Can only be used for decimation > 2.
 *
 * Bit 3 - Reserved.
 *
 * Bit 4 - Enable 4:2:0 mode.
 *
 * Bits 5:6 - Reserved.
 */
#define MT9D111_REG_DECIMATOR_CONTROL                                                           0x15

/**
 * Bits 12:0 - X output = int (X input/2048*reg. value). Value is calculated and overwritten by mode driver
 *             (ID = 7).
 */
#define MT9D111_REG_WEIGHT_FOR_HORIZONTAL_DECIMATION                                            0x16

/**
 * \brief InputSize is defined by Registers 17–20. Minimal output size supported by the decimator is 3 x 1 pixe.
 *
 * Bits 12:0 - Y output = int (Y input/2048*reg. value). Value is calculated and overwritten by mode driver
 *             (ID = 7).
 */
#define MT9D111_REG_WEIGHT_FOR_VERTICAL_DECIMATION                                              0x17

/**
 * \brief In order to avoid skewing WB statistics by very dark or very bright values, this register allows
 *        programming the luminance range of pixels to be used for WB computation.
 *
 * Bits 7:0 - Lower limit of luminance for WB statistics.
 *
 * Bits 15:8 - Upper limit of luminance for WB statistics.
 */
#define MT9D111_REG_LUMINANCE_RANGE_OF_PIX_CONSIDERED_IN_WB_STATS                               0x20

/**
 * \brief This register specifies the right/left coordinates of the window used by AWB measurement engine.
 *        The values programmed in the registers are desired boundaries divided by 8.
 *
 * Bits 7:0 - Left window boundary.
 *
 * Bits 15:8 - Right window boundary.
 */
#define MT9D111_REG_RIGHT_LEFT_COORDINATES_OF_AWB_MEASUREMENT_WINDOW                            0x2D

/**
 * \brief This register specifies the bottom/top coordinates of the window used by AWB measurement engine.
 *        The values programmed in the registers are desired boundaries divided by 8.
 *
 * Bits 7:0 - Top window boundary.
 *
 * Bits 15:8 - Bottom window boundary.
 */
#define MT9D111_REG_BOTTOM_TOP_COORDINATES_OF_AWB_MEASUREMENT_WINDOW                            0x2E

/**
 * This register contains a measure of red chrominance obtained using AWB measurement algorithm. The measure 
 * is normalized to an arbitrary maximum value; the same for R48:1, R49:1, and R50:1. Because of this 
 * normalization, only the ratios of values of registers R48:1 R49:1, and R50:1 should be used.
 */
#define MT9D111_REG_RED_CHROMIANCE_MEASURE_CALCULATED_BY_AWB                                    0x30

/**
 * This register contains a measure of image luminance obtained using AWB measurement algorithm. The measure
 * is normalized to an arbitrary maximum value; the same for R48:1, R49:1, and R50:1. Because of this
 * normalization, only the ratios of values of registers R48:1, R49:1, and R50:1 should be used.
 */
#define MT9D111_REG_LUMINANCE_MEASURE_CALCULATED_BY_AWB                                         0x31

/**
 * This register contains a measure of blue chrominance obtained using AWB measurement algorithm. The measure 
 * is normalized to an arbitrary maximum value; the same for R48:1, R49:1, and R50:1. Because of this 
 * normalization, only the ratios of values of registers R48:1, R49:1, and R50:1 should be used.
 */
#define MT9D111_REG_BLUE_CHROMIANCE_MEASURE_CALCULATED_BY_AWB                                   0x32

/**
 * Bits 7:0 - Ap_knee; threshold for aperture signal.
 *
 * Bits 10:8 - Ap_gain; gain for aperture signal.
 *
 * Bits 13:11 - Ap_exp; exponent for gain for aperture signal.
 */
#define MT9D111_REG_1D_APERTURE_CORRECTION_PARAMETERS                                           0x35

/**
 * \brief Defines 2D aperture gain and threshold.
 *
 * Bits 7:0 - Ap_knee; threshold for aperture signal.
 *
 * Bits 10:8 - Ap_gain; gain for aperture signal.
 *
 * Bits 13:11 - Ap_exp; exponent for gain for aperture signal.
 *
 * Bit 14 - Reserved.
 */
#define MT9D111_REG_2D_APERTURE_CORRECTION_PARAMETERS                                           0x36

/**
 * Bits 2:0 - UV filter:
 *            000 - no filter
 *            001 - 11110 averaging filter
 *            010 - 01100 averaging filter
 *            011 - 01210 averaging filter
 *            100 - 12221 averaging filter
 *            101 - median 3
 *            110 - median 5
 *            111 - Reserved
 *
 * Bits 4:3 - Y filter mode:
 *            00 - no filter
 *            01 - median 3
 *            10 - median 5
 *            11 - Reserved
 *
 * Bit 5 - Permanently enable Y filter.
 */
#define MT9D111_REG_FILTERS                                                                     0x37

/**
 * This register contains the value subtracted by IFP from pixel values prior to CCM. If the subtraction produces
 * a negative result for a particular pixel, the value of this pixel is set to "0".
 */
#define MT9D111_REG_SECOND_BLACK_LEVEL                                                          0x3B

/**
 * This register contains the value subtracted by IFP from raw pixel values before applying lens shading correction
 * and digital gains. If the subtraction produces a negative result for a particular pixel, the value of this pixel
 * is set to "0". Typically, the subtracted value should be equal to the black level targeted by the sensor. This
 * value is subtracted from all test patterns as well.
 */
#define MT9D111_REG_FIRST_BLACK_LEVEL                                                           0x3C

/**
 * 1 - enable. Enable automatic recalculation operation of coefficient lens correction dependent on sensor output
 * resolution.
 */
#define MT9D111_REG_ENABLE_SUPPORT_FOR_PREVIEW_MODES                                            0x43

/**
 * Read only.
 */
#define MT9D111_REG_MIRRORS_SENSOR_REGISTER_0x20                                                0x44

/**
 * Read only.
 */
#define MT9D111_REG_MIRRORS_SENSOR_REGISTER_0xF2                                                0x45

/**
 * Read only.
 */
#define MT9D111_REG_MIRRORS_SENSOR_REGISTER_0x21                                                0x46

/**
 * Threshold for identifying pixel neighborhood as having an edge.
 */
#define MT9D111_REG_EDGE_THRESHOLD_FOR_INTERPOLATION                                            0x47

/**
 * \brief Injects test pattern into beginning of color pipeline.
 *
 * Bits 2:0 - Test mode:
 *            001 - flat field; RGB values are specified in R73-75:1
 *            010 - vertical monochrome ramp
 *            011 - vertical color bars
 *            100 - vertical monochrome bars; set bar intensity in R73:1 and R74:1
 *            101 - pseudo-random test pattern
 *            110 - horizontal monochrome bars; set bar intensity in R73:1 and R74:1
 */
#define MT9D111_REG_TEST_PATTERN                                                                0x48

/**
 * Bits 9:0
 */
#define MT9D111_REG_TEST_PATTERN_R_MONOCHROME_VALUE                                             0x49

/**
 * Bits 9:0
 */
#define MT9D111_REG_TEST_PATTERN_G_MONOCHROME_VALUE                                             0x4A

/**
 * Bits 9:0
 */
#define MT9D111_REG_TEST_PATTERN_B_VALUE                                                        0x4B

/**
 * Default setting 32 corresponds to gain value of 1. Gain scales linearly with value.
 */
#define MT9D111_REG_DIGITAL_GAIN_2                                                              0x4E

/**
 * Bits 2:0 - matrix element 1 (C11) exponent
 *
 * Bits 5:3 - matrix element 2 (C12) exponent
 *
 * Bits 8:6 - matrix element 3 (C13) exponent
 *
 * Bits 11:9 - matrix element 4 (C21) exponent
 *
 * Bits 14:12 - matrix element 5 (C22) exponent
 */
#define MT9D111_REG_COLOR_CORRECTION_MATRIX_EXPONENTS_FOR_C11_C22                               0x60

/**
 * Bits 2:0 - matrix element 6 (C23) exponent
 *
 * Bits 5:3 - matrix element 7(C31) exponent
 *
 * Bits 8:6 - matrix element 8(C32) exponent
 *
 * Bits 11:9 - matrix element 9(C33) exponent
 *
 * The value of a matrix coefficient is calculated Cij=(1 - 2*Sij)*Mij*2^-(Eij + 4), 0 <= Eij <= 4
 * Here Sij is coefficient’s sign, Mij is the mantissa and Eij is the exponent.
 */
#define MT9D111_REG_COLOR_CORRECTION_MATRIX_EXPONENTS_FOR_C22_C33                               0x61

/**
 * Bits 7:0 - Color correction matrix element 1 (C11).
 *
 * Bits 15:8 - Color correction matrix element 2 (C12).
 */
#define MT9D111_REG_COLOR_CORRECTION_MATRIX_ELEMENTS_1_AND_2_MANTISSAS                          0x62

/**
 * Bits 7:0 - Color correction matrix element 3 (C13).
 *
 * Bits 15:8 - Color correction matrix element 4 (C21).
 */
#define MT9D111_REG_COLOR_CORRECTION_MATRIX_ELEMENTS_3_AND_4_MANTISSAS                          0x63

/**
 * Bits 7:0 - Color correction matrix element 5 (C22).
 *
 * Bits 15:8 - Color correction matrix element 6 (C23).
 */
#define MT9D111_REG_COLOR_CORRECTION_MATRIX_ELEMENTS_5_AND_6_MANTISSAS                          0x64

/**
 * Bits 7:0 - Color correction matrix element 7 (C31).
 *
 * Bits 15:8 - Color correction matrix element 8 (C32).
 */
#define MT9D111_REG_COLOR_CORRECTION_MATRIX_ELEMENTS_7_AND_8_MANTISSAS                          0x65

/**
 * Bits 7:0 - Color correction matrix element 9 (C33).
 *
 * Bits 13:8 - Signs for off-diagonal CCM elements.
 *             Bit 8 - sign for C12
 *             Bit 9 - sign for C13
 *             Bit 10 - sign for C21
 *             Bit 11 - sign for C23
 *             Bit 12 - sign for C31
 *             Bit 13 - sign for C32
 *             1 - indicates negative
 *             0 - indicates positive
 *             Signs for C11, C22, and C33 are assumed always positive.
 */
#define MT9D111_REG_COLOR_CORRECTION_MATRIX_ELEMENT_9_MANTISSA_AND_SIGNS                        0x66

/**
 * Default setting 128 corresponds to gain value of 1. Gain scales linearly with value.
 */
#define MT9D111_REG_DIGITAL_GAIN_1_FOR_RED_PIXELS                                               0x6A

/**
 * Default setting 128 corresponds to gain value of 1. Gain scales linearly with value.
 */
#define MT9D111_REG_DIGITAL_GAIN_1_FOR_GREEN_1_PIXELS                                           0x6B

/**
 * Default setting 128 corresponds to gain value of 1. Gain scales linearly with value.
 */
#define MT9D111_REG_DIGITAL_GAIN_1_FOR_GREEN_2_PIXELS                                           0x6C

/**
 * Default setting 128 corresponds to gain value of 1. Gain scales linearly with value.
 */
#define MT9D111_REG_DIGITAL_GAIN_1_FOR_BLUE_PIXELS                                              0x6D

/**
 * Write 128 to set all gains (R106-R109) to 1. When read, this register returns the value of R107.
 */
#define MT9D111_REG_DIGITAL_GAIN_1_FOR_ALL_COLORS                                               0x6E

/**
 * \brief This register specifies the boundaries of the window used by the flicker measurement engine. The values
 * programmed in the registers are the desired boundaries divided by 8.
 *
 * Bits 7:0 - Window width.
 *
 * Bits 15:8 - Left window boundary.
 */
#define MT9D111_REG_BOUNDARIES_OF_FLICKER_MEASUREMENT_WINDOW_LEFT_WIDTH                         0x7A

/**
 * \brief This register specifies the boundaries of the window used by the flicker measurement engine.
 *
 * Bits 5:0 - Window height.
 *
 * Bits 15:6 - Top window boundary.
 */
#define MT9D111_REG_BOUNDARIES_OF_FLICKER_MEASUREMENT_WINDOW_TOP_HEIGHT                         0x7B

/**
 * This register specifies the number of pixels in the window used by the flicker measurement engine.
 */
#define MT9D111_REG_FLICKER_MEASUREMENT_WINDOW_SIZE                                             0x7C

/**
 * Bits 15:0
 */
#define MT9D111_REG_MEASURE_OF_AVERAGE_LUMINANCE_IN_FLICKER_MEASUREMENT_WINDOW                  0x7D

/**
 * 1 = blank outgoing frames. When set, current frame completes and following frames are not output, FEN = LEN = 0.
 * When unset, output resumes with the next frame. The bit is synchronized with frame enable. See freeze bit (R152[7]).
 */
#define MT9D111_REG_BLANK_FRAMES                                                                0x96

/**
 * Bit 0 - In YUV output mode, swaps Cb and Cr channels. In RGB mode, swaps R and B. This bit is subject to
 *         synchronous update.
 *
 * Bit 1 - Swaps chrominance byte with luminance byte in YUV output. In RGB mode, swaps odd and even bytes. This bit
 *         is subject to synchronous update.
 *
 * Bit 2 - Reserved
 *
 * Bit 3 - Monochrome output.
 *
 * Bit 4 - 1 = use ITU-R BT.601 codes when bypassing FIFO. (0xAB = frame start; 0x80 = line start; 0x9D = line end;
 *         0xB6 = frame end.)
 *
 * Bit 5 - 1 = output RGB (see R151[7:6])
 *         0 = output YUV
 *
 * Bits 7:6 - RGB output format:
 *            00 = 16-bit RGB565
 *            01 = 15-bit RGB555
 *            10 = 12-bit RGB444x
 *            11 = 12-bit RGBx444
 */
#define MT9D111_REG_OUTPUT_FORMAT_CONFIGURATION                                                 0x97

/**
 * Bit 0 - 1 = disable Cr channel (R in RGB mode).
 *
 * Bit 1 - 1 = disable Y channel (G in RGB mode).
 *
 * Bit 2 - 1 = disable Cb channel (B in RGB mode).
 *
 * Bits 5:3 - Test ramp output:
 *            00 - off
 *            01 - by column
 *            10 - by row
 *            11 - by frame
 *
 * Bit 6 - 1 = enable 8+2 bypass.
 *
 * Bit 7 - 1 = freeze update SOC registers affecting output size and format. These include R151:1, R17-23:1.
 */
#define MT9D111_REG_OUTPUT_FORMAT_TEST                                                          0x98

/**
 * Bits 11:0
 */
#define MT9D111_REG_LINE_COUNT                                                                  0x99

/**
 * Bits 15:0
 */
#define MT9D111_REG_FRAME_COUNT                                                                 0x9A

/**
 * Bits 2:0 - Special effect selection bits:
 *            0 - disabled
 *            1 - monochrome
 *            2 - sepia
 *            3 - negative
 *            4 - solarization with unmodified UV
 *            5 - solarization with -UV
 *
 * Bits 5:3 - Dither enable and amplitude. Valid values are 1..4, others disable.
 *
 * Bit 6 - 1 = dither only in luma channel, 0 = dither in all color channels.
 *
 * Bits 15:8 - Solarization threshold for luma, divided by 2; 64..127.
 */
#define MT9D111_REG_SPECIAL_EFFECTS                                                             0xA4

/**
 * Bits 7:0 - Sepia constant for Cr.
 *
 * Bits 15:8 - Sepia constant for Cb.
 */
#define MT9D111_REG_SEPIA_CONSTANTS                                                             0xA5

/**
 * Bits 7:0 - Ordinate of gamma curve knee point 0 (its abscissa is 0).
 *
 * Bits 15:8 - Gamma curve knee point 1.
 *
 * Gamma correction curve is implemented in the MT9D111 as a piecewise linear function mapping 12-bit arguments
 * to 8-bit output. Seventeen line fragments forming the curve connect 19 knee points, whose abscissas are fixed
 * and ordinates are programmable through registers R[178:187]:1. The abscissas of the knee points are 0, 64, 128,
 * 256, 512, 768, 1024, 1280, 1536, 1792, 2048, 2304, 2560, 2816, 3072, 3328, 3584, 3840, and 4095. Ordinates of
 * knee points written directly to the registers R[178:187]:1 may be overwritten by mode driver (ID=7). The recommended
 * way to program a gamma curve into the MT9D111 is to write desired knee ordinates to one of the two
 * mode.gamma_table[A/B][] arrays that hold gamma curves used in contexts A and B. Once the desired ordinates are in
 * one of those arrays, all that is needed to put them into effect (i.e. into the registers) is a short command
 * telling the sequencer to go to proper context or through REFRESH loop.
 */
#define MT9D111_REG_GAMMA_CURVE_KNEES_0_AND_1                                                   0xB2

/**
 * Bits 7:0 - Gamma curve knee point 2.
 *
 * Bits 15:8 - Gamma curve knee point 3.
 */
#define MT9D111_REG_GAMMA_CURVE_KNEES_2_AND_3                                                   0xB3

/**
 * Bits 7:0 - Gamma curve knee point 4.
 *
 * Bits 15:8 - Gamma curve knee point 5.
 */
#define MT9D111_REG_GAMMA_CURVE_KNEES_4_AND_5                                                   0xB4

/**
 * Bits 7:0 - Gamma curve knee point 6.
 *
 * Bits 15:8 - Gamma curve knee point 7.
 */
#define MT9D111_REG_GAMMA_CURVE_KNEES_6_AND_7                                                   0xB5

/**
 * Bits 7:0 - Gamma curve knee point 8.
 *
 * Bits 15:8 - Gamma curve knee point 9.
 */
#define MT9D111_REG_GAMMA_CURVE_KNEES_8_AND_9                                                   0xB6

/**
 * Bits 7:0 - Gamma curve knee point 10.
 *
 * Bits 15:8 - Gamma curve knee point 11.
 */
#define MT9D111_REG_GAMMA_CURVE_KNEES_10_AND_11                                                 0xB7

/**
 * Bits 7:0 - Gamma curve knee point 12.
 *
 * Bits 15:8 - Gamma curve knee point 13.
 */
#define MT9D111_REG_GAMMA_CURVE_KNEES_12_AND_13                                                 0xB8

/**
 * Bits 7:0 - Gamma curve knee point 14.
 *
 * Bits 15:8 - Gamma curve knee point 15.
 */
#define MT9D111_REG_GAMMA_CURVE_KNEES_14_AND_15                                                 0xB9

/**
 * Bits 7:0 - Gamma curve knee point 16.
 *
 * Bits 15:8 - Gamma curve knee point 17.
 */
#define MT9D111_REG_GAMMA_CURVE_KNEES_16_AND_17                                                 0xBA

/**
 * Bits 7:0
 */
#define MT9D111_REG_GAMMA_CURVE_KNEE_18                                                         0xBB

/**
 * Bit 3 - Clips Y values to 16–235; clips UV values to 16–240.
 *
 * Bit 2 - Adds 128 to U and V values.
 *
 * Bit 1 - 1 = ITU-R BT.601 coefficients
 *         0 = use sRGB coefficients.
 *
 * Bit 0 - 0 = no scaling
 *         1 = scales Y data by 219/256 and UV data by 224/256.
 */
#define MT9D111_REG_YUV_YCbCr_CONTROL                                                           0xBE

/**
 * Bit 15:8 - Y offset.
 *
 * Bit 7:0 - RGB offset.
 */
#define MT9D111_REG_Y_RGB_OFFSET                                                                0xBF

/**
 * Bit 0 - 1 = reset microcontroller.
 *
 * Bit 1 - Reserved
 *
 * Bit 2 - Reserved
 *
 * Bit 3 - Reserved
 *
 * Bits 6:4 - Reserved
 *
 * Bits 6:5 - Reserved
 *
 * Bits 7:5 - Reserved
 *
 * Bit 7 - Microcontroller debug indicator.
 *
 * Bits 11:8 - Reserved
 *
 * Bit 12 - Reserved
 *
 * Bit 13 - Reserved
 *
 * Bit 14 - Reserved
 *
 * Bit 15 - Reserved
 */
#define MT9D111_REG_MICROCONTROLLER_BOOT_MODE                                                   0xC3

/**
 * Bits 7:0 - Bits 7:0 of address for physical access; driver variable offset for logical access.
 *
 * Bits 12:8 - Bits 12:8 of address for physical access; driver ID for logical access.
 *
 * Bits 14:13 - Bits 14:13 of address for physical access; R198:1[14:13] = 01 select logical access.
 *
 * Bit 15 - 1 = 8-bit access;
 *          0 = 16-bit.
 *
 * Microcontroller variables are similar to two-wire serial interface registers, except that they are located in the
 * microcontroller’s memory and have different bit widths. Registers 198:1 and R200:1 provide easy access to variables
 * that can be represented as 8- or 16-bit unsigned integers (bytes or words). To access such a variable, one must
 * write its address to R198:1 and then read its value from R200:1 or write a new value to the same register.
 * Variables having more than 16 bits (e.g. 32-bit unsigned long integers) must be accessed as arrays of bytes or words -
 * there is no way to read or write their values without parsing. Variable address written to R198:1 can be physical
 * or logical. Physical address is the actual address of a byte or word in the microcontroller's address space.
 * Physical addresses can be used in many manipulations of memory content, for example, to upload custom binary code
 * to a specific RAM segment. The logical addressing option is provided only to facilitate access to public variables
 * of various firmware drivers. Logical address of a public variable consists of a 5-bit driver ID (0 = monitor,
 * 1 = sequencer, etc.) and 8-bit offset of the variable in the driver’s data structure (which cannot be larger than
 * 256 bytes).
 */
#define MT9D111_REG_MICROCONTROLLER_VARIABLE_ADDRESS                                            0xC6

/**
 * To read current value of an 8- or 16-bit variable from microcontroller memory, write its address to R198:1 and read
 * R200:1. To change value of a variable, write its address to R198:1 and its new value to R200:1. When bit width of
 * a variable is specified as 8 bits (R198:1[15]=1), the upper byte of R200:1 is irrelevant. It is set to “0” when the
 * register is read and ignored when it is written to. See R198:1 above for explanation how to read and set variables
 * having more than 16 bits.
 */
#define MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA                                               0xC8

/**
 * Use these registers to read or write up to 16 bytes of variable data using the burst two-wire serial interface
 * access mode. The variables must have consecutive addresses.
 */
#define MT9D111_REG_MICROCONTROLLER_VARIABLE_DATA_USING_BURST_TWO_WIRE_SERIAL_INTERFACE_ACCESS  0xC9
//! \}

/**
 * \brief IFP Registers, Page 2.
 *
 * Reference: Table 7: IFP Registers, Page 2; "MT9D111 - 1/3.2-Inch 2-Megapixel SOC Digital Image Sensor Registers".
 * \{
 */
#define MT9D111_REG_JPEG_CONTROL                                                        0x00
#define MT9D111_REG_JPEG_STATUS_0                                                       0x02
#define MT9D111_REG_JPEG_STATUS_1                                                       0x03
#define MT9D111_REG_JPEG_STATUS_2                                                       0x04
#define MT9D111_REG_JPEG_FRONT_END_CONFIG                                               0x05
#define MT9D111_REG_JPEG_CORE_CONFIG                                                    0x06
#define MT9D111_REG_JPEG_ENCODER_BYPASS                                                 0x0A
#define MT9D111_REG_OUTPUT_CONFIG                                                       0x0D
#define MT9D111_REG_OUTPUT_PCLK1_AND_PCLK2_CONFIG                                       0x0E
#define MT9D111_REG_OUTPUT_PCLK3_CONFIG                                                 0x0F
#define MT9D111_REG_SPOOF_FRAME_WIDTH                                                   0x10
#define MT9D111_REG_SPOOF_FRAME_HEIGHT                                                  0x11
#define MT9D111_REG_SPOOF_FRAME_LINE_TIMING                                             0x12
#define MT9D111_REG_JPEG_RAM_TEST_CONTROL_REGISTER                                      0x1D
#define MT9D111_REG_JPEG_INDIRECT_ACCESS_CONTROL                                        0x1E
#define MT9D111_REG_JPEG_INDIRECT_ACCESS_DATA                                           0x1F
#define MT9D111_REG_BOUNDARIES_OF_FIRST_AF_MEASUREMENT_WINDOW_TOP_LEFT                  0x40
#define MT9D111_REG_BOUNDARIES_OF_FIRST_AF_MEASUREMENT_WINDOW_HEIGHT_WIDTH              0x41
#define MT9D111_REG_AF_MEASUREMENT_WINDOW_SIZE                                          0x42
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AF_WINDOWS_W12_AND_W11                         0x43
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AF_WINDOWS_W14_AND_W13                         0x44
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AF_WINDOWS_W22_AND_W21                         0x45
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AF_WINDOWS_W24_AND_W23                         0x46
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AF_WINDOWS_W32_AND_W31                         0x47
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AF_WINDOWS_W34_AND_W33                         0x48
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AF_WINDOWS_W42_AND_W41                         0x49
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AF_WINDOWS_W44_AND_W43                         0x4A
#define MT9D111_REG_AF_FILTER_1_COEFFICIENTS                                            0x4B
#define MT9D111_REG_AF_FILTER_1_CONFIG                                                  0x4C
#define MT9D111_REG_AF_FILTER_1_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W12_AND_W11    0x4D
#define MT9D111_REG_AF_FILTER_1_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W14_AND_W13    0x4E
#define MT9D111_REG_AF_FILTER_1_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W22_AND_W21    0x4F
#define MT9D111_REG_AF_FILTER_1_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W24_AND_W23    0x50
#define MT9D111_REG_AF_FILTER_1_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W32_AND_W31    0x51
#define MT9D111_REG_AF_FILTER_1_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W34_AND_W33    0x52
#define MT9D111_REG_AF_FILTER_1_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W42_AND_W41    0x53
#define MT9D111_REG_AF_FILTER_1_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W44_AND_W43    0x54
#define MT9D111_REG_AF_FILTER_2_COEFFICIENTS                                            0x55
#define MT9D111_REG_AF_FILTER_2_CONFIG                                                  0x56
#define MT9D111_REG_AF_FILTER_2_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W12_AND_W11    0x57
#define MT9D111_REG_AF_FILTER_2_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W14_AND_W13    0x58
#define MT9D111_REG_AF_FILTER_2_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W22_AND_W21    0x59
#define MT9D111_REG_AF_FILTER_2_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W24_AND_W23    0x5A
#define MT9D111_REG_AF_FILTER_2_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W32_AND_W31    0x5B
#define MT9D111_REG_AF_FILTER_2_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W34_AND_W33    0x5C
#define MT9D111_REG_AF_FILTER_2_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W42_AND_W41    0x5D
#define MT9D111_REG_AF_FILTER_2_AVERAGE_SHARPNESS_MEASURE_FOR_AF_WINDOWS_W44_AND_W43    0x5E
#define MT9D111_REG_LENS_CORRECTION_CONTROL                                             0x80
#define MT9D111_REG_ZONE_BOUNDARIES_X1_AND_X2                                           0x81
#define MT9D111_REG_ZONE_BOUNDARIES_X0_AND_X3                                           0x82
#define MT9D111_REG_ZONE_BOUNDARIES_X4_AND_X5                                           0x83
#define MT9D111_REG_ZONE_BOUNDARIES_Y1_AND_Y2                                           0x84
#define MT9D111_REG_ZONE_BOUNDARIES_Y0_AND_Y3                                           0x85
#define MT9D111_REG_ZONE_BOUNDARIES_Y4_AND_Y5                                           0x86
#define MT9D111_REG_CENTER_OFFSET                                                       0x87
#define MT9D111_REG_FX_FOR_RED_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                    0x88
#define MT9D111_REG_FX_FOR_GREEN_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                  0x89
#define MT9D111_REG_FX_FOR_BLUE_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                   0x8A
#define MT9D111_REG_FY_FOR_RED_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                    0x8B
#define MT9D111_REG_FY_FOR_GREEN_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                  0x8C
#define MT9D111_REG_FY_FOR_BLUE_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                   0x8D
#define MT9D111_REG_DF_DX_FOR_RED_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                 0x8E
#define MT9D111_REG_DF_DX_FOR_GREEN_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY               0x8F
#define MT9D111_REG_DF_DX_FOR_BLUE_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                0x90
#define MT9D111_REG_DF_DY_FOR_RED_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                 0x91
#define MT9D111_REG_DF_DY_FOR_GREEN_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY               0x92
#define MT9D111_REG_DF_DY_FOR_BLUE_COLOR_AT_THE_FIRST_PIXEL_OF_THE_ARRAY                0x93
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_0_RED_COLOR                              0x94
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_0_GREEN_COLOR                            0x95
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_0_BLUE_COLOR                             0x96
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_1_RED_COLOR                              0x97
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_1_GREEN_COLOR                            0x98
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_1_BLUE_COLOR                             0x99
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_2_RED_COLOR                              0x9A
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_2_GREEN_COLOR                            0x9B
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_2_BLUE_COLOR                             0x9C
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_3_RED_COLOR                              0x9D
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_3_GREEN_COLOR                            0x9E
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_3_BLUE_COLOR                             0x9F
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_4_RED_COLOR                              0xA0
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_4_GREEN_COLOR                            0xA1
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_4_BLUE_COLOR                             0xA2
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_5_RED_COLOR                              0xA3
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_5_GREEN_COLOR                            0xA4
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_5_BLUE_COLOR                             0xA5
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_6_RED_COLOR                              0xA6
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_6_GREEN_COLOR                            0xA7
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_6_BLUE_COLOR                             0xA8
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_7_RED_COLOR                              0xA9
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_7_GREEN_COLOR                            0xAA
#define MT9D111_REG_SECOND_DERIVATIVE_FOR_ZONE_7_BLUE_COLOR                             0xAB
#define MT9D111_REG_X2_FACTORS                                                          0xAC
#define MT9D111_REG_GLOBAL_OFFSET_OF_FXY_FUNCTION                                       0xAD
#define MT9D111_REG_K_FACTOR_IN_K_FX_FY                                                 0xAE
#define MT9D111_REG_BOUNDARIES_OF_FIRST_AE_MEASUREMENT_WINDOW_TOP_LEFT                  0xC0
#define MT9D111_REG_BOUNDARIES_OF_FIRST_AE_MEASUREMENT_WINDOW_HEIGHT_WIDTH              0xC1
#define MT9D111_REG_AE_MEASUREMENT_WINDOW_SIZE_LSW                                      0xC2
#define MT9D111_REG_AE_AF_MEASUREMENT_ENABLE                                            0xC3
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AE_WINDOWS_W12_AND_W11                         0xC4
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AE_WINDOWS_W14_AND_W13                         0xC5
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AE_WINDOWS_W22_AND_W21                         0xC6
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AE_WINDOWS_W24_AND_W23                         0xC7
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AE_WINDOWS_W32_AND_W31                         0xC8
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AE_WINDOWS_W34_AND_W33                         0xC9
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AE_WINDOWS_W42_AND_W41                         0xCA
#define MT9D111_REG_AVERAGE_LUMINANCE_IN_AE_WINDOWS_W44_AND_W43                         0xCB
#define MT9D111_REG_SATURATION_AND_COLOR_KILL                                           0xD2
#define MT9D111_REG_HISTOGRAM_WINDOW_LOWER_BOUNDARIES                                   0xD3
#define MT9D111_REG_HISTOGRAM_WINDOW_UPPER_BOUNDARIES                                   0xD4
#define MT9D111_REG_FIRST_SET_OF_BIN_DEFINITIONS                                        0xD5
#define MT9D111_REG_SECONDS_SET_OF_BIN_DEFINITIONS                                      0xD6
#define MT9D111_REG_HISTOGRAM_WINDOW_SIZE                                               0xD7
#define MT9D111_REG_PIXEL_COUNTS_FOR_BIN0_AND_BIN1                                      0xD8
#define MT9D111_REG_PIXEL_COUNTS_FOR_BIN2_AND_BIN3                                      0xD9
//! \}

#endif // MT9D111_REG_H_

//! \} End of mt9d111 group
