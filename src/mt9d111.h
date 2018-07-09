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
#define MT9D111_CONFIG_I2C_ADR_LOW                                  0x48
#define MT9D111_CONFIG_I2C_ADR_HIGH                                 0xBA

#define MT9D111_CONFIG_I2C_ID                                       MT9D111_CONFIG_I2C_ADR_LOW

// Reset types
#define MT9D111_RESET_HARD                                          0
#define MT9D111_RESET_SOFT                                          1

// Standby types
#define MT9D111_STANDBY_HARD                                        0
#define MT9D111_STANDBY_SOFT                                        1

// Operation modes (or context)
#define MT9D111_MODE_PREVIEW                                        0
#define MT9D111_MODE_CAPTURE                                        1

// Output formats
#define MT9D111_OUTPUT_FORMAT_YCbCr                                 0
#define MT9D111_OUTPUT_FORMAT_RGB565                                1
#define MT9D111_OUTPUT_FORMAT_RGB555                                2
#define MT9D111_OUTPUT_FORMAT_RGB444x                               3
#define MT9D111_OUTPUT_FORMAT_RGBx444                               4
#define MT9D111_OUTPUT_FORMAT_JPEG                                  5
#define MT9D111_OUTPUT_FORMAT_RAW_8                                 6
#define MT9D111_OUTPUT_FORMAT_RAW_10                                7

// Max. resolution
#define MT9D111_OUTPUT_MAX_WIDTH                                    1600
#define MT9D111_OUTPUT_MAX_HEIGHT                                   1200

// Special Effects
#define MT9D111_SPECIAL_EFFECTS_DISABLED                            0
#define MT9D111_SPECIAL_EFFECTS_MONOCHROME                          1
#define MT9D111_SPECIAL_EFFECTS_SEPIA                               2
#define MT9D111_SPECIAL_EFFECTS_NEGATIVE                            3
#define MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UNMODIFIED_UV     4
#define MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UV                5

// Sensor States
#define MT9D111_STATE_PREVIEW_ENTER                                 0
#define MT9D111_STATE_PREVIEW                                       1
#define MT9D111_STATE_PREVIEW_LEAVE                                 2
#define MT9D111_STATE_CAPTURE_ENTER                                 3
#define MT9D111_STATE_CAPTURE                                       4
#define MT9D111_STATE_CAPTURE_LEAVE                                 5

