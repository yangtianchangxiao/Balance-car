#include<Servo.h>
#include <Wire.h>
#include <JY901.h>
Servo servo_forward;
Servo servo_back;
bool flag=true;
float AngleY;
float AngleZ;
int value_forward;
void ReadAngle();
void setup() {
  // put your setup code here, to run once:
  servo_forward.attach(10);
  servo_back.attach(9);
  Serial.begin(115200);
  value_forward=35;
}
  

void loop() {
  // put your main code here, to run repeatedly:
  //滤波

  ReadAngle();
  if(flag)
  {
     if(AngleY<-2.5)
    {
      value_forward=2*(35-(45.5+AngleZ));
      servo_forward.write(value_forward);
      servo_back.write(100);
    }
     else
    {
      servo_back.write(100);
      servo_forward.write(35);
    }
    /*if(-0.5<AngleZ<0.5)
    {
      servo_forward.write(35);
      flag=false;  
    }*/
  }
  else
  {
    servo_back.write(70);
  }
  
 
}


void ReadAngle()
{
  AngleY = (float)JY901.stcAngle.Angle[1]/32768*180;
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
