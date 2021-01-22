//actuator 1 param
const int inb1 = 5;
const int ina1 = 6;
const int pwm1 = 4;
const int ena1 = 3;
const int enb1 = 2;
float calibration_factor1 = -14690;
boolean h = HIGH;
boolean l = LOW;
boolean n = LOW;
boolean check1 = false;
boolean check2 = false;
boolean check3 = false;
boolean check4 = false;
boolean check5 = false;
boolean check6 = false;
int number = 0;
int i;
int j=0;
int index_max;
int line;

//actuator 2 param
const int inb2 = 9;
const int ina2 = 10;
const int pwm2 = 13;
const int ena2 = 8;
const int enb2 = 7;
float calibration_factor2 = -14780;

//actuator 3 param
const int inb3 = 51;
const int ina3 = 50;
const int pwm3 = 46;
const int ena3 = 52;
const int enb3 = 53;
float calibration_factor3 = -14630;

//actuator 4 param
const int inb4 = 47;
const int ina4 = 44;
const int pwm4 = 45;
const int ena4 = 48;
const int enb4 = 49;
float calibration_factor4 = -14690;

//actuator 5 param
const int inb5 = 41;
const int ina5 = 40;
const int pwm5 = 11;
const int ena5 = 42;
const int enb5 = 43;
float calibration_factor5 = -14550;

//actuator 6 param
const int inb6 = 15;
const int ina6 = 14;
const int pwm6 = 12;
const int ena6 = 16;
const int enb6 = 17;
float calibration_factor6 = -14700;

// Check all the references - (minus) sensor values = this will give you 6 differenet distances, one for each motor.
// distans1, distans2, distans3, distans4, distans5, distans6
// Sort them from longest to shortest
// The longest distans (say distans1) should have MotorSpeed1 = max speed (Set maxSpeed as a variable (not 100 pwm))
// Next distance (say distans2) should have MotorSpeed2 = ( distans2/distans1 ) * maxSpeed. (if its float number change to int.)
// Do the same for each MotorSpeedX.
// MotorSpeed variables should only change with new reference. 
// This way all the motors should reach it's references appprox. at the same time.
// This is tho only usefull if the calculated distances are not relatively small.

double refMotor[37][6]; // How many references you send
double motorSpeed[6];
double error[6];
double sensor[6];

int RefTol = 5;  /// Reference tolerance




