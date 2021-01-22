#include <stdio.h>
#include <stdlib.h>
#include "HX711.h"
#include "SerialTransfer.h"
SerialTransfer myTransfer;

// Force sensor definitions
#define CLK 31
#define DOUT1 23
#define DOUT2 24
#define DOUT3 25
#define DOUT4 26
#define DOUT5 27
#define DOUT6 22

// Initialize global params
boolean h = HIGH;
boolean l = LOW;
boolean n = LOW;
boolean check1 = false;
boolean check2 = false;
boolean check3 = false;
boolean check4 = false;
boolean check5 = false;
boolean check6 = false;

SerialTransfer myTransfer;
bool blink = 1;

int **piBuffer = NULL; //pointer to pointer
int nRow = 0; //variable store number of Row
int nColumn = 6; //variable store number of Row
int iRow = 0; //Variable for looping Row
int iCol = 0; //Variable for looping column
int rxRow = 0;

int flag=0;
int arr[6];
int row = 0;
int i;
int j=0;
int index_max;
int line;
double motorSpeed[6];
double error[6];
double motor_position_sensor[6];
double force_sensor[6];
double tx_sensor_data[12];
// Reference tolerance
int RefTol = 5;

// Initialize received motor-references
struct STRUCT {
  int16_t len;
  int16_t len_sign;
  int16_t m1;
  int16_t m1_sign;
  int16_t m2;
  int16_t m2_sign;
  int16_t m3;
  int16_t m3_sign;
  int16_t m4;
  int16_t m4_sign;
  int16_t m5;
  int16_t m5_sign;
  int16_t m6;
  int16_t m6_sign;
} motorStruct;

// Actuator 1 param
HX711 scale1;
const int inb1 = 5;
const int ina1 = 6;
const int pwm1 = 4;
const int ena1 = 3;
const int enb1 = 2;
float calibration_factor1 = -14690;

// Actuator 2 param
HX711 scale2;
const int inb2 = 9;
const int ina2 = 10;
const int pwm2 = 13;
const int ena2 = 8;
const int enb2 = 7;
float calibration_factor2 = -14780;

// Actuator 3 param
HX711 scale3;
const int inb3 = 51;
const int ina3 = 50;
const int pwm3 = 46;
const int ena3 = 52;
const int enb3 = 53;
float calibration_factor3 = -14630;

// Actuator 4 param
HX711 scale4;
const int inb4 = 47;
const int ina4 = 44;
const int pwm4 = 45;
const int ena4 = 48;
const int enb4 = 49;
float calibration_factor4 = -14690;

// Actuator 5 param
HX711 scale5;
const int inb5 = 41;
const int ina5 = 40;
const int pwm5 = 11;
const int ena5 = 42;
const int enb5 = 43;
float calibration_factor5 = -14550;

// Actuator 6 param
HX711 scale6;
const int inb6 = 15;
const int ina6 = 14;
const int pwm6 = 12;
const int ena6 = 16;
const int enb6 = 17;
float calibration_factor6 = -14700;

