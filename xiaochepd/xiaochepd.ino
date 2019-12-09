#include<Servo.h>
#include <Wire.h>
#include <JY901.h>
Servo servo_back;
float kp_back,ki_back,kd_back;
int value_back=86;
float err_now=0;//PID
float err_last=0;//PID
float err_sum=0;//PID
float err_last2=0;
float AngleY;
float AngleY_last=0;
void ReadAngle();
void setup() {
  // put your setup code here, to run once:
  servo_back.attach(9);
  Serial.begin(115200);
  kp_back=80;
  ki_back=4;
  kd_back=80;
}


void loop() {
  // put your main code here, to run repeatedly:
  //滤波

  ReadAngle();
  if(AngleY>4)
  {
    servo_back.write(72);
    }
    else if(AngleY<-4)
    {
      servo_back.write(100);
      }
 // ReadGyro();
  //AngleX=weight*(AngleX_Last+GyroX*dt)+(1-weight)*AngleX;
 // AngleY=weight*(AngleY_Last+GyroY*dt)+(1-weight)*AngleY;

else{ err_now=AngleY-AngleY_last;
 err_sum=err_sum+err_now;
 value_back=(int)(-(kp_back*err_now+kd_back*(err_now-err_last))/*/kp_back/35*15*/+86);//
// value_back=value_back+(int)((kp_back*(err_now-err_last)+ki_back*err_now+kd_back*(err_now+err_last2-2*err_last)));

 //err_last2=err_last;
 err_last=err_now;
 AngleY_last=AngleY;
 
 if(value_back>100)
 {
  servo_back.write(100);
  }
 else if(value_back<72)
 {
  
 servo_back.write(72);
 }
 else
 {
  servo_back.write(value_back);
  }
}
}


void ReadAngle()
{
  //AngleX = (float)JY901.stcAngle.Angle[0]/32768*180;
  AngleY = (float)JY901.stcAngle.Angle[1]/32768*180;
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
