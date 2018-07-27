/*
 * ------------------------------------------------------------------------
 *   File Name: debug.h
 *      Author: Zhao Yanbai
 *              2018-07-26 15:47:46 Thursday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

#pragma once

void debug();

// 在mac系统调用asm_debug会自动调用_asm_debug
// 在linux系统上会自动调用asm_debug
// 所以这里强制编译器生成的代码只能调用asm_debug
void asm_debug() asm("asm_debug");
