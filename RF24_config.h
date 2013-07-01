
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 Many modifications for use with teensy3x but far for being optimized.
 Modifications by Max MC Costa (sumotoy)
 */

#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__


#include <Arduino.h>

/*
turning this off will save a lot of ram/eeprom but you cannot debug anymore
*/
#define PRINTFENABLED

#include <stddef.h>

//detect teensy3 and over
#if defined(__arm__) && defined(CORE_TEENSY)
	#define TEENSY3X
	#ifdef PRINTFENABLED
		#include <stdarg.h>
	#endif
#endif

// Stuff that is normally provided by Arduino
#ifdef ARDUINO || defined(TEENSY3X)
	#include <SPI.h>
#else
	#include <stdint.h>
	#include <stdio.h>
	#include <string.h>
	extern HardwareSPI SPI;
	#define _BV(x) (1<<(x))
#endif

#undef SERIAL_DEBUG
#ifdef SERIAL_DEBUG
	#define IF_SERIAL_DEBUG(x) ({x;})
#else
	#define IF_SERIAL_DEBUG(x)
#endif



// Avoid spurious warnings
#if 1
	#if !defined(NATIVE) && defined(ARDUINO)
		#undef PROGMEM
		#if defined(TEENSY3X)
			#define PROGMEM __attribute__(( section(".data") ))
		#else
			#define PROGMEM __attribute__(( section(".progmem.data") ))
		#endif
		#undef PSTR
		#ifdef PRINTFENABLED
			#if defined(TEENSY3X)
				#define PSTR(s) (__extension__({static const char __c[] = (s); &__c[0];}))
			#else
				#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
			#endif
		#endif
	#endif
#endif

// Progmem is Arduino-specific
#if defined(TEENSY3X)
	//typedef char const char;
	//typedef uint16_t prog_uint16_t;
	#ifdef PRINTFENABLED
		#define PSTR(x) (x)
		#define printf_P kprintf
	#endif
	#define strlen_P strlen
	//#define PROGMEM
	#define pgm_read_word(p) (*(p)) 
	#define PRIPSTR "%s"
#elif defined(ARDUINO)
	#include <avr/pgmspace.h>
	#define PRIPSTR "%S"
#else
	typedef char const char;
	typedef uint16_t prog_uint16_t;
	#ifdef PRINTFENABLED
		#define PSTR(x) (x)
		#define printf_P printf
	#endif
	#define strlen_P strlen
	#define PROGMEM
	#define pgm_read_word(p) (*(p)) 
	#define PRIPSTR "%s"
#endif

#endif // __RF24_CONFIG_H__
// vim:ai:cin:sts=2 sw=2 ft=cpp
