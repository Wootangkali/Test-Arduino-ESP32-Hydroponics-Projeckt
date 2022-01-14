/**
 * @file Cosa/IOStream.cpp
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
 * This file is part of the Arduino Che Cosa project.
 */

#include "Cosa/IOStream.hh"
#include "Cosa/Power.hh"
#include <ctype.h>

const char IOStream::CR[] __PROGMEM = "\n";
const char IOStream::LF[] __PROGMEM = "\r";
const char IOStream::CRLF[] __PROGMEM = "\r\n";

IOStream::IOStream(Device* dev) : 
  m_dev(dev),
  m_base(dec),
  m_width(6),
  m_prec(4),
  m_eol_P((str_P) CRLF)
{}

IOStream::IOStream() : 
  m_dev(NULL),
  m_base(dec),
  m_width(6),
  m_prec(4),
  m_eol_P((str_P) CRLF)
{}

IOStream::Device* 
IOStream::set_device(Device* dev) 
{ 
  if (dev == NULL) return (m_dev);
  Device* previous = m_dev;
  m_dev = dev;
  return (previous);
}

void 
IOStream::print(int n, Base base) 
{
  if (base != bcd) {
    if (base != dec) print_prefix(base);
    char buf[sizeof(int) * CHARBITS + 1];
    print(itoa(n, buf, base));
  }
  else {
    print((char) ('0' + ((n >> 4) & 0xf)));
    print((char) ('0' + (n & 0xf)));
  }
}

void 
IOStream::print(long int n, Base base)
{
  if (base != dec) print_prefix(base);
  char buf[sizeof(long int) * CHARBITS + 1];
  print(ltoa(n, buf, base));
}

void 
IOStream::print(unsigned int n, Base base) 
{
  if (base != dec) print_prefix(base);
  char buf[sizeof(int) * CHARBITS + 1];
  print(utoa(n, buf, base));
}

void 
IOStream::print(unsigned long int n, Base base)
{
  if (base != dec) print_prefix(base);
  char buf[sizeof(long int) * CHARBITS + 1];
  print(ultoa(n, buf, base));
}

void 
IOStream::print(unsigned int n, uint8_t digits, Base base) 
{
  char buf[sizeof(int) * CHARBITS + 1];
  utoa(n, buf, base);
  for (uint8_t length = strlen(buf); length < digits; length++)
    print('0');
  print(buf);
}

void 
IOStream::print(unsigned long int n, uint8_t digits, Base base)
{
  char buf[sizeof(long int) * CHARBITS + 1];
  ultoa(n, buf, base);
  for (uint8_t length = strlen(buf); length < digits; length++)
    print('0');
  print(buf);
}

void 
IOStream::print(double value, int8_t width, uint8_t prec)
{
  const uint8_t BUF_MAX = 33;
  char buf[BUF_MAX];
  dtostrf(value, width, prec, buf);
  print(buf);
}

void 
IOStream::print(IOStream::Device* buffer)
{
  int c;
  while ((c = buffer->getchar()) != EOF)
    print((char) c);
}

void 
IOStream::print_prefix(Base base)
{
  if (base == hex)
    print_P(PSTR("0x"));
  else if (base == bin)
    print_P(PSTR("0b"));
  else if (base == oct)
    print_P(PSTR("0"));
}

void 
IOStream::print(uint32_t src, const void *ptr, size_t size, Base base, uint8_t max)
{
  Base b = (base != dec ? hex : dec);
  uint8_t w = (base == hex ? 2 : (base == bin ? 8 : 3));
  uint8_t* p = (uint8_t*) ptr;
  uint8_t n = 0;
  print(src, 6, b);
  print_P(PSTR(": "));
  while (size--) {
    print((unsigned int) *p++, w, base);
    src += 1;
    if (++n < max) {
      print_P(PSTR(" "));
    }
    else {
      println();
      n = 0;
      if (size > 0) {
	print(src, 6, b);
	print_P(PSTR(": "));
      }
    }
  }
  if (n != 0) println();
}

void 
IOStream::vprintf_P(str_P format, va_list args)
{
  const char* s = (const char*) format;
  uint8_t is_signed;
  Base base;
  char c;
  while ((c = pgm_read_byte(s++)) != 0) {
    if (c == '%') {
      is_signed = 1;
      base = dec;
    next:
      c = pgm_read_byte(s++);
      if (c == 0) s--;
      switch (c) {
      case 'b': 
	base = bin; 
	goto next;
      case 'B': 
	base = bcd; 
	goto next;
      case 'o': 
	base = oct; 
	goto next;
      case 'h':
      case 'x': 
	base = hex; 
	goto next;
      case 'u': 
	is_signed = 0; 
	goto next;
      case 'c': 
	print((char) va_arg(args, int)); 
	continue;
      case 'p': 
	print(va_arg(args, void*)); 
	continue;
      case 's': 
	print(va_arg(args, char*)); 
	continue;
      case 'S': 
	print_P(va_arg(args, str_P)); 
	continue;
      case 'd': 
	if (is_signed) 
	  print(va_arg(args, int), base); 
	else
	  print(va_arg(args, unsigned int), base); 
	continue;
      case 'l': 
	if (is_signed) 
	  print(va_arg(args, long int), base);
	else
	  print(va_arg(args, unsigned long int), base);
	continue;
      };
    }
    print(c);
  }
}

char* 
IOStream::scan(char *s, size_t count)
{
  if (m_dev == NULL) return (NULL);
  char* res = s;

  // Skip whitespace
  int c = m_dev->peekchar();
  while (c <= ' ' && c != '\n') {
    if (c == EOF) return (NULL);
    c = m_dev->getchar();
    c = m_dev->peekchar();
  }
  c = m_dev->getchar();

  // Scan the token; identifier, number or special character
  count -= 1;
  *s++ = c;
  if (isalpha(c)) {
    while (count--) {
      c = m_dev->peekchar();
      if (!isalnum(c)) break;
      c = m_dev->getchar();
      *s++ = c;
    }
  }
  else if (isdigit(c) || c == '-') {
    while (count--) {
      c = m_dev->peekchar();
      if (!isdigit(c)) break;
      c = m_dev->getchar();
      *s++ = c;
    }
  }
  *s = 0;
  return (res);
}

char*
IOStream::readline(char* buf, size_t size, bool echo)
{
  const char DEL = 127;
  const char ESC = 27;
  if (m_dev == NULL) return (NULL);
  int count = m_dev->available();
  if (count <= 0) return (NULL);
  size_t len = strlen(buf);
  char* s = buf + len;
  char c = 0;
  while (count--) {
    c = m_dev->getchar();
    if (c == ESC) continue;
    if (c == '\b' || c == DEL) {
      if (len > 0) {
	if (echo) print_P(PSTR("\b \b"));
	len -= 1;
	s -= 1;
      }
    }
    else {
      if (c == '\r') {
	if (echo) print(c);
	if (m_dev->get_eol() == CRLF_MODE) continue;
	c = '\n';
      }
      if (echo) print(c);
      if (len < size) {
	len += 1;
	*s++ = c;
      }
      if (c == '\n') break;
    }
  }
  *s = 0;
  return (c == '\n' ? buf : NULL);
}

// IOStream::Device IOStream::Device::null;

int 
IOStream::Device::available()
{
  return (0);
}

int 
IOStream::Device::room()
{
  return (0);
}

int 
IOStream::Device::putchar(char c) 
{ 
  int res = write(&c, sizeof(c));
  return (res == sizeof(c) ? c & 0xff : res);
}
    
int 
IOStream::Device::puts(const char* s) 
{ 
  return (write(s, strlen(s)));
}

int 
IOStream::Device::puts_P(str_P s)
{ 
  const char* p = (const char*) s;
  return (write_P(p, strlen_P(p)));
}

int 
IOStream::Device::write(const void* buf, size_t size) 
{ 
  char* bp = (char*) buf;
  size_t n = 0;
  for(; n < size; n++)
    if (putchar(*bp++) < 0)
      break;
  return (n);
}

int 
IOStream::Device::write_P(const void* buf, size_t size) 
{ 
  char* bp = (char*) buf;
  size_t n = 0;
  for(; n < size; n++)
    if (putchar(pgm_read_byte(bp++)) < 0)
      break;
  return (n);
}

int 
IOStream::Device::write(const iovec_t* vec)
{
  size_t size = 0;
  for (const iovec_t* vp = vec; vp->buf != NULL; vp++) {
    size_t res = (size_t) write(vp->buf, vp->size);
    if (res == 0) break;
    size += res;
  }
  return (size);
}

int 
IOStream::Device::peekchar() 
{ 
  return (EOF); 
}

int 
IOStream::Device::peekchar(char c) 
{ 
  UNUSED(c);
  return (EOF); 
}

int 
IOStream::Device::getchar() 
{ 
  return (EOF); 
}

char* 
IOStream::Device::gets(char *s, size_t count) 
{ 
  char* res = s;
  while (--count) {
    int c = getchar();
    if (c == EOF) {
      if (m_blocking) {
	while (c == EOF) {
	  yield();
	  c = getchar();
	}
      }
      else break;
    }
    if (c == '\r') {
      if (m_eol == CRLF_MODE) continue;
      c = '\n';
    }
    *s++ = c;
    if (c == '\n') break;
  }
  *s = 0;
  return (s == res ? NULL : res);
}

int 
IOStream::Device::read(void* buf, size_t size) 
{ 
  char* bp = (char*) buf;
  size_t n = 0; 
  for (; n < size; n++) {
    int c = getchar();
    if (c < 0) break;
    *bp++ = c;
  }
  return (n);
}

int 
IOStream::Device::read(iovec_t* vec) 
{
  size_t size = 0;
  for (const iovec_t* vp = vec; vp->buf != NULL; vp++) {
    size_t res = (size_t) read(vp->buf, vp->size);
    if (res == 0) break;
    size += res;
  }
  return (size);
}

int 
IOStream::Device::flush() 
{ 
  return (EOF); 
}

void
IOStream::Device::empty()
{
}