void setup() {
  Serial.begin(115200);
  myTransfer.begin(Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  // PWM Pins
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  pinMode(pwm5, OUTPUT);
  pinMode(pwm6, OUTPUT);

  // Other driver pins
  pinMode(ina1, OUTPUT);
  pinMode(inb1, OUTPUT);
  pinMode(ena1, INPUT);
  pinMode(enb1, INPUT);

  pinMode(ina2, OUTPUT);
  pinMode(inb2, OUTPUT);
  pinMode(ena2, INPUT);
  pinMode(enb2, INPUT);

  pinMode(ina3, OUTPUT);
  pinMode(inb3, OUTPUT);
  pinMode(ena3, INPUT);
  pinMode(enb3, INPUT);

  pinMode(ina4, OUTPUT);
  pinMode(inb4, OUTPUT);
  pinMode(ena4, INPUT);
  pinMode(enb4, INPUT);

  pinMode(ina5, OUTPUT);
  pinMode(inb5, OUTPUT);
  pinMode(ena5, INPUT);
  pinMode(enb5, INPUT);

  pinMode(ina6, OUTPUT);
  pinMode(inb6, OUTPUT);
  pinMode(ena6, INPUT);
  pinMode(enb6, INPUT);

  // Motor-position sensor input
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);

  // Interrupt
  TCCR2A |= 0x00;
  TCCR2B |= 0x00;
  TCCR2A |= _BV(WGM21) | _BV(COM2A0);
  // Following set the interrupt timer rate
  TCCR2B = _BV(CS22) | _BV(CS21) | _BV(CS20);
  TIMSK2 |= _BV(OCIE2A);

  // Timer 0
  TCCR0A = 0x00;
  TCCR0B = 0x00;
  TCCR0A |= (1 << WGM00) | (1 << WGM01);
  TCCR0A |= (1 << COM0B1) | (1 << COM0A1);
  TCCR0B |= (1 << CS01) | (1 << CS00);
  OCR0A = map(0, 0, 100, 0, 255); // Actuator 2
  OCR0B = map(0, 0, 100, 0, 255); // Actuator 1

  // Timer 1
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCCR1A |= _BV(WGM10) | _BV(COM1A1) | _BV(COM1B1);
  TCCR1B |= _BV(WGM12) | _BV(CS10) | _BV(CS11);
  OCR1A = map(0, 0, 100, 0, 255); // Actuator 5
  OCR1B = map(0, 0, 100, 0, 255); // Actuator 6

  // Timer 5
  TCCR5A = 0x00;
  TCCR5B = 0x00;
  TCCR5A |= _BV(COM5A1) | _BV(COM5B1) | _BV(WGM50);
  TCCR5B |= _BV(WGM52) | _BV(CS50) | _BV(CS51);
  OCR5A = map(0, 0, 100, 0, 255); // Actuator 3
  OCR5B = map(0, 0, 100, 0, 255); // Actuator 4

  // Load cell amplifier digital input and calibration
  scale1.begin(DOUT1, CLK);
  scale2.begin(DOUT2, CLK);
  scale3.begin(DOUT3, CLK);
  scale4.begin(DOUT4, CLK);
  scale5.begin(DOUT5, CLK);
  scale6.begin(DOUT6, CLK);
  scale1.set_scale(calibration_factor1);
  scale2.set_scale(calibration_factor2);
  scale3.set_scale(calibration_factor3);
  scale4.set_scale(calibration_factor4);
  scale5.set_scale(calibration_factor5);
  scale6.set_scale(calibration_factor6);
}

void stop_motors()
{
  digitalWrite(ina6, l);
  digitalWrite(inb6, l);
  digitalWrite(ina5, l);
  digitalWrite(inb5, l);
  digitalWrite(ina4, l);
  digitalWrite(inb4, l);
  digitalWrite(ina3, l);
  digitalWrite(inb3, l);
  digitalWrite(ina2, l);
  digitalWrite(inb2, l);
  digitalWrite(ina1, l);
  digitalWrite(inb1, l);
}

void motorPositionRead() {
  motor_position_sensor[0] = analogRead(A1);
  motor_position_sensor[1] = analogRead(A2);
  motor_position_sensor[2] = analogRead(A3);
  motor_position_sensor[3] = analogRead(A4);
  motor_position_sensor[4] = analogRead(A5);
  motor_position_sensor[5] = analogRead(A6);
}

void forceSensorRead() {
  force_sensor[0] = scale1.get_units();
  force_sensor[1] = scale2.get_units();
  force_sensor[2] = scale3.get_units();
  force_sensor[3] = scale4.get_units();
  force_sensor[4] = scale5.get_units();
  force_sensor[5] = scale6.get_units();
}

void calculateErrorFromMotorStruct() {
  error[0] = motorStruct.m1 - motor_position_sensor[0];
  error[1] = motorStruct.m2 - motor_position_sensor[1];
  error[2] = motorStruct.m3 - motor_position_sensor[2];
  error[3] = motorStruct.m4 - motor_position_sensor[3];
  error[4] = motorStruct.m5 - motor_position_sensor[4];
  error[5] = motorStruct.m6 - motor_position_sensor[5];
}

void calculateError() {
  for (i=0; i<6; ++i) {
      error[i] = piBuffer[row][i] - motor_position_sensor[i];
  }
  i = 0;
}

void calculateMaxIndex() {
  index_max=0;
  for(i=0; i<6; ++i) {
        if(abs(error[i]) > abs(error[index_max])) {
            index_max=i;
        }
  }
  i=0;
}

void calculateMotorSpeed() {
  for (i=0; i<6; ++i) {
    motorSpeed[i] = abs(error[i] / error[index_max]) * 100;
  }
}

void serialPrintMotorPosition() {
  for (i=0; i<6; i++) {
    Serial.print(motor_position_sensor[i]);
    Serial.print("-");
    Serial.print(motorSpeed[i]);
    Serial.print(",");
  }
}

void motorControl(int motor_index, int ina, int inb, bool check) {
  int err_index = motor_index - 1;
  if (error[motor_index] > RefTol) {
    digitalWrite(ina, h);
    digitalWrite(inb, l);
  }
  if (error[err_index] < -RefTol) {
    digitalWrite(ina, l);
    digitalWrite(inb, h);
  }
  if (error[err_index] < RefTol && error[err_index] > -RefTol) {
    digitalWrite(ina, l);
    digitalWrite(inb, l);
    check = true;
  }
}

void allMotorControl() {
  motorControl(1, ina1, inb1, check1);
  motorControl(2, ina2, inb2, check2);
  motorControl(3, ina3, inb3, check3);
  motorControl(4, ina4, inb4, check4);
  motorControl(5, ina5, inb5, check5);
  motorControl(6, ina6, inb6, check6);
}

void applyMotorVelocities() {
  // Only want to apply once per reference-row
  if(j==0) {
    OCR0B = map(motorSpeed[0], 0, 100, 0, 255); // Actuator 1
    OCR0A = map(motorSpeed[1], 0, 100, 0, 255); // Actuator 2
    OCR5A = map(motorSpeed[2], 0, 100, 0, 255); // Actuator 3
    OCR5B = map(motorSpeed[3], 0, 100, 0, 255); // Actuator 4
    OCR1B = map(motorSpeed[5], 0, 100, 0, 255); // Actuator 6
    OCR1A = map(motorSpeed[4], 0, 100, 0, 255); // Actuator 5
    j=1;
  }
}


bool isPositionReachedCheck() {
  // This makes the program stop after reaching the reference.
  if(check1==true && check2==true && check3==true && check4==true && check5==true && check6==true) {
      row++;
      check1=false;
      check2=false;
      check3=false;
      check4=false;
      check5=false;
      check6=false;
      return true;
  }
  return false;
}

void rowCountCheck(int lastRowIndex) {
  // Reset the row number to redo it all
  if(row==lastRowIndex) {
      row=0;
  }
}

void serialPrintMotorStruct() {
    Serial.print(motorStruct.m1);
    Serial.print(",");
    Serial.print(motorStruct.m2);
    Serial.print(",");
    Serial.print(motorStruct.m3);
    Serial.print(",");
    Serial.print(motorStruct.m4);
    Serial.print(",");
    Serial.print(motorStruct.m5);
    Serial.print(",");
    Serial.print(motorStruct.m6);
    Serial.print("|");
}

void forceSecurityCheck(int limit, int option) {
  for(i=0; i<6; ++i) {
    if (abs(force_sensor[i]) > limit) {
      //stop_motors();

      // Go back to default position
      motorStruct.m1 = 0;
      motorStruct.m2 = 0;
      motorStruct.m3 = 0;
      motorStruct.m4 = 0;
      motorStruct.m5 = 0;
      motorStruct.m6 = 0;
      calculateErrorFromMotorStruct();
      calculateMaxIndex();
      calculateMotorSpeed();
      serialPrintMotorPosition();
      allMotorControl();
      isPositionReachedCheck();

      if (option = 1) {
        delay(100000);
      }
      else if (option = 2) {
        forceSecurityCheck(limit, 2);
      }
    }
  }
}

void serialReadRowControlThenSendData() {
  // ToDo: Pass pointer to function as argument
  // Setup serial transfer
  myTransfer.begin(Serial);

  if(myTransfer.available()) {
    int16_t recSize = 0;
    recSize = myTransfer.rxObj(motorStruct, recSize);

    velocityControlTestSerialRows();

    uint16_t sendSize = 0;
    sendSize = myTransfer.txObj(tx_sensor_data, sendSize);
    myTransfer.sendData(sendSize);
  }
}

