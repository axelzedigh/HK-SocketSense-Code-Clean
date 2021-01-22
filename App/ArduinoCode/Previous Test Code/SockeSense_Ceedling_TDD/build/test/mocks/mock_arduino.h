/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_ARDUINO_H
#define _MOCK_ARDUINO_H

#include "unity.h"
#include "arduino.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_arduino_Init(void);
void mock_arduino_Destroy(void);
void mock_arduino_Verify(void);




#define analogRead_IgnoreAndReturn(cmock_retval) analogRead_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void analogRead_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, double cmock_to_return);
#define analogRead_StopIgnore() analogRead_CMockStopIgnore()
void analogRead_CMockStopIgnore(void);
#define analogRead_ExpectAndReturn(analogPin, cmock_retval) analogRead_CMockExpectAndReturn(__LINE__, analogPin, cmock_retval)
void analogRead_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, int analogPin, double cmock_to_return);
typedef double (* CMOCK_analogRead_CALLBACK)(int analogPin, int cmock_num_calls);
void analogRead_AddCallback(CMOCK_analogRead_CALLBACK Callback);
void analogRead_Stub(CMOCK_analogRead_CALLBACK Callback);
#define analogRead_StubWithCallback analogRead_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif