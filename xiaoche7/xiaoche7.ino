#include<Servo.h>
#include <Wire.h>
#include <JY901.h>
Servo servo_forward;
Servo servo_back;
float AngleY;
float AngleZ;
int value_forward;
void ReadAngle();
void setup() {
  // put your setup code here, to run once:
  servo_back.attach(9);
  servo_back.attach(10);
  Serial.begin(115200);
  value_forward=35;
}


void loop() {
  // put your main code here, to run repeatedly:
  //滤波

  ReadAngle();
  value_forward=35-AngleZ;
  servo_back.write(value_forward);
  
  

}


void ReadAngle()
{
  //AngleX = (float)JY901.stcAngle.Angle[0]/32768*180;
  AngleZ = (float)JY901.stcAngle.Angle[2]/32768*180;
  }

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
 
void serialEvent() 
{
  while (Serial.available()) 
  {
    JY901.CopeSerialData(Serial.read()); //Call JY901 data cope function
  }
}
