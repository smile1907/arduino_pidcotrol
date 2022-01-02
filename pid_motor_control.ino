////////////////////////////////
//주행 목표
//정지선에서 멈추기
//장애물에서 멈추기, 치워지면 출발
//라인 따라가기
//////////////////////////////
#include "AllHead.h"

void display_running(void);
bool check_car_floating(void);
double error, errorold;
char str[50];

void setup() //--------------------------------------- /// 정지선, 장애물, 3분발표,2분질문,ppt6장
{
  HWsetup(); //Car initialize//Oled display and Select Joystick
  strcpy(str,"Running"); oled.string(str);
  pid.maxduty = 400;
  pid.Kp = 1;
  pid.Kd = 100;
 // pid.Ki = 50;

    
}



void loop() //--------------------------------------- 
{
    trs.AnalogRead(); //trs.senv[5]
    trs.readAnalogPosition(); //trs.pos  // pid.pid_motor(trs.pos, Ts); //motor speed only Kp control송의호교수님이 주신 코드야 
    pid.p_control(trs.pos);
    motor.duty(pid.Dutyleft, pid.Dutyright);
    
    if(Cm <30) //초음파 센서 
    { 
      motor.duty(0,0);
      delay(500);   
        
      }   
      
    else if(trs.senv[0]+trs.senv[1]+trs.senv[2]+trs.senv[3]+trs.senv[4] > 3200)//결승선
    {motor.duty(0,0); exit(0); }

  
  while(TsFlag == 0) {} //Block on no intr - 5ms 
  TsFlag = 0; 
}


void pid_tuning(void) 
  { oled.pid_tunning(pid.maxduty, pid.Kp, pid.Ki, pid.Kd);
    switch(fjoy.rd()){
      case JU :
      pid.Kp += 1;
      break;
      case JD :
      pid.Kp -= 1;
      break;
      case JR :
      pid.Kp -= 1;
      break;
      case JL :
      pid.Kd -= 1;
      break;
      case JC :
      pid.maxduty += 1;
      break;
    }
    
  }



bool check_car_floating(void)
{
  byte i;

  for (i=0;i<trs.NUM;i++)
  {
    if(trs.senv[i] > 100) return 0;
  }
  return 1;
}
