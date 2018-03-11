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
    uint16_t    value;      /**< Register value. */
};

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
 *                                See “Column and Row Skip” on page 125 for more information.
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
 *
 */
#define MT9D111_REG_READ_MODE_A                     0x21

/**
 *
 */
#define MT9D111_REG_DARK_COL_ROWS                   0x22

/**
 *
 */
#define MT9D111_REG_FLASH                           0x23

/**
 *
 */
#define MT9D111_REG_EXTRA_RESET                     0x24

/**
 *
 */
#define MT9D111_REG_LINE_VALID_CONTROL              0x25

/**
 *
 */
#define MT9D111_REG_BOTTOM_DARK_ROWS                0x26

/**
 *
 */
#define MT9D111_REG_GREEN_1_GAIN                    0x2B

/**
 *
 */
#define MT9D111_REG_BLUE_GAIN                       0x2C

/**
 *
 */
#define MT9D111_REG_RED_GAIN                        0x2D

/**
 *
 */
#define MT9D111_REG_GREEN_2_GAIN                    0x2E

/**
 * This register can be used to simultaneously set all 4 gains. When read, it returns the value stored in R0x2B:0.
 */
#define MT9D111_REG_GLOBAL_GAIN                     0x2F

/**
 *
 */
#define MT9D111_REG_ROW_NOISE                       0x30

/**
 * For each bit set, the corresponding dark row (rows 0–7) are used in the black level algorithm.
 * For this to occur, the reading of those rows must be enabled by the settings in R0x22:0.
 */
#define MT9D111_REG_BLACK_ROWS                      0x59

/**
 *
 */
#define MT9D111_REG_DARK_G1_AVERAGE                 0x5B

/**
 *
 */
#define MT9D111_REG_DARK_B_AVERAGE                  0x5C

/**
 *
 */
#define MT9D111_REG_DARK_R_AVERAGE                  0x5D

/**
 *
 */
#define MT9D111_REG_DARK_G2_AVERAGE                 0x5E

/**
 *
 */
#define MT9D111_REG_CALIB_THRESHOLD                 0x5F

/**
 *
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
 *
 */
#define MT9D111_REG_CLOCK_CONTROL                   0x65

/**
 *
 */
#define MT9D111_REG_PLL_CONTROL_1                   0x66

/**
 *
 */
#define MT9D111_REG_PLL_CONTROL_2                   0x67

/**
 *
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
 * When this value is reached, the strobe is de-asserted if strobe control is “0” (R0xC0:0[1]).
 */
#define MT9D111_REG_DEASSERT_STROBE_T4              0xC4

/**
 * Bits 15:0 - Assert Flash Time: These 16 bits are compared to the upper bits of a 24-bit counter, which starts counting master
 * clocks when global reset starts. When this value is reached, the flash is asserted.
 */
#define MT9D111_REG_ASSERT_FLASH                    0xC5

/**
 * Bits 15:0 - De-assert Flash Time: These 16 bits are compared to the upper bits of a 24-bit Time counter, which starts counting
 * master clocks when global reset starts. When this value is reached, the flash is de-asserted if flash control is “0” (R0xC0:0[2]).
 */
#define MT9D111_REG_DEASSERT_FLASH                  0xC6

/**
 * Bit 9:0 - AIN3 Sample: Contains sample of AIN3 if external signal sampling is enabled (R0xE3:0[15] = 1).
 * See “Analog Inputs AIN1–AIN3” on page 134.
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
 * Bits 2:0 - Page Register: Must be kept at “0” to be able to write/read from sensor. Used in SOC to access other pages with
 * registers.
 */
#define MT9D111_REG_PAGE_REGISTER                   0xF0

/**
 * Bits 15:0 - Bytewise Address: Special address to perform 16-bit reads and writes to the sensor in 8-bit chunks.
 * See “8-Bit Write Sequence” on page 183.
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

#endif // MT9D111_REG_H_

//! \} End of mt9d111 group
