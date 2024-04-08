#include <Servo.h>
Servo servo;
const int l1= 30;  // Motor 1 enable pin
const int l2= 32;  // Motor 1 input pin 1
const int r1= 34;  // Motor 1 input pin 2
const int r2= 36;
const int brush1= 32;
const int brush2= 34;
const int mob1= 36;  // Motor 2 input pin 3
const int mob2= 38;
const int irfl= A0;  // Sensor 1 analog pin
const int irfr= A1;  // Sensor 2 analog pin
const int irdl= A2;  // Sensor 3 analog pin
const int irdr= A3;  // Sensor 4 analog pin
const int irl= A4;  // Sensor 5 analog pin
const int irr=A5;
int count=0;
const int buzzer=38;
const int light=40;
#define ir 8
void buzzon();
void buzzoff();
void lighton();
void front();
void back();
void left();
void right();
void Stop();
void Start();
void turn();
void setup()
{
  servo.attach(9);
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);
  pinMode(mob1,OUTPUT);
  pinMode(mob2,OUTPUT);
  pinMode(brush1,OUTPUT);
  pinMode(brush2,OUTPUT);
  pinMode(irfl,INPUT); 
  pinMode(irfr,INPUT);
  pinMode(irdl,INPUT);
  pinMode(irdr,INPUT);
  pinMode(irl,INPUT);
  pinMode(irr,INPUT);
  pinMode(ir,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(light,OUTPUT);
  delay(1000);
  Start();
  // put your setup code here, to run once:
}

void loop() 
{
 int i,ir1,ir2,ir3,ir4,ir5,ir6,Ir;
  ir1=digitalRead(irfl);
  ir2=digitalRead(irfr);
  ir3=digitalRead(irdl);
  ir4=digitalRead(irdr);
  ir5=digitalRead(irl);
  ir6=digitalRead(irr);

  
  front();  
 
}
void Stop()
{  
   buzzon();
   digitalWrite(l1,LOW);
   digitalWrite(l2,LOW);
   digitalWrite(r1,LOW);
   digitalWrite(r2,LOW);
   digitalWrite(brush1,LOW);
   digitalWrite(brush2,LOW);
   digitalWrite(mob1,LOW);
   digitalWrite(mob2,LOW);
   delay(50);
   buzzoff();
   lighton();
}
void buzzon()
{
   digitalWrite(buzzer,LOW);

}
void buzzoff()
{
   digitalWrite(buzzer,HIGH);
}
void front()
{  
   digitalWrite(l1,HIGH);
   digitalWrite(l2,LOW);
   digitalWrite(r1,HIGH);
   digitalWrite(r2,LOW);
}
void left()
{
   digitalWrite(l1,LOW);
   digitalWrite(l2,HIGH);
   digitalWrite(r1,HIGH);
   digitalWrite(r2,LOW);
}
void right()
{
   digitalWrite(l1,HIGH);
   digitalWrite(l2,LOW);
   digitalWrite(r1,LOW);
   digitalWrite(r2,HIGH);
}
void back()
{
   digitalWrite(l1,LOW);
   digitalWrite(l2,HIGH);
   digitalWrite(r1,LOW);
   digitalWrite(r2,HIGH);
}
void lighton()
{
  digitalWrite(light,LOW);
  delay(500);
  digitalWrite(light,HIGH);
} 
void Start()
{
  lighton();
  delay(50);
  lighton();
  front();
  delay(500);
  Stop();
  delay(500);
  back();
  delay(500);
  Stop();
  servo.write(90);
  delay(500);
  servo.write(0);
  delay(500);
  servo.write(180);
  delay(500);
  servo.write(0);
}
void turn(){
  if(count==0)
  {
    right();
    count++;
  }
  else
  {
    left();
    count--;
  }
}