void setup() {
  Serial.begin(115200);
  //reference in mm*10
  refMotor[0][0] = 500;  // Reference
  refMotor[0][1] = 500;  // Reference
  refMotor[0][2] = 500;  // Reference
  refMotor[0][3] = 500;  // Reference
  refMotor[0][4] = 500;  // Reference
  refMotor[0][5] = 500;  // Reference

  refMotor[1][0] = 488;  // Reference
  refMotor[1][1] = 512;  // Reference
  refMotor[1][2] = 488;  // Reference
  refMotor[1][3] = 512;  // Reference
  refMotor[1][4] = 488;  // Reference
  refMotor[1][5] = 512;  // Reference

  refMotor[2][0] = 476;  // Reference
  refMotor[2][1] = 524;  // Reference
  refMotor[2][2] = 476;  // Reference
  refMotor[2][3] = 524;  // Reference
  refMotor[2][4] = 476;  // Reference
  refMotor[2][5] = 524;  // Reference

  refMotor[3][0] = 465;  // Reference
  refMotor[3][1] = 536;  // Reference
  refMotor[3][2] = 465;  // Reference
  refMotor[3][3] = 536;  // Reference
  refMotor[3][4] = 465;  // Reference
  refMotor[3][5] = 536;  // Reference

  refMotor[4][0] = 455;  // Reference
  refMotor[4][1] = 561;  // Reference
  refMotor[4][2] = 455;  // Reference
  refMotor[4][3] = 561;  // Reference
  refMotor[4][4] = 455;  // Reference
  refMotor[4][5] = 561;  // Reference

  refMotor[5][0] = 445;  // Reference
  refMotor[5][1] = 561;  // Reference
  refMotor[5][2] = 445;  // Reference
  refMotor[5][3] = 561;  // Reference
  refMotor[5][4] = 445;  // Reference
  refMotor[5][5] = 561;  // Reference

  refMotor[6][0] = 436;  // Reference
  refMotor[6][1] = 573;  // Reference
  refMotor[6][2] = 436;  // Reference
  refMotor[6][3] = 573;  // Reference
  refMotor[6][4] = 436;  // Reference
  refMotor[6][5] = 573;  // Reference

  refMotor[7][0] = 427;  // Reference
  refMotor[7][1] = 584;  // Reference
  refMotor[7][2] = 427;  // Reference
  refMotor[7][3] = 584;  // Reference
  refMotor[7][4] = 427;  // Reference
  refMotor[7][5] = 584;  // Reference

  refMotor[8][0] = 419;  // Reference
  refMotor[8][1] = 595;  // Reference
  refMotor[8][2] = 419;  // Reference
  refMotor[8][3] = 595;  // Reference
  refMotor[8][4] = 419;  // Reference
  refMotor[8][5] = 595;  // Reference

  refMotor[9][0] = 412;  // Reference
  refMotor[9][1] = 606;  // Reference
  refMotor[9][2] = 412;  // Reference
  refMotor[9][3] = 606;  // Reference
  refMotor[9][4] = 412;  // Reference
  refMotor[9][5] = 606;  // Reference

  refMotor[10][0] = 406;  // Reference
  refMotor[10][1] = 615;  // Reference
  refMotor[10][2] = 406;  // Reference
  refMotor[10][3] = 615;  // Reference
  refMotor[10][4] = 406;  // Reference
  refMotor[10][5] = 615;  // Reference

  refMotor[11][0] = 400;  // Reference
  refMotor[11][1] = 624;  // Reference
  refMotor[11][2] = 400;  // Reference
  refMotor[11][3] = 624;  // Reference
  refMotor[11][4] = 400;  // Reference
  refMotor[11][5] = 624;  // Reference

  refMotor[12][0] = 396;  // Reference
  refMotor[12][1] = 632;  // Reference
  refMotor[12][2] = 396;  // Reference
  refMotor[12][3] = 632;  // Reference
  refMotor[12][4] = 396;  // Reference
  refMotor[12][5] = 632;  // Reference

  refMotor[13][0] = 392;  // Reference
  refMotor[13][1] = 639;  // Reference
  refMotor[13][2] = 392;  // Reference
  refMotor[13][3] = 639;  // Reference
  refMotor[13][4] = 392;  // Reference
  refMotor[13][5] = 639;  // Reference

  refMotor[14][0] = 388;  // Reference
  refMotor[14][1] = 644;  // Reference
  refMotor[14][2] = 388;  // Reference
  refMotor[14][3] = 644;  // Reference
  refMotor[14][4] = 388;  // Reference
  refMotor[14][5] = 644;  // Reference

  refMotor[15][0] = 386;  // Reference
  refMotor[15][1] = 649;  // Reference
  refMotor[15][2] = 386;  // Reference
  refMotor[15][3] = 649;  // Reference
  refMotor[15][4] = 386;  // Reference
  refMotor[15][5] = 649;  // Reference

  refMotor[16][0] = 384;  // Reference
  refMotor[16][1] = 652;  // Reference
  refMotor[16][2] = 384;  // Reference
  refMotor[16][3] = 652;  // Reference
  refMotor[16][4] = 384;  // Reference
  refMotor[16][5] = 652;  // Reference

  refMotor[17][0] = 383;  // Reference
  refMotor[17][1] = 654;  // Reference
  refMotor[17][2] = 383;  // Reference
  refMotor[17][3] = 654;  // Reference
  refMotor[17][4] = 383;  // Reference
  refMotor[17][5] = 654;  // Reference

  refMotor[18][0] = 382;  // Reference
  refMotor[18][1] = 655;  // Reference
  refMotor[18][2] = 382;  // Reference
  refMotor[18][3] = 655;  // Reference
  refMotor[18][4] = 382;  // Reference
  refMotor[18][5] = 655;  // Reference

  refMotor[19][0] = 383;  // Reference
  refMotor[19][1] = 654;  // Reference
  refMotor[19][2] = 383;  // Reference
  refMotor[19][3] = 654;  // Reference
  refMotor[19][4] = 383;  // Reference
  refMotor[19][5] = 654;  // Reference

  refMotor[20][0] = 384;  // Reference
  refMotor[20][1] = 652;  // Reference
  refMotor[20][2] = 384;  // Reference
  refMotor[20][3] = 652;  // Reference
  refMotor[20][4] = 384;  // Reference
  refMotor[20][5] = 652;  // Reference

  refMotor[21][0] = 386;  // Reference
  refMotor[21][1] = 649;  // Reference
  refMotor[21][2] = 386;  // Reference
  refMotor[21][3] = 649;  // Reference
  refMotor[21][4] = 386;  // Reference
  refMotor[21][5] = 649;  // Reference

  refMotor[22][0] = 388;  // Reference
  refMotor[22][1] = 644;  // Reference
  refMotor[22][2] = 388;  // Reference
  refMotor[22][3] = 644;  // Reference
  refMotor[22][4] = 388;  // Reference
  refMotor[22][5] = 644;  // Reference

  refMotor[23][0] = 392;  // Reference
  refMotor[23][1] = 639;  // Reference
  refMotor[23][2] = 392;  // Reference
  refMotor[23][3] = 639;  // Reference
  refMotor[23][4] = 392;  // Reference
  refMotor[23][5] = 639;  // Reference

  refMotor[24][0] = 396;  // Reference
  refMotor[24][1] = 632;  // Reference
  refMotor[24][2] = 396;  // Reference
  refMotor[24][3] = 632;  // Reference
  refMotor[24][4] = 396;  // Reference
  refMotor[24][5] = 632;  // Reference

  refMotor[25][0] = 400;  // Reference
  refMotor[25][1] = 624;  // Reference
  refMotor[25][2] = 400;  // Reference
  refMotor[25][3] = 624;  // Reference
  refMotor[25][4] = 400;  // Reference
  refMotor[25][5] = 624;  // Reference

  refMotor[26][0] = 406;  // Reference
  refMotor[26][1] = 615;  // Reference
  refMotor[26][2] = 406;  // Reference
  refMotor[26][3] = 615;  // Reference
  refMotor[26][4] = 406;  // Reference
  refMotor[26][5] = 615;  // Reference

  refMotor[27][0] = 412;  // Reference
  refMotor[27][1] = 606;  // Reference
  refMotor[27][2] = 412;  // Reference
  refMotor[27][3] = 606;  // Reference
  refMotor[27][4] = 412;  // Reference
  refMotor[27][5] = 606;  // Reference

  refMotor[28][0] = 419;  // Reference
  refMotor[28][1] = 595;  // Reference
  refMotor[28][2] = 419;  // Reference
  refMotor[28][3] = 595;  // Reference
  refMotor[28][4] = 419;  // Reference
  refMotor[28][5] = 595;  // Reference

  refMotor[29][0] = 427;  // Reference
  refMotor[29][1] = 584;  // Reference
  refMotor[29][2] = 427;  // Reference
  refMotor[29][3] = 584;  // Reference
  refMotor[29][4] = 427;  // Reference
  refMotor[29][5] = 584;  // Reference

  refMotor[30][0] = 436;  // Reference
  refMotor[30][1] = 573;  // Reference
  refMotor[30][2] = 436;  // Reference
  refMotor[30][3] = 573;  // Reference
  refMotor[30][4] = 436;  // Reference
  refMotor[30][5] = 573;  // Reference

  refMotor[31][0] = 445;  // Reference
  refMotor[31][1] = 561;  // Reference
  refMotor[31][2] = 445;  // Reference
  refMotor[31][3] = 561;  // Reference
  refMotor[31][4] = 445;  // Reference
  refMotor[31][5] = 561;  // Reference

  refMotor[32][0] = 455;  // Reference
  refMotor[32][1] = 549;  // Reference
  refMotor[32][2] = 455;  // Reference
  refMotor[32][3] = 549;  // Reference
  refMotor[32][4] = 455;  // Reference
  refMotor[32][5] = 549;  // Reference

  refMotor[33][0] = 465;  // Reference
  refMotor[33][1] = 536;  // Reference
  refMotor[33][2] = 465;  // Reference
  refMotor[33][3] = 536;  // Reference
  refMotor[33][4] = 465;  // Reference
  refMotor[33][5] = 536;  // Reference

  refMotor[34][0] = 476;  // Reference
  refMotor[34][1] = 524;  // Reference
  refMotor[34][2] = 476;  // Reference
  refMotor[34][3] = 524;  // Reference
  refMotor[34][4] = 476;  // Reference
  refMotor[34][5] = 524;  // Reference

  refMotor[35][0] = 488;  // Reference
  refMotor[35][1] = 512;  // Reference
  refMotor[35][2] = 488;  // Reference
  refMotor[35][3] = 512;  // Reference
  refMotor[35][4] = 488;  // Reference
  refMotor[35][5] = 512;  // Reference

  refMotor[36][0] = 500;  // Reference
  refMotor[36][1] = 500;  // Reference
  refMotor[36][2] = 500;  // Reference
  refMotor[36][3] = 500;  // Reference
  refMotor[36][4] = 500;  // Reference
  refMotor[36][5] = 500;  // Reference

  //pwm pins
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  pinMode(pwm5, OUTPUT);
  pinMode(pwm6, OUTPUT);

  //other driver pins
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
  //interrupt
  TCCR2A |= 0x00;
  TCCR2B |= 0x00;
  TCCR2A |= _BV(WGM21) | _BV(COM2A0);
  TCCR2B = _BV(CS22) | _BV(CS21) | _BV(CS20);
  TIMSK2 |= _BV(OCIE2A);

  //---***--- Change the speed for each motor to a variable motorSpeed
  
  //timer 0
  TCCR0A = 0x00;
  TCCR0B = 0x00;
  TCCR0A |= (1 << WGM00) | (1 << WGM01);
  TCCR0A |= (1 << COM0B1) | (1 << COM0A1);
  TCCR0B |= (1 << CS01) | (1 << CS00);
  OCR0A = map(0, 0, 100, 0, 255); // Actuator 2
  OCR0B = map(0, 0, 100, 0, 255); // Actuator 1

  //timer 1
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCCR1A |= _BV(WGM10) | _BV(COM1A1) | _BV(COM1B1);
  TCCR1B |= _BV(WGM12) | _BV(CS10) | _BV(CS11);
  OCR1A = map(0, 0, 100, 0, 255); // Actuator 5
  OCR1B = map(0, 0, 100, 0, 255); // Actuator 6

  //timer 5
  TCCR5A = 0x00;
  TCCR5B = 0x00;
  TCCR5A |= _BV(COM5A1) | _BV(COM5B1) | _BV(WGM50);
  TCCR5B |= _BV(WGM52) | _BV(CS50) | _BV(CS51);
  OCR5A = map(0, 0, 100, 0, 255); // Actuator 3
  OCR5B = map(0, 0, 100, 0, 255); // Actuator 4

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);

  
}

