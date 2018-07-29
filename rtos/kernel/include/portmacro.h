/*
 * ------------------------------------------------------------------------
 *   File Name: portmacro.h
 *      Author: Zhao Yanbai
 *              2018-07-28 13:25:04 Saturday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

#pragma once

#define portCHAR        int8_t
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        int32_t
#define portSHORT       int16_t
#define portSTACK_TYPE  uint8_t
#define portBASE_TYPE   int

typedef portSTACK_TYPE          StackType_t;
typedef portBASE_TYPE           BaseType_t;
typedef unsigned portBASE_TYPE  UBaseType_t;

typedef uint32_t TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffffffffUL

#define portBYTE_ALIGNMENT 4
#define portSTACK_GROWTH            ( -1 )
#define portTICK_PERIOD_MS          ( ( TickType_t ) 1000 / 100)

// TODO BELOW
#define portYIELD()


// Need to Modify, see esp idf source code
#define portENTER_CRITICAL()
#define portEXIT_CRITICAL()


#define portDISABLE_INTERRUPTS()
#define portENABLE_INTERRUPTS()

#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )
