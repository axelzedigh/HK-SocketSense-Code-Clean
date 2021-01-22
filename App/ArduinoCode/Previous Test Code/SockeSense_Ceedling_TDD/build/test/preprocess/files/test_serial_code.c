#include "build/temp/_test_serial_code.c"
#include "src/PositionControlTDD.h"
#include "build/test/mocks/mock_arduino.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


























double motor_position_sensor[6] = {1,2,3,4,5,6};

int A1 = 1;

int A2 = 2;

int A3 = 3;

int A4 = 4;

int A5 = 5;

int A6 = 6;

void motorPositionRead(double motor_position_sensor[6]);











void setUp(void)

{



  analogRead_CMockExpectAndReturn(45, A1, 100);

  analogRead_CMockExpectAndReturn(46, A2, 200);

  analogRead_CMockExpectAndReturn(47, A3, 300);

  analogRead_CMockExpectAndReturn(48, A4, 400);

  analogRead_CMockExpectAndReturn(49, A5, 500);

  analogRead_CMockExpectAndReturn(50, A6, 600);

}



void tearDown(void)

{

}









void test_arduino_analog_read(void) {

  int retVal;





  retVal = analogRead(A1);

  UnityAssertEqualNumber((UNITY_INT)((retVal)), (UNITY_INT)((100)), (((void*)0)), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);

  retVal = analogRead(A2);

  UnityAssertEqualNumber((UNITY_INT)((retVal)), (UNITY_INT)((200)), (((void*)0)), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_INT);

  retVal = analogRead(A3);

  UnityAssertEqualNumber((UNITY_INT)((retVal)), (UNITY_INT)((300)), (((void*)0)), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_INT);

  retVal = analogRead(A4);

  UnityAssertEqualNumber((UNITY_INT)((retVal)), (UNITY_INT)((400)), (((void*)0)), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT);

  retVal = analogRead(A5);

  UnityAssertEqualNumber((UNITY_INT)((retVal)), (UNITY_INT)((500)), (((void*)0)), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);

  retVal = analogRead(A6);

  UnityAssertEqualNumber((UNITY_INT)((retVal)), (UNITY_INT)((600)), (((void*)0)), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT);

}



void test_motor_position_read(void) {





  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((1)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((1))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[0]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(81)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((2)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((2))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[1]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(82)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((3)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((3))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[2]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(83)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((4)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((4))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[3]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(84)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((5)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((5))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[4]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(85)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((6)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((6))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[5]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(86)));





  motorPositionRead(motor_position_sensor);



  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((100)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((100))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[0]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(91)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((200)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((200))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[1]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(92)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((300)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((300))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[2]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(93)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((400)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((400))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[3]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(94)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((500)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((500))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[4]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(95)));

  UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((600)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((600))), (UNITY_FLOAT)((UNITY_FLOAT)((motor_position_sensor[5]))), ((((void*)0))), (UNITY_UINT)((UNITY_UINT)(96)));

}
