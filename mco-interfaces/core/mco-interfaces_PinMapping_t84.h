/*!
 *  \file       mco-firmware_PinMapping_t84.h
 *  \author     Francois Best
 *  \date       30/01/2013
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2013
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "mco-firmware.h"
#include <avr/io.h>

BEGIN_MCO_CORE_NAMESPACE

/*
 Pin Function   Port    Special Function
 ----------------------------------------
 1  N.A.        VCC     Not swappable
 2  N.A.        XTAL1   Not swappable
 3  N.A.        XTAL2   Not swappable
 4  N.A.        Reset   Not swappable
 5  PWM MSB     (PB2)   OC0A
 6  PWM LSB     (PA7)   OC0B
 7  SPI MOSI    (PA6)   Not swappable
 8  SPI MISO    (PA5)   Not swappable
 9  SPI SCK     (PA4)   Not swappable
 10 SPI SS      (PA3)   PCINT3
 11 Clock out   (PA2)   
 12 Sync in     (PA1)   PCINT1
 13 Modulation  (PA0)   
 14 N.A.        GND     Not swappable
 */

#define MCO_CLOCK_PORT              PORTA
#define MCO_CLOCK_PIN               PA2
#define MCO_CLOCK_DDR               DDRA

#define MCO_MODULATION_PORT         PORTA
#define MCO_MODULATION_PIN          PA0
#define MCO_MODULATION_DDR          DDRA

#define MCO_SPI_DDR                 DDRA
#define MCO_SPI_PORT                PORTA
#define MCO_SPI_READ                PINA
#define MCO_SPI_MOSI                PA6
#define MCO_SPI_MISO                PA5
#define MCO_SPI_SCK                 PA4
#define MCO_SPI_SS                  PA3
#define MCO_SPI_SS_PCINT            PCINT3

#define MCO_SYNC_PORT               PORTA
#define MCO_SYNC_READ               PINA
#define MCO_SYNC_DDR                DDRA
#define MCO_SYNC_PIN                PA1
#define MCO_SYNC_PCINT              PCINT1
#define MCO_SYNC_PCINT_ENABLE       PCMSK0 |=  (1 << MCO_SYNC_PCINT)
#define MCO_SYNC_PCINT_DISABLE      PCMSK0 &= ~(1 << MCO_SYNC_PCINT)
#define MCO_SYNC_PCINT_ENABLE_BANK  GIMSK  |=  (1 << PCIE0)

#define MCO_SLOPE_MSB_DDR           DDRB
#define MCO_SLOPE_MSB_PIN           PB2
#define MCO_SLOPE_LSB_DDR           DDRA
#define MCO_SLOPE_LSB_PIN           PA7

#define MCO_TICK_TIMER_ISR          TIM0_OVF_vect

END_MCO_CORE_NAMESPACE
