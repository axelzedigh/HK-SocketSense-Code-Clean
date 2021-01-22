/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/

//-- unity: unit test framework
#include "unity.h"

//-- module being tested (mocked)
#include "mock_arduino.h"
#include "mock_HX711.h"

//-- Actual src code
#include "PositionControlTDD.h"

/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

double motor_position_sensor[6] = {1,2,3,4,5,6};
double force_sensor[6];
int A1 = 1;
int A2 = 2;
int A3 = 3;
int A4 = 4;
int A5 = 5;
int A6 = 6;
HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;
HX711 scale5;
HX711 scale6;

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/


/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/
void motorPositionRead(double motor_position_sensor[6]);
void forceSensorRead();

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
  // Mock arduino function
  analogRead_ExpectAndReturn(A1, 100);
  analogRead_ExpectAndReturn(A2, 200);
  analogRead_ExpectAndReturn(A3, 300);
  analogRead_ExpectAndReturn(A4, 400);
  analogRead_ExpectAndReturn(A5, 500);
  analogRead_ExpectAndReturn(A6, 600);

  // Mock HX711
  scale1.get_units_ExpectAndReturn(100);
  scale2.get_units_ExpectAndReturn(200);
  scale3.get_units_ExpectAndReturn(300);
  scale4.get_units_ExpectAndReturn(400);
  scale5.get_units_ExpectAndReturn(500);
  scale6.get_units_ExpectAndReturn(600);
}

void tearDown(void)
{
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_arduino_analog_read(void) {
  int retVal;
  
  // Test arduinoRead-mock
  retVal = analogRead(A1);
  TEST_ASSERT_EQUAL_INT(retVal, 100);
  retVal = analogRead(A2);
  TEST_ASSERT_EQUAL_INT(retVal, 200);
  retVal = analogRead(A3);
  TEST_ASSERT_EQUAL_INT(retVal, 300);
  retVal = analogRead(A4);
  TEST_ASSERT_EQUAL_INT(retVal, 400);
  retVal = analogRead(A5);
  TEST_ASSERT_EQUAL_INT(retVal, 500);
  retVal = analogRead(A6);
  TEST_ASSERT_EQUAL_INT(retVal, 600);
}

void test_motor_position_read(void) {
  // Test first initialized values
  TEST_ASSERT_EQUAL_FLOAT(1, motor_position_sensor[0]);
  TEST_ASSERT_EQUAL_FLOAT(2, motor_position_sensor[1]);
  TEST_ASSERT_EQUAL_FLOAT(3, motor_position_sensor[2]);
  TEST_ASSERT_EQUAL_FLOAT(4, motor_position_sensor[3]);
  TEST_ASSERT_EQUAL_FLOAT(5, motor_position_sensor[4]);
  TEST_ASSERT_EQUAL_FLOAT(6, motor_position_sensor[5]);

  // Test motorPositionRead()
  motorPositionRead(motor_position_sensor);

  TEST_ASSERT_EQUAL_FLOAT(100, motor_position_sensor[0]);
  TEST_ASSERT_EQUAL_FLOAT(200, motor_position_sensor[1]);
  TEST_ASSERT_EQUAL_FLOAT(300, motor_position_sensor[2]);
  TEST_ASSERT_EQUAL_FLOAT(400, motor_position_sensor[3]);
  TEST_ASSERT_EQUAL_FLOAT(500, motor_position_sensor[4]);
  TEST_ASSERT_EQUAL_FLOAT(600, motor_position_sensor[5]);
}

void test_force_sensor_read(void) {
}