void loop() {
}

//internrupt function
ISR(TIMER2_COMPA_vect) {

  sensor[0] = analogRead(A1);
  sensor[1] = analogRead(A2);
  sensor[2] = analogRead(A3);
  sensor[3] = analogRead(A4);
  sensor[4] = analogRead(A5);
  sensor[5] = analogRead(A6);
  
//    Serial.println(counter1);
//    Serial.println(counter2);
   
  for (i=0;i<6;++i){
      error[i]=refMotor[number][i]-sensor[i];
      }
  i = 0;
    
  index_max=0;
  for(i=0;i<6;++i)
    {
        if(abs(error[i])>abs(error[index_max]))
        {
            index_max=i;  
        }
    }
  i=0;
  for (int i=0; i<6; ++i) {
    motorSpeed[i] = abs(error[i] / error[index_max]) * 70;
    if (motorSpeed[i] < 40){
      motorSpeed[i] = 40;
    } else if (motorSpeed[i] > 60) {
      motorSpeed[i] = 60;
    }
  }
  
    Serial.print(sensor[0]);
//    Serial.print("-");
//    Serial.print(motorSpeed[0]);
    Serial.print(",");
    Serial.print(sensor[1]);
//    Serial.print("-");
//    Serial.print(motorSpeed[1]);
    Serial.print(",");
    Serial.print(sensor[2]);
//    Serial.print("-");
//    Serial.print(motorSpeed[2]);
    Serial.print(",");
    Serial.print(sensor[3]);
//    Serial.print("-");
//    Serial.print(motorSpeed[3]);
    Serial.print(",");
    Serial.print(sensor[4]);
//    Serial.print("-");
//    Serial.print(motorSpeed[4]);
    Serial.print(",");
    Serial.println(sensor[5]);
//    Serial.print("-");
//    Serial.print(motorSpeed[5]);
  
  //
  // Motor 1
  if (error[0] > RefTol)
  {
    digitalWrite(ina1, h);
    digitalWrite(inb1, l);
  }
  if (error[0] < -RefTol)
  {
    digitalWrite(ina1, l);
    digitalWrite(inb1, h);
  }
  if (error[0] < RefTol && error[0] > -RefTol)
  {
    digitalWrite(ina1, l);
    digitalWrite(inb1, l);
    check1 = true;
  }
  
  
  // Motor 2
  if (error[1] > RefTol)
  {
    digitalWrite(ina2, h);
    digitalWrite(inb2, l);
  }
  if (error[1] < -RefTol)
  {
    digitalWrite(ina2, l);
    digitalWrite(inb2, h);
  }
  if (error[1] < RefTol && error[1] > -RefTol)
  {
    digitalWrite(ina2, l);
    digitalWrite(inb2, l);
    check2 = true;
  }
  

  
    // Motor 3
    if(error[2]>RefTol)
    {
        digitalWrite(ina3, h);
        digitalWrite(inb3, l);
      }
    if(error[2]<-RefTol)
    {
      digitalWrite(ina3, l);
        digitalWrite(inb3,h);
      }
    if(error[2]<RefTol&&error[2]>-RefTol)
    {
      digitalWrite(ina3, l);
      digitalWrite(inb3,l);
      check3=true;
      }
    
    
    // Motor 4
    if(error[3]>RefTol)
    {
        digitalWrite(ina4, h);
        digitalWrite(inb4, l);
      }
    if(error[3]<-RefTol)
    {
      digitalWrite(ina4, l);
        digitalWrite(inb4,h);
      }
    if(error[3]<RefTol&&error[3]>-RefTol)
    {
      digitalWrite(ina4, l);
      digitalWrite(inb4,l);
      check4=true;
      }
    
    
    // Motor 5
    if(error[4]>RefTol)
    {
        digitalWrite(ina5, h);
        digitalWrite(inb5, l);
      }
    if(error[4]<-RefTol)
    {
      digitalWrite(ina5, l);
        digitalWrite(inb5,h);
      }
    if(error[4]<RefTol&&error[4]>-RefTol)
    {
      digitalWrite(ina5, l);
      digitalWrite(inb5,l);
      check5=true;
      }
      
  // Motor 6
    if(error[5]>RefTol)
    {
        digitalWrite(ina6, h);
        digitalWrite(inb6, l);
      }
    if(error[5]<-RefTol)
    {
      digitalWrite(ina6, l);
        digitalWrite(inb6,h);
      }
    if(error[5]<RefTol&&error[5]>-RefTol)
    {
      digitalWrite(ina6, l);
      digitalWrite(inb6,l);
      check6=true;
      }
    if(j==0)
    {
      OCR0B = map(motorSpeed[0], 0, 100, 0, 255); // Actuator 1
      OCR0A = map(motorSpeed[1], 0, 100, 0, 255); // Actuator 2
      OCR5A = map(motorSpeed[2], 0, 100, 0, 255); // Actuator 3
      OCR5B = map(motorSpeed[3], 0, 100, 0, 255); // Actuator 4
      OCR1B = map(motorSpeed[5], 0, 100, 0, 255); // Actuator 6
      OCR1A = map(motorSpeed[4], 0, 100, 0, 255); // Actuator 5
     j=1;
    }
// This is commented to make the program stop after reaching the reference.
    if(check1==true&&check2==true&&check3==true&&check4==true&&check5==true&&check6==true)
    {
      number++;
       check1=false;
       check2=false;
       check3=false;
       check4=false;
       check5=false;
       check6=false;
  
      }
    if(number==37)
    {
      number=0;
      }
}


void stp()
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
