/**
 * @file Cosa/Driver/DS1302.hh
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2013-2014, Mikael Patel
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
 * This file is part of the Arduino Che Cosa project.
 */

#include "Cosa/Driver/DS1302.hh"

uint8_t 
DS1302::read()
{
  uint8_t bits = CHARBITS;
  uint8_t res = 0;
  synchronized {
    for (;;) {
      if (m_sda.is_set()) res |= 0x80;
      m_clk._toggle();
      m_clk._toggle();
      if (--bits == 0) break;
      res >>= 1;
    }
  }
  return (res);
}

void 
DS1302::write(uint8_t data)
{
  uint8_t bits = CHARBITS;
  synchronized {
    do {
      m_sda._write(data & 0x01);
      m_clk._toggle();
      data >>= 1;
      m_clk._toggle();
    } while (--bits);
  }
}

uint8_t
DS1302::read(uint8_t addr)
{
  addr = ((addr << 1) | READ);
  uint8_t res = 0;
  asserted(m_cs) {
    write(addr);
    m_sda.set_mode(IOPin::INPUT_MODE);
    res = read();
    m_sda.set_mode(IOPin::OUTPUT_MODE);
  }  
  return (res);
}
  
void 
DS1302::write(uint8_t addr, uint8_t data)
{
  addr = ((addr << 1) | WRITE);
  asserted(m_cs) {
    write(addr);
    write(data);
  }
}

void 
DS1302::get_time(time_t& now)
{
  asserted(m_cs) {
    write(RTC_BURST | READ);
    m_sda.set_mode(IOPin::INPUT_MODE);
    now.seconds = read();
    now.minutes = read();
    now.hours = read();
    now.date = read();
    now.month = read();
    now.day = read();
    now.year = read();
    m_sda.set_mode(IOPin::OUTPUT_MODE);
  }  
}

void 
DS1302::set_time(time_t& now)
{
  set_write_protect(false);
  asserted(m_cs) {
    write(RTC_BURST | WRITE);
    write(now.seconds);
    write(now.minutes);
    write(now.hours);
    write(now.date);
    write(now.month);
    write(now.day);
    write(now.year);
  }
  set_write_protect(true);
}

void 
DS1302::read_ram(void* buf, size_t size)
{
  if (size == 0) return;
  uint8_t* bp = (uint8_t*) buf;
  if (size > RAM_MAX) size = RAM_MAX;
  asserted(m_cs) {
    write(RAM_BURST | READ);
    m_sda.set_mode(IOPin::INPUT_MODE);
    do *bp++ = read(); while (--size);
    m_sda.set_mode(IOPin::OUTPUT_MODE);
  }  
}

void 
DS1302::write_ram(void* buf, size_t size)
{
  if (size == 0) return;
  uint8_t* bp = (uint8_t*) buf;
  if (size > RAM_MAX) size = RAM_MAX;
  set_write_protect(false);
  asserted(m_cs) {
    write(RAM_BURST | WRITE);
    do write(*bp++); while (--size); 
  }
  set_write_protect(true);
}
