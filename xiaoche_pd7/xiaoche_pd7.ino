#include<Servo.h>
#include <Wire.h>
#include <JY901.h>
Servo servo_back;
Servo servo_forward;
float kp_back,ki_back,kd_back;
int value_back=86;
int value_forward=35;
float part1=0;
float part2=0;
float err_now=0;//PID
float err_last=0;//PID
float err_sum=0;//PID
float err_last2=0;
float AngleY=0;
float AngleY_last=0;
float GyroY;
float AngleZ=35;
float sign=0;
float unit=13.9;
int flag=1;
int i=0;
void ReadAngle();
void ReadGyro();
void setup() {
  // put your setup code here, to run once:
  servo_back.attach(9);
  servo_forward.attach(10);
  Serial.begin(115200);
  kp_back=4;
  //kd_back=2.35*1.2*0.9;
  kd_back=0.1;
  ki_back=0.35;
}


void loop() {
  // put your main code here, to run repeatedly:
  //滤波

  ReadAngle();
  ReadGyro();



  //Turn
if(flag==1)
    { 
      servo_back.write(100);
      delay(200);
      if(AngleY<-3)
      {flag=0;}
    }
  //Balance
  if((flag==0)&&(AngleY>-4)&&(AngleY<4))
  {
 
     err_now=GyroY;
     err_sum=err_sum+err_now;
     part1=kd_back*(err_now-err_last)+ki_back*AngleY;
     part2=kd_back*(err_now-err_last);
     err_last=err_now;
    /* if(abs(part2)>abs(part1)&&(part1*part2<0))
     {
      value_back=(int)(part1+part2);
      value_back=abs(value_back);
      
     }
     else
     {*/
      value_back=(int)(part1+part2);
       value_back=abs(value_back);
    /* }*/
     if(err_now>=0)
     {sign=-1.1;}
     else
     {sign=0.61;}
    // value_back=(int)((sign*value_back*25/*+sign*abs(AngleY))*5*/+86));//
     value_back=(int)(sign*unit*value_back+86);//
    /* if((value_back<90)&&(value_back>91))
     {*/
        servo_back.write(value_back);
        
    /* }
     
    
// value_back=value_back+(int)((kp_back*(err_now-err_last)+ki_back*err_now+kd_back*(err_now+err_last2-2*err_last)));

 //err_last2=err_last;
     
     //AngleY_last=AngleY;
   //  if((value_back<100)&&(value_back>72))
     /*{*/     
       
     /*}*/
     
   }
  else if(AngleY<=4)
  {
    servo_back.write(95);
  }
  else
  {
    servo_back.write(76);
  }
     value_forward=int(1.5*(33-(36.7+AngleZ)));
      servo_forward.write(value_forward);

 // ReadGyro();
  //AngleX=weight*(AngleX_Last+GyroX*dt)+(1-weight)*AngleX;
 // AngleY=weight*(AngleY_Last+GyroY*dt)+(1-weight)*AngleY; 
 

}



void ReadAngle()
{
  AngleZ = (float)JY901.stcAngle.Angle[2]/32768*180;
  AngleY = (float)JY901.stcAngle.Angle[1]/32768*180;
  }
void ReadGyro()
{
  GyroY=(float)JY901.stcGyro.w[1]/32768*2000;
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