void appendSensorDataToArray(){
  // TODO: Append all sensor data to a final sensor-matrix to be sent?
  for (i=0; i<6; i++) {
    tx_sensor_data[i] = motor_position_sensor[i];
    tx_sensor_data[i+6] = force_sensor[i];
  }
}

void velocityControlTestSerialRows() {
  bool positionCheck = isPositionReachedCheck();
  while (positionCheck == false) {
    motorPositionRead();
    forceSensorRead();
    forceSecurityCheck(200, 2);
    calculateErrorFromMotorStruct();
    calculateMaxIndex();
    calculateMotorSpeed();
    serialPrintMotorPosition();
    allMotorControl();
    appendSensorDataToArray();
    positionCheck = isPositionReachedCheck();
  }
}

void velocityControlTest1() {
  // Need to import hardcoded matrix again to work
  motorPositionRead();
  calculateError();
  calculateMaxIndex();
  calculateMotorSpeed();
  serialPrintMotorPosition();
  allMotorControl();
  isPositionReachedCheck();
  rowCountCheck(nRow-1);
}

//Free Allocated memory
void freeAllocatedMemory(int **piBuffer, int nRow)
{
  int iRow = 0;
  for (iRow = 0; iRow < nRow; iRow++)
  {
    free(piBuffer[iRow]); // free allocated memory
  }
  free(piBuffer);
}

void send_all_received_refs() {
  for (int i = 0; i < nRow; i++) {
    for (int k = 0; k < 6; k++) {
      arr[k] = piBuffer[i][k];
    }
    myTransfer.packet.txBuff[i] = arr[0];
    uint16_t sendSize = 0;
    sendSize = myTransfer.txObj(arr, sendSize);
    myTransfer.sendData(myTransfer.bytesRead);
    delay(500);
    blink = !blink;
    digitalWrite(LED_BUILTIN, blink);

    // Clean up
    //for (iRow =0 ; iRow < nRow ; iRow++) {
    //      freeAllocatedMemory(piBuffer,iRow);
    //}
  }
}

void loop() {
  
  // Store received rows in a matrix
  if (myTransfer.available()) {
    flag=0;
    int16_t recSize = 0;
    recSize = myTransfer.rxObj(motorStruct, recSize);

    if (rxRow == 0) {
      digitalWrite(LED_BUILTIN, HIGH);
      nRow = motorStruct.len;
      piBuffer = (int **)malloc(nRow * sizeof(int*));

      //Allocate memory for column
      for (iRow = 0 ; iRow < nRow ; iRow++) {
        piBuffer[iRow] = (int *)malloc(nColumn * sizeof(int));

        //Check memory validity
        if (piBuffer[iRow] == NULL) {
          freeAllocatedMemory(piBuffer, iRow);
        }
      }

      piBuffer[rxRow][0] = (int)motorStruct.m1;
      piBuffer[rxRow][1] = (int)motorStruct.m2;
      piBuffer[rxRow][2] = (int)motorStruct.m3;
      piBuffer[rxRow][3] = (int)motorStruct.m4;
      piBuffer[rxRow][4] = (int)motorStruct.m5;
      piBuffer[rxRow][5] = (int)motorStruct.m6;
      rxRow++;
    } else if (rxRow > 0) {
      piBuffer[rxRow][0] = (int)motorStruct.m1;
      piBuffer[rxRow][1] = (int)motorStruct.m2;
      piBuffer[rxRow][2] = (int)motorStruct.m3;
      piBuffer[rxRow][3] = (int)motorStruct.m4;
      piBuffer[rxRow][4] = (int)motorStruct.m5;
      piBuffer[rxRow][5] = (int)motorStruct.m6;
      rxRow++;
      blink = !blink;
      digitalWrite(LED_BUILTIN, blink);
    }
  }

  // Run only if all rows have been sent
  if (rxRow == nRow-1) {
    digitalWrite(LED_BUILTIN, LOW);
    send_all_received_refs();
    rxRow = 0;
    flag=1;
  }
}

// Interrupt function
ISR(TIMER2_COMPA_vect) {
  // velocityControlTest1();
  if(flag==1){
  serialReadRowControlThenSendData();
  }
}