// Auto Exposure Configuration
#define MT9D111_AUTO_EXPOSURE_OFF                                   0
#define MT9D111_AUTO_EXPOSURE_FAST_SETTLING                         1
#define MT9D111_AUTO_EXPOSURE_MANUAL                                2
#define MT9D111_AUTO_EXPOSURE_CONTINUOUS                            3
#define MT9D111_AUTO_EXPOSURE_FAST_SETTLING_PLUS_METERING           4

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
         * \brief Reads the value of a bit from a register.
         *
         * \param adr is the address of the register.
         * \param bit is the bit position to read.
         * \param state is a pointer to store the bit value.
         *
         * \return TRUE/FALSE if the reading was successful or not.
         */
        bool ReadRegBit(uint8_t adr, uint8_t bit, bool *state);
        /**
         * \brief Changes a register bit.
         *
         * \param adr is the address of the register.
         * \param bit is the bit position to write.
         * \param state is the new state of the bit position (high or low/true or false).
         *
         * \return TRUE/FALSE if the writing was successful or not.
         */
        bool WriteRegBit(uint8_t adr, uint8_t bit, bool state);
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
        /**
         * \brief Enables/Disables the hard standby.
         *
         * \param s is TRUE/FALSE to enable or disable the hard standby.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool HardStandby(bool s);
        /**
         * \brief Enables/Disables the soft standby.
         *
         * \param s is TRUE/FALSE to enable or disable the soft standby.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool SoftStandby(bool s);
        /**
         * \brief Sets the registers page to configure or read.
         *
         * Hardware registers are organized into several pages. Page 0 contains sensor controls.
         * Page 1 contains color pipeline controls. Page 2 contains JPEG, output FIFO and more color
         * pipeline controls. The desired page is selected by writing the desired value to R0xF0.
         * After that all READs and WRITEs to registers 0..255 except R0xF0 and R0xF1, is directed to
         * the selected page. R0xF0 and R0xF1 are special registers and are present on all pages.
         *
         * \param page is the registers page to set. It can be:
         *            - MT9D111_REG_PAGE_0.
         *            - MT9D111_REG_PAGE_1.
         *            - MT9D111_REG_PAGE_2.
         *            .
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool SetRegisterPage(uint16_t page);
        /**
         * \brief Gets the current active registers page.
         *
         * Note: See "SetRegisterPage" for more details about registers pages.
         *
         * \param page is pointer to store the active page number.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool GetRegisterPage(uint16_t *page);
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
         * \brief Enables the standby mode.
         *
         * Standby mode can be activated by two methods:
         *     - 1) The first method is to assert STANDBY, which places the chip into hard standby. Turning
         *          off the input clock (EXTCLK) reduces the standby power consumption to the maximum
         *          specification of 100 uA at 55 oC. There is no serial interface access for hard standby.
         *     - 2) The second method is activated through the serial interface by setting R0x0D:0[2] = 1 known
         *          as the soft standby. As long as the input clock remains on, the chip will allow access
         *          through the serial interface in soft standby.
         *     .
         *
         * Standby should only be activated from the preview mode (context A), and not the capture mode
         * (context B). In addition, the PLL state (off/bypassed/activated) is recorded at the time of firmware
         * standby (seq.cmd = 3) and restored once the camera is out of firmware standby. In both hard and soft
         * standby scenarios, internal clocks are turned off and the analog circuitry is put into a low power
         * state. Exit from standby must go through the same interface as entry to standby. If the input clock
         * is turned off, the clock must be restarted before leaving standby.
         *
         * To Enter Standby
         *     - 1) To prepare for standby:
         *              - a) Issue the STANDBY command to the firmware by setting seq.cmd = 3
         *              - b) Poll seq.state until the current state is in standby (seq.state = 9)
         *              - c) Bypass the PLL if used by setting R0x65:0[15] = 1
         *              .
         *     - 2) To prevent additional leakage current during standby:
         *              - a) Set R0x0A:1[7] = 1 to prevent elevated standby current. It will control the
         *                   bidirectional pads D OUT , LINE_VALID, FRAME_VALID, PIXCLK.
         *              - b) If the outputs are allowed to be left in an unknown state while in standby, the
         *                   current can increase. Therefore, either have the receiver hold the camera outputs
         *                   HIGH or LOW, or allow the camera to drive its outputs to a known state by setting
         *                   R0x0D:0[6] = 1. R0x0D:0[4] needs to remain at the default value of "0". In this case,
         *                   some pads will be HIGH while some will be LOW. For dual camera systems, at least
         *                   one camera has to be driving the bus at any time so that the outputs will not be
         *                   left floating.
         *              - c) Configure internal reserved I/O as outputs and drive LOW by the setting the respective
         *                   bit to "0" in the reserved I/O variables 0x1078, 0x1079, 0x1070, and 0x1071 (accessed
         *                   through R0xC6:1 and R0xC8:1). The following settings should be used:
         *                       - i)    R0xC6:1 = 0x9078
         *                       - ii)   R0xC8:1 = 0x0000
         *                       - iii)  R0xC6:1 = 0x9079
         *                       - iv)   R0xC8:1 = 0x0000
         *                       - v)    R0xC6:1 = 0x9070
         *                       - vi)   R0xC8:1 = 0x0000
         *                       - vii)  R0xC6:1 = 0x9071
         *                       - viii) R0xC8:1 = 0x0000
         *                       .
         *              .
         *     - 3) To put the camera in standby: Assert STANDBY = 1. Optionally, stop the EXTCLK clock to minimize
         *          the standby current specified in the MT9D131 data sheet. For soft standby, program standby
         *          R0x0D:0[2] = 1 instead.
         *     .
         *
         * Reference: MT9D131 Developer Guide. Standby Sequence. Page 13.
         *
         * \param type is the type of standby to enter (MT9D111_STANDBY_HARD or MT9D111_STANDBY_SOFT).
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool EnterStandby(uint8_t type=MT9D111_STANDBY_HARD);
        /**
         * \brief Disables the stanby mode.
         *
         * See "EnterStandby" method for more details about the standby mode.
         *
         * To Exit Standby
         *     - 1) De-assert standby:
         *              - a) Provide EXTCLK clock, if it was disabled when using STANDBY.
         *              - b) De-assert STANDBY = 0 if hard standby was used. Or program R0x0D:0[2] = 0 if soft
         *                   standby was used.
         *              .
         *     - 2) Reconfiguring output pads:
         *              - a) Go to preview.
         *              - b) Issue a GO_PREVIEW command to the firmware by setting seq.cmd = 1.
         *              - c) Poll seq.state until the current state is preview (seq.state = 3).
         *              .
         *     - 3) The following timing requirements should be met to turn off EXTCLK during hard standby:
         *              - a) After the asserting standby, wait 10 clock cycles before stopping the clock.
         *              - b) Restart the clock 24 clock cycles before de-asserting standby.
         *              .
         *     .
         *
         * Reference: MT9D131 Developer Guide. Standby Sequence. Page 13.
         *
         * \param type is the type of standby to enter (MT9D111_STANDBY_HARD or MT9D111_STANDBY_SOFT).
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool LeaveStandby(uint8_t type=MT9D111_STANDBY_HARD);
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
        /**
         * \brief Configure and enables the internal PLL.
         *
         * Since the input clock frequency is unknown, the part starts with PLL disabled.
         * The default MNP values are for 10 MHz, with 80 MHz as target. For other frequencies,
         * calculate and program appropriate MNP values. PLL programming and power-up sequence
         * is as follows:
         *     - 1) Program PLL frequency settings, R0x66-67:0
         *     - 2) Power up PLL, R0x65:0[14] = 0
         *     - 3) Wait for PLL settling time >150 us
         *     - 4) Turn off PLL bypass, R0x65:2[15] = 0
         *     .
         *
         * Allow one complete frame to effect the correct integration time after enabling PLL.
         *
         * Note: Until PLL is enabled the two-wire serial interface may be limited in speed.
         * After PLL is enabled, the two-wire serial interface master can increase its communication
         * speed.
         *
         * \param[in] val_1 is the fist value of the PLL frequency settings.
         * \param[in] val_2 is the second value of the PLL frequency settings.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool EnablePLL(uint16_t val_1, uint16_t val_2);
        /**
         * \brief Sets the operation mode (or context) of the sensor.
         *
         * \param mode is the operation mode.
         *
         * The operation mode can be:
         *     - MT9D111_MODE_PREVIEW for preview mode (usually, lower resolution and faster acquisition).
         *     - MT9D111_MODE_CAPTURE for capture mode (usually, higher resolution and slower acquisition).
         *     .
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool SetMode(uint8_t mode);
        /**
         * \brief Sets the output format of the frames.
         *
         * \param format is the new output format. It can be:
         *            - MT9D111_OUTPUT_FORMAT_YCbCr
         *            - MT9D111_OUTPUT_FORMAT_RGB565
         *            - MT9D111_OUTPUT_FORMAT_RGB555
         *            - MT9D111_OUTPUT_FORMAT_RGB444x
         *            - MT9D111_OUTPUT_FORMAT_RGBx444
         *            - MT9D111_OUTPUT_FORMAT_JPEG
         *            - MT9D111_OUTPUT_FORMAT_RAW_8
         *            - MT9D111_OUTPUT_FORMAT_RAW_10
         *            .
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool SetOutputFormat(uint8_t format);
        /**
         * \brief Sets the output image resolution of the given mode.
         *
         * \param[in] mode is the output mode (MT9D111_MODE_PREVIEW or MT9D111_MODE_CAPTURE).
         * \param[in] width is the output image width in pixels.
         * \param[in] height is the output image height in pixels.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool SetResolution(uint8_t mode, uint16_t width, uint16_t height);
        /**
         * \brief Sets special effects in the output images.
         *
         * \param[in] effect is the desired special effect. It can be:
         * \parblock
         *      - MT9D111_SPECIAL_EFFECTS_DISABLED
         *      - MT9D111_SPECIAL_EFFECTS_MONOCHROME
         *      - MT9D111_SPECIAL_EFFECTS_SEPIA
         *      - MT9D111_SPECIAL_EFFECTS_NEGATIVE
         *      - MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UNMODIFIED_UV
         *      - MT9D111_SPECIAL_EFFECTS_SOLARIZATION_WITH_UV
         *      .
         * \endparblock
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool SetSpecialEffects(uint8_t effect);

        /**
         * \brief Sets the auto exposure configuration.
         *
         * \param[in] state is the sensor state. It can be:
         * \parblock
         *      - MT9D111_STATE_PREVIEW_ENTER
         *      - MT9D111_STATE_PREVIEW
         *      - MT9D111_STATE_PREVIEW_LEAVE
         *      - MT9D111_STATE_CAPTURE_ENTER
         *      .
         * \endparblock
         * \param[in] config is the auto exposure configuration for the given state. It can be:
         * \parblock
         *      - MT9D111_AUTO_EXPOSURE_OFF
         *      - MT9D111_AUTO_EXPOSURE_FAST_SETTLING
         *      - MT9D111_AUTO_EXPOSURE_MANUAL
         *      - MT9D111_AUTO_EXPOSURE_CONTINUOUS
         *      - MT9D111_AUTO_EXPOSURE_FAST_SETTLING_PLUS_METERING
         *      .
         * \endparblock
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool SetAutoExposure(uint8_t state, uint8_t config);
};

#endif // MT9D111_H_

//! \} End of mt9d111 group
