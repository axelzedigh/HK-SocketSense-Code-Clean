/*

*/
#include "HX711.h"
#include "Force.h"

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

#define DOUT1 23
#define DOUT2 24
#define DOUT3 25
#define DOUT4 26
#define DOUT5 27
#define DOUT6 22
#define CLK 31

//actuator 1 param
HX711 scale1;
const int inb1 = 5;
const int ina1 = 6;
const int pwm1 = 4;
const int ena1 = 3;
const int enb1 = 2;
float calibration_factor1 = -14690;

//actuator 2 param
HX711 scale2;
const int inb2 = 9;
const int ina2 = 10;
const int pwm2 = 13;
const int ena2 = 8;
const int enb2 = 7;
float calibration_factor2 = -14780;

//actuator 3 param
HX711 scale3;
const int inb3 = 51;
const int ina3 = 50;
const int pwm3 = 46;
const int ena3 = 52;
const int enb3 = 53;
float calibration_factor3 = -14630;

//actuator 4 param
HX711 scale4;
const int inb4 = 47;
const int ina4 = 44;
const int pwm4 = 45;
const int ena4 = 48;
const int enb4 = 49;
float calibration_factor4 = -14690;

//actuator 5 param
HX711 scale5;
const int inb5 = 41;
const int ina5 = 40;
const int pwm5 = 11;
const int ena5 = 42;
const int enb5 = 43;
float calibration_factor5 = -14550;

//actuator 6 param
HX711 scale6;
const int inb6 = 15;
const int ina6 = 14;
const int pwm6 = 12;
const int ena6 = 16;
const int enb6 = 17;
float calibration_factor6 = -14700;

double error[6];
double sense[6];
int RefTol = 0.5;  /// Reference tolerance

void setup() {
  Serial.begin(115200);

  //pwm pins
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(pwm3,OUTPUT);
  pinMode(pwm4,OUTPUT);
  pinMode(pwm5,OUTPUT);
  pinMode(pwm6,OUTPUT);

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
  TCCR2A |=0x00;                   
  TCCR2B |=0x00;  
  TCCR2A |=_BV(WGM21)|_BV(COM2A0);
  TCCR2B=_BV(CS22)|_BV(CS21)|_BV(CS20);     
  TIMSK2 |=_BV(OCIE2A); 

  
  //timer 0
  TCCR0A = 0x00;
  TCCR0B = 0x00;
  TCCR0A |= (1 << WGM00) | (1 << WGM01); 
  TCCR0A |= (1 << COM0B1) | (1<<COM0A1);
  TCCR0B |= (1 << CS01) | (1 << CS00); 
  OCR0A = map(50,0,100,0,255);
  OCR0B = map(50,0,100,0,255);
  
  //timer 1
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCCR1A |=_BV(WGM10)|_BV(COM1A1)|_BV(COM1B1);
  TCCR1B |=_BV(WGM12)|_BV(CS10)|_BV(CS11);
  OCR1A=map(50,0,100,0,255);
  OCR1B=map(50,0,100,0,255);
  
  //timer 5
  TCCR5A = 0x00;
  TCCR5B = 0x00;
  TCCR5A |=_BV(COM5A1)|_BV(COM5B1)|_BV(WGM50);
  TCCR5B |=_BV(WGM52)|_BV(CS50)|_BV(CS51);
  OCR5A =map(50,0,100,0,255);
  OCR5B = map(50,0,100,0,255);
  
  //load cell amplifier
  scale1.begin(DOUT1, CLK);
  scale1.set_scale(calibration_factor1);

  scale2.begin(DOUT2, CLK);
  scale2.set_scale(calibration_factor2);

  scale3.begin(DOUT3, CLK);
  scale3.set_scale(calibration_factor3);

  scale4.begin(DOUT4, CLK);
  scale4.set_scale(calibration_factor4);

  scale5.begin(DOUT5, CLK);
  scale5.set_scale(calibration_factor5);

  scale6.begin(DOUT6, CLK);
  scale6.set_scale(calibration_factor6);

}

