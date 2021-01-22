#include "HX711.h"

// Force sensor definitions
#define CLK 31
#define DOUT1 23
#define DOUT2 24
#define DOUT3 25
#define DOUT4 26
#define DOUT5 27
#define DOUT6 22

// Initialize global params
bool h = HIGH;
bool l = LOW;
bool n = LOW;
bool check1 = false;
bool check2 = false;
bool check3 = false;
bool check4 = false;
bool check5 = false;
bool check6 = false;
bool check_array[] = {0,0,0,0,0,0};
bool motor_speed_applied = false;
bool matrix_downloaded = false;
bool program_done = false;
int read_row = 0;
int index_max;
int nRow = 0; //variable store number of Row
int rxRow = 0;
int arr[6];

int stop_program = false;
int matrix_len;
int16_t ref1;
int16_t ref2;
int16_t ref3;
int16_t ref4;
int16_t ref5;
int16_t ref6;
int millis_time;
char refs[40];

char stop_program_char[1];
char matrix_len_char[5];
char ref1_char[5];
char ref2_char[5];
char ref3_char[5];
char ref4_char[5];
char ref5_char[5];
char ref6_char[5];

char millis_time_char[10];
char program_done_char[10];
char pos1_char[5];
char pos2_char[5];
char pos3_char[5];
char pos4_char[5];
char pos5_char[5];
char pos6_char[5];
char force1_char[5];
char force2_char[5];
char force3_char[5];
char force4_char[5];
char force5_char[5];
char force6_char[5];
char comma[1] = {','};

char sensor_arr[40];
int refMatrix[100][6];

double motor_speed[6];
double error[6];
double motor_position_sensor[6];
double force_sensor[6];
double tx_sensor_data[14];
int RefTol = 5;

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

  

  // Interrupt
  TCCR2A |= 0x00;
  TCCR2B |= 0x00;
  TCCR2A |= _BV(WGM21) | _BV(COM2A0);
  // Following set the interrupt timer rate
  TCCR2B = _BV(CS22) | _BV(CS21) | _BV(CS20);
  TIMSK2 |= _BV(OCIE2A);
}

void loop() {
  
}

// Interrupt function
ISR(TIMER2_COMPA_vect) {
  rxMatrixViaSerial();
  velocityControl();
}

void is_matrix_downloaded(int &rxRow) {
  if (rxRow == nRow) {
    matrix_downloaded = true;
  }
}

void rxMatrixViaSerial() {
  while (matrix_downloaded == false) {
    if (Serial.available()) {
      Serial.readString().toCharArray(refs, 40);
      parseData();
      append_to_matrix(rxRow);
      //convert_matrix_int_to_char(rxRow);
      change_val_increase(rxRow);
      is_matrix_downloaded(rxRow);
      //append_to_sensor_arr_and_send();
    }
  }
}

void velocityControl() {
  
  if (program_done == false) {
    
    forceSensorRead();
    motorPositionRead();
    //serialPrintMotorPosition();
    //forceSecurityCheck(2);

    calculateError(read_row);
    calculateMotorSpeed();
    allMotorControlDirection();

    if (motor_speed_applied == false) {
      applyMotorVelocities();
      motor_speed_applied = true;
    }

    isPositionReachedCheck();
    rowCountCheck(nRow, read_row);

    sendSensorDataToPC();
  }
}

void forceSensorRead() {
  force_sensor[0] = scale1.get_units();
  force_sensor[1] = scale2.get_units();
  force_sensor[2] = scale3.get_units();
  force_sensor[3] = scale4.get_units();
  force_sensor[4] = scale5.get_units();
  force_sensor[5] = scale6.get_units();
}

void motorPositionRead() {
  motor_position_sensor[0] = analogRead(A1);
  motor_position_sensor[1] = analogRead(A2);
  motor_position_sensor[2] = analogRead(A3);
  motor_position_sensor[3] = analogRead(A4);
  motor_position_sensor[4] = analogRead(A5);
  motor_position_sensor[5] = analogRead(A6);
  millis_time = millis();
}

void calculateError(int &read_row) {
  for (int i=0; i<6; ++i) {
      error[i] = refMatrix[read_row][i] - motor_position_sensor[i];
  }
}

void calculateMotorSpeed() {
  index_max=0;
  for(int i=0; i<6; ++i) {
        if(abs(error[i]) > abs(error[index_max])) {
            index_max=i;
        }
  }

  for (int i=0; i<6; ++i) {
    motor_speed[i] = abs(error[i] / error[index_max]) * 70;
    if (motor_speed[i] < 40){
      motor_speed[i] = 40;
    } else if (motor_speed[i] > 60) {
      motor_speed[i] = 60;
    }
  }
}

void serialPrintMotorPosition() {
  for (int i=0; i<6; i++) {
    Serial.print(motor_position_sensor[i]);
    Serial.print("-");
    Serial.print(motor_speed[i]);
    Serial.print(",");
  }
}

void motorControl(int motor_index, int ina, int inb) {
  int err_index = motor_index - 1;
  if (error[err_index] > RefTol) {
    digitalWrite(ina, h);
    digitalWrite(inb, l);
  }
  else if (error[err_index] < -RefTol) {
    digitalWrite(ina, l);
    digitalWrite(inb, h);
  }
  else if (error[err_index] <= RefTol && error[err_index] >= -RefTol) {
    digitalWrite(ina, l);
    digitalWrite(inb, l);
    check_array[err_index] = true;
    //check = true;
  }
}

void allMotorControlDirection() {
  motorControl(1, ina1, inb1);
  motorControl(2, ina2, inb2);
  motorControl(3, ina3, inb3);
  motorControl(4, ina4, inb4);
  motorControl(5, ina5, inb5);
  motorControl(6, ina6, inb6);
}

void applyMotorVelocities() {
  OCR0B = map(motor_speed[0], 0, 100, 0, 255); // Actuator 1
  OCR0A = map(motor_speed[1], 0, 100, 0, 255); // Actuator 2
  OCR5A = map(motor_speed[2], 0, 100, 0, 255); // Actuator 3
  OCR5B = map(motor_speed[3], 0, 100, 0, 255); // Actuator 4
  OCR1B = map(motor_speed[5], 0, 100, 0, 255); // Actuator 6
  OCR1A = map(motor_speed[4], 0, 100, 0, 255); // Actuator 5
}

bool checkArrayComparison(bool a[]) {
  bool b[] = {1,1,1,1,1,1};
  for(int i=0; i<6; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

bool isPositionReachedCheck() {
  if(checkArrayComparison(check_array)) {
      check_array[0] = false;
      check_array[1] = false;
      check_array[2] = false;
      check_array[3] = false;
      check_array[4] = false;
      check_array[5] = false;
      motor_speed_applied = false;
      change_val_increase(read_row);
      return true;
  }
  return false;
}

void rowCountCheck(int &lastRowIndex, int &read_row) {
  // Reset the row number to redo it all
  if(read_row==lastRowIndex) {
      read_row = 0;
      program_done = true;
  }
}

void forceSecurityCheck(int limit) {
  for(int i=0; i<6; ++i) {
    if (abs(force_sensor[i]) > limit) {
      stop_motors();
      for (;;) {};
    }
  }
}

void sendSensorDataToPC() {
  convert_sensor_int_to_char();
  append_to_sensor_arr_and_send();
  change_val_zero(rxRow);
}

void stop_motors() {
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

void change_val_increase(int &rxRow) {
  rxRow++;
}

void change_val_zero(int &rxRow) {
  rxRow = 0;
}

void append_to_matrix(int &rxRow) {
    refMatrix[rxRow][0] = ref1;
    refMatrix[rxRow][1] = ref2;
    refMatrix[rxRow][2] = ref3;
    refMatrix[rxRow][3] = ref4;
    refMatrix[rxRow][4] = ref5;
    refMatrix[rxRow][5] = ref6;
}

void convert_sensor_int_to_char() {
    itoa(motor_position_sensor[5], program_done_char, 10);
    itoa(millis_time, millis_time_char, 10);

    itoa(motor_position_sensor[0], pos1_char, 10);
    itoa(motor_position_sensor[1], pos2_char, 10);
    itoa(motor_position_sensor[2], pos3_char, 10);
    itoa(motor_position_sensor[3], pos4_char, 10);
    itoa(motor_position_sensor[4], pos5_char, 10);
    itoa(motor_position_sensor[5], pos6_char, 10);

    itoa(force_sensor[0], force1_char, 10);
    itoa(force_sensor[1], force2_char, 10);
    itoa(force_sensor[2], force3_char, 10);
    itoa(force_sensor[3], force4_char, 10);
    itoa(force_sensor[4], force5_char, 10);
    itoa(force_sensor[5], force6_char, 10);
}

void append_to_sensor_arr_and_send() {
    strcat(sensor_arr, program_done_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, millis_time_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, pos1_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, pos2_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, pos3_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, pos4_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, pos5_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, pos6_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, force1_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, force2_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, force3_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, force4_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, force5_char);
    strcat(sensor_arr, comma);
    strcat(sensor_arr, force6_char);
    strcat(sensor_arr, comma);
    Serial.print(sensor_arr);
    sensor_arr[0] = '\0';
}

void parseData() {
  char * strtokIndx;

  strtokIndx = strtok(refs,",");
  strcpy(stop_program_char, strtokIndx);
  stop_program = atoi(stop_program_char);
  
  strtokIndx = strtok(NULL,",");
  strcpy(matrix_len_char, strtokIndx);
  matrix_len = atoi(matrix_len_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref1_char, strtokIndx);
  ref1 = atoi(ref1_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref2_char, strtokIndx);
  ref2 = atoi(ref2_char);
  
  strtokIndx = strtok(NULL,",");
  strcpy(ref3_char, strtokIndx);
  ref3 = atoi(ref3_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref4_char, strtokIndx);
  ref4 = atoi(ref4_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref5_char, strtokIndx);
  ref5 = atoi(ref5_char);

  strtokIndx = strtok(NULL,",");
  strcpy(ref6_char, strtokIndx);
  ref6 = atoi(ref6_char);
}
