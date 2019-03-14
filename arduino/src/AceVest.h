/*
 * ------------------------------------------------------------------------
 *   File Name: AceVest.h
 *      Author: Zhao Yanbai
 *              2018-12-14 12:14:38 Friday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

#pragma once
#include <stdint.h>
#include <Arduino.h>

#if defined(__GNUC__) && defined(__AVR__)
#  define ACEVEST_FONT_SECTION(name) ACEVEST_SECTION(".progmem." name)
#  define ACEVEST_PROGMEM PROGMEM
#endif

#if defined(ESP8266)
#  define ACEVEST_FONT_SECTION(name) __attribute__((section(".text." name)))
#  define ACEVEST_PROGMEM
#endif

#ifndef ACEVEST_FONT_SECTION
#  define ACEVEST_FONT_SECTION(name)
#endif


extern const uint8_t font_acevest[] ACEVEST_FONT_SECTION("font_acevest");

typedef struct {
  String ssid;
  String pwd;
} WiFiItem_t;