void loop() {
  
}

//internrupt function
ISR(TIMER2_COMPA_vect){

  sense[0]=scale1.get_units();
  sense[1]=scale2.get_units();
  sense[2]=scale3.get_units();
  sense[3]=scale4.get_units();
  sense[4]=scale5.get_units();
  sense[5]=scale6.get_units();
  
  for (i=0;i<6;++i){
      error[i]=ForceMat[number][i]-sense[i];
      }

  if(error[0] > -RefTol && error[0] < RefTol )
    {
    digitalWrite(ina1, HIGH);
    digitalWrite(inb1, HIGH);
    //Serial.println("stop1");
    check1 = true;
    }

    if(error[0] > RefTol)
    {
     digitalWrite(ina1, HIGH);
     digitalWrite(inb1, LOW);
     //Serial.println("forward1");
      }

    if(error[0] < -RefTol)
    {
     digitalWrite(ina1, LOW);
     digitalWrite(inb1, HIGH);
     //Serial.println("backward1");
      }

      if(error[1] > -RefTol && error[1] <RefTol )
    {
    digitalWrite(ina2, HIGH);
    digitalWrite(inb2, HIGH);
    //Serial.println("stop2");
    check2 = true;
    }

    if(error[1] > RefTol)
    {
     digitalWrite(ina2, HIGH);
     digitalWrite(inb2, LOW);
     //Serial.println("forward2");
      }

    if(error[1] < -RefTol)
    {
     digitalWrite(ina2, LOW);
     digitalWrite(inb2, HIGH);
     //Serial.println("backward2");
      }

    if(error[2] > -RefTol && error[2] < RefTol )
    {
    digitalWrite(ina3, HIGH);
    digitalWrite(inb3, HIGH);
    //Serial.println("stop3");
    check3=true;
    }

    if(error[2] > RefTol)
    {
     digitalWrite(ina3, HIGH);
     digitalWrite(inb3, LOW);
     //Serial.println("forward3");
      }

    if(error[2] < -RefTol)
    {
     digitalWrite(ina3, LOW);
     digitalWrite(inb3, HIGH);
     //Serial.println("backward3");
      }
    if(error[3] > -RefTol && error[3] < RefTol )
    {
    digitalWrite(ina4, HIGH);
    digitalWrite(inb4, HIGH);
    //Serial.println("stop4");
    check4=true;
    }

    if(error[3] > RefTol)
    {
     digitalWrite(ina4, HIGH);
     digitalWrite(inb4, LOW);
    // Serial.println("forward4");
      }

    if(error[3] < -RefTol)
    {
     digitalWrite(ina4, LOW);
     digitalWrite(inb4, HIGH);
     //Serial.println("backward4");
      }

   if(error[4] > -RefTol && error[4] < RefTol )
    {
    digitalWrite(ina5, HIGH);
    digitalWrite(inb5, HIGH);
    //Serial.println("stop5");
    check5=true;
    }

    if(error[4] > RefTol)
    {
     digitalWrite(ina5, HIGH);
     digitalWrite(inb5, LOW);
     //Serial.println("forward5");
      }

    if(error[4] < -RefTol)
    {
     digitalWrite(ina5, LOW);
     digitalWrite(inb5, HIGH);
     //Serial.println("backward3");
      }

    if(error[5] > -RefTol&& error[5] < RefTol)
    {
    digitalWrite(ina6, HIGH);
    digitalWrite(inb6, HIGH);
    //Serial.println("stop6");
    check6=true;
    }

    if(error[5] > RefTol)
    {
     digitalWrite(ina6, HIGH);
     digitalWrite(inb6, LOW);
     //Serial.println("forward6");
      }

    if(error[5] < -RefTol)
    {
     digitalWrite(ina6, LOW);
     digitalWrite(inb6, HIGH);
     //Serial.println("backward6");
      }

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

     if(number==line)
    {
      number=0;
      }
  
}
