/**
 * @file CosaBenchmarkRTC.ino
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2012-2014, Mikael Patel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * @section Description
 * Cosa RTC (Real-Time Clock) Benchmark. Measurement and validate RTC
 * operations; micro- and milli-second. The benchmark shows the number
 * of micro-seconds required for access of the RTC values, how
 * accurate the DELAY macro and Watchdog delay is. 
 *
 * @section Circuit
 * This example requires no special circuit. Uses serial output.
 *
 * This file is part of the Arduino Che Cosa project.
 */

#include "Cosa/RTC.hh"
#include "Cosa/Watchdog.hh"
#include "Cosa/Memory.h"
#include "Cosa/Trace.hh"
#include "Cosa/IOStream/Driver/UART.hh"

void setup()
{
  uint32_t start, stop, err;

  // Start the trace output stream on the serial port
  uart.begin(9600);
  trace.begin(&uart, PSTR("CosaBenchmarkRTC: started"));

  // Check amount of free memory
  TRACE(free_memory());

  // Print CPU clock and instructions per 1MHZ 
  TRACE(F_CPU);
  TRACE(I_CPU);

  // Start the timers
  Watchdog::begin();
  RTC::begin();

  // Check timer parameters
  TRACE(Watchdog::ms_per_tick());
  TRACE(Watchdog::ticks());
  TRACE(RTC::us_per_tick());
  TRACE(RTC::seconds());
  
  // Measure baseline
  MEASURE("RTC::micros(): ", 1) RTC::micros();
  MEASURE("RTC::millis(): ", 1) RTC::millis();
  MEASURE("RTC::seconds(): ", 1) RTC::seconds();
  MEASURE("RTC::delay(1): ", 1)  RTC::delay(1);
  MEASURE("RTC::delay(10): ", 1) RTC::delay(10);
  MEASURE("DELAY(10): ", 1) DELAY(10);
  MEASURE("DELAY(100): ", 1) DELAY(100);
  MEASURE("delay(10): ", 1) delay(10);
  MEASURE("delay(100): ", 1) delay(100);
  MEASURE("sleep(1): ", 1) sleep(1);
  MEASURE("yield(): ", 1) yield();

  // Start the measurement
  TRACE(RTC::micros());
  TRACE(RTC::millis());
  TRACE(RTC::seconds());
  for (uint8_t i = 0; i < 5; i++) {
    Watchdog::delay(1000);
    TRACE(RTC::micros());
    TRACE(RTC::millis());
    TRACE(RTC::seconds());
  }

  // Measure and validate micro-second level (RTC)
  err = 0;
  for (uint32_t i = 0; i < 100000; i++) {
    start = RTC::micros();
    DELAY(100);
    stop = RTC::micros();
    uint32_t diff = stop - start;
    if (diff > 136) {
      trace.printf_P(PSTR("%ul: start = %ul, stop = %ul, diff = %ul\n"), 
		     i, start, stop, diff);
      Watchdog::delay(128);
      err++;
    }
  }
  TRACE(RTC::seconds());
  INFO("DELAY(100): 100000 measurement/validation (err = %ul)", err);

  // Measure and validate milli-second level (RTC)
  err = 0;
  for (uint32_t i = 0; i < 100; i++) {
    start = RTC::millis();
    RTC::delay(100);
    stop = RTC::millis();
    uint32_t diff = stop - start;
    if (diff > 115) {
      trace.printf_P(PSTR("%ul: start = %ul, stop = %ul, diff = %ul\n"), 
		     i, start, stop, diff);
      Watchdog::delay(128);
      err++;
    }
  }
  TRACE(RTC::seconds());
  INFO("RTC::delay(100): 100 measurement/validation (err = %ul)", err);

  // Measure and validate milli-second level (Watchdog)
  err = 0;
  for (uint32_t i = 0; i < 100; i++) {
    start = RTC::millis();
    Watchdog::delay(100);
    stop = RTC::millis();
    uint32_t diff = stop - start;
    if (diff > 115) {
      trace.printf_P(PSTR("%ul: start = %ul, stop = %ul, diff = %ul\n"), 
		     i, start, stop, diff);
      Watchdog::delay(128);
      err++;
    }
  }
  TRACE(RTC::seconds());
  INFO("Watchdog::delay(100): 100 measurement/validation (err = %ul)", err);
}

void loop()
{
  ASSERT(true == false);
}
