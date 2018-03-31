/*
 * gpio.h
 * 
 * Copyright (c) 2018, Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * This file is part of MT9D111-Driver.
 * 
 * MT9D111-Driver is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * MT9D111-Driver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with MT9D111-Driver; if not, see <http://www.gnu.org/licenses/>
 * 
 */

/**
 * \file gpio.h
 * 
 * \brief GPIO Raspberry Pi driver.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 30/03/2018
 * 
 * \defgroup gpio Raspberry Pi GPIO Driver
 * \ingroup drivers
 * \{
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#define GPIO_DIR_OUTPUT         0
#define GPIO_DIR_INPUT          1

/**
 * \class GPIO
 *
 * \brief Class for a GPIO pin of the Raspberry Pi.
 */
class GPIO
{
        uint8_t pin;    /**< GPIO pin number. */
        bool dir;       /**< GPIO direction (output or input). */
        bool state;     /**< GPIO state (HIGH or LOW). */
        /**
         * \brief Export GPIO.
         *
         * \return TRUE/FALSE if it was successful or not.
         */
        bool Export();
        /**
         * \brief Unexport GPIO.
         *
         * \return TRUE/FALSE if it was successful or not.
         */
        bool Unexport();
    public:
        /**
         * \brief Class constructor (without initialization).
         *
         * \return None
         */
        GPIO();
        /**
         * \brief Class constructor with pin initialization.
         *
         * \param p is the GPIO pin number.
         * \param d is the GPIO direction (GPIO_DIR_OUTPUT or GPIO_DIR_INPUT).
         *
         * \return None
         */
        GPIO(uint8_t p, bool d=GPIO_DIR_OUTPUT);
        /**
         * \brief Class destructor.
         *
         * \return None
         */
        ~GPIO();
        /**
         * \brief GPIO initialization.
         *
         * \param p is the GPIO pin number.
         * \param d is the GPIO direction (GPIO_DIR_OUTPUT or GPIO_DIR_INPUT).
         *
         * \return TRUE/FALSE if it was successful or not.
         */
        bool Open(uint8_t p, bool d);
        /**
         * \brief Closes the GPIO pin (deinitialization).
         *
         * \rerun TRUE/FALSE if it was successful or not.
         */
        bool Close();
        /**
         * \brief Sets GPIO direction.
         *
         * \param d is the direction of the GPIO pin (GPIO_DIR_OUTPUT or GPIO_DIR_INPUT).
         *
         * \return TRUE/FALSE if it was successful or not.
         */
        bool SetDir(bool d);
        /**
         * \brief Sets GPIO state (when it is a output GPIO).
         *
         * \param s is the state of the output GPIO pin (HIGH or LOW).
         *
         * \return TRUE/FALSE if it was successful or not.
         */
        bool Set(bool s);
        /**
         * \brief Toggles an output GPIO state.
         *
         * \return TRUE/FALSE if it was successful or not.
         */
        bool Toggle();
        /**
         * \brief Gets the state of a input GPIO.
         *
         * \param s is a variable to store the state of the input GPIO.
         *
         * \return TRUE/FALSE if it was successful or not.
         */
        bool Get(bool &s);
        /**
         * \brief Returns the GPIO pin number.
         *
         * \return The number of the GPIO pin.
         */
        uint8_t GetPinNumber();
        /**
         * \brief Returns the GPIO direction.
         *
         * \return The direction of the GPIO pin.
         */
        bool GetDir();
};

#endif // GPIO_H_

//! \} End of gpio group
