#include <Servo.h>
// Define motor pins
const int motor1_ENA = 11;  // Motor 1 enable pin
const int motor1_IN1 = 30;  // Motor 1 input pin 1
const int motor1_IN2 = 32;  // Motor 1 input pin 2
const int motor1_IN3 = 34;
const int motor1_IN4 = 36;

const int motor2_ENB = 4;// Motor 2 enable pin
const int motor2_IN1 = 22;
const int motor2_IN2 = 24;
const int motor2_IN3 = 26;  // Motor 2 input pin 3
const int motor2_IN4 = 28;  // Motor 2 input pin 4

// Define IR sensor pins
const int IR1 = A0;  // Sensor 1 analog pin
const int IR2 = A1;  // Sensor 2 analog pin
const int IR3 = A2;  // Sensor 3 analog pin
const int IR4 = A3;  // Sensor 4 analog pin
const int IR5 = A4;  // Sensor 5 analog pin
const int IR6 = A5;
#define light 40// Sensor 6 analog pin
#define buzzer 38
#define TURN_DELAY 1000
#define RADAR_ANGLE 90
#define IR_MAIN  A7
#define IR_MAIN_THRESHOLD 1
#define SERVO_PIN 42
Servo servo_radar;
void buzzon();
void buzzoff();
void setup() {
  // Set pin modes for motor control pins
  pinMode(motor1_ENA, OUTPUT);
  pinMode(motor1_IN1, OUTPUT);
  pinMode(motor1_IN2, OUTPUT);
  pinMode(motor1_IN3, OUTPUT);
  pinMode(motor1_IN4, OUTPUT);
  pinMode(motor2_ENB, OUTPUT);
  pinMode(motor2_IN1, OUTPUT);
  pinMode(motor2_IN2, OUTPUT);
  pinMode(motor2_IN3, OUTPUT);
  pinMode(motor2_IN4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(light , OUTPUT);
  // Set pin modes for IR sensor pins
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR6, INPUT);
  pinMode(IR_MAIN, INPUT);
  Serial.begin(9600);
  buzzon();
  lighton();
  moveForward();
  delay(300);
  backward();
  delay(500);
  turnLeft();
  turnRight();

  lightoff();
  buzzoff();
  servo_radar.attach(SERVO_PIN);
  servo_radar.write(0);
  //irrecv.enableIRIn();  // Start the receiver
}

float radar_val = 0;
int angle = 0;
bool radar_turning_right = false;
void loop() {
  int sensor1 = digitalRead(IR1);  //frontleft
  int sensor2 = digitalRead(IR2);  //frontright
  int sensor3 = digitalRead(IR3);  //downleft
  int sensor4 = digitalRead(IR4);  //downright


  int sensor5 = digitalRead(IR5);  //right
  int sensor6 = digitalRead(IR6);  //left
  int sensorMain = digitalRead(IR_MAIN);
  //  Serial.print("front-left: ");
  //  Serial.print(sensor1);
  //  Serial.print(" front-right: ");
  //  Serial.print(sensor2);
  //  Serial.print(" down-left: ");
  //  Serial.print(sensor3);
  //  Serial.print(" down-right: ");
  //  Serial.print(sensor4);
  //  Serial.println(" left: ");
  //  Serial.println(sensor5);
  //  Serial.println(" right: ");
  //  Serial.println(sensor6);
  //  Serial.print(" main: ");
  //  Serial.println(sensorMain);


  //   if (radar_turning_right)
  //     for (angle = 0; angle < RADAR_ANGLE; angle++) {
  //       servo_radar.write(angle);
  //       radar_val = digitalRead(IR_MAIN);
  //       if (radar_val ==HIGH) {
  //         break;
  //       }
  //       delay(2);
  //     }
  //   else
  //     for (angle = RADAR_ANGLE; angle > 0; angle--) {
  //       servo_radar.write(angle);
  //       radar_val = digitalRead(IR_MAIN);
  //       if (radar_val ==HIGH) {
  //         break;
  //       }
  //       delay(2);
  //     }
  //   radar_turning_right = !radar_turning_right;
  //
  //  // Check if any sensor detects an obstacle
  if (sensor1 == LOW || sensor2 == LOW
      //    || radar_val ==HIGH
     ) {
    //    // Obstacle detected, stop and turn
    Serial.print("obstacle:");
    Serial.println(sensor1);
    Serial.println(sensor2);
    stopMotors();
    stopClean();
    buzzon();
    lighton();
    delay(100);
    lightoff();
    buzzoff();
    delay(200);


    lighton();
    makeATurn(sensor5, sensor6, sensor1, sensor2);
    lightoff();

  } else {
    // No obstacle, move forward
    if (sensor3 == LOW && sensor4 == LOW ) {
      //  Serial.println("forward");
      moveForward();
      startClean();

    } else {
      stopClean();

      backward();
      makeATurn(sensor5, sensor6, sensor1, sensor2);
    }
  }
  delay(50);
}
void makeATurn(int sensor5, int sensor6, int sensor1, int sensor2) {

  if (sensor5 == LOW && sensor6 == LOW)
    rotate180();
  else if (sensor5 == LOW)
    turnLeft();
  else if (sensor6 == LOW)
    turnRight();
  else if(sensor6==LOW&&sensor1==LOW)
    turnRight();
  else if(sensor5==LOW&&sensor2==LOW)
      turnLeft();
  else {
    if (sensor1 == LOW)
      turnRight(); 
    else if (sensor2 == LOW)
      turnLeft();
    else
      turnLeft();
  }
}
void backward() {

  digitalWrite(motor1_IN1, LOW);
  digitalWrite(motor1_IN2, HIGH);
  digitalWrite(motor1_IN3, LOW);
  digitalWrite(motor1_IN4, HIGH);
  digitalWrite(motor1_ENA, HIGH);
  digitalWrite(motor2_ENB, HIGH);
  buzzon();
  for (int j = 0; j < 500 / 25; j++) {
    lighton();

    delay(25);
    lightoff();
  }

  buzzoff();
  stopMotors();
}
void moveForward() {
  digitalWrite(motor1_IN1, HIGH);
  digitalWrite(motor1_IN2, LOW);
  digitalWrite(motor1_IN3, HIGH);
  digitalWrite(motor1_IN4, LOW);
  digitalWrite(motor1_ENA, HIGH);
  digitalWrite(motor2_ENB, HIGH);
}
void stopClean() {

  digitalWrite(motor2_IN1, LOW);
  digitalWrite(motor2_IN2, LOW);
  digitalWrite(motor2_IN3, LOW);
  digitalWrite(motor2_IN4, LOW);
}
void startClean() {

  digitalWrite(motor2_IN1, HIGH);
  digitalWrite(motor2_IN2, LOW);
  digitalWrite(motor2_IN3, HIGH);
  digitalWrite(motor2_IN4, LOW);
}
void stopMotors() {

  digitalWrite(motor1_IN1, LOW);
  digitalWrite(motor1_IN2, LOW);
  digitalWrite(motor1_IN3, LOW);
  digitalWrite(motor1_IN4, LOW);
  stopClean();
  digitalWrite(motor1_ENA, LOW);
  digitalWrite(motor2_ENB, LOW);
  delay(50);
}

void turnLeft() {
  digitalWrite(motor1_IN1, HIGH);
  digitalWrite(motor1_IN2, LOW);
  digitalWrite(motor1_IN3, LOW);
  digitalWrite(motor1_IN4, HIGH);
  stopClean();
  digitalWrite(motor1_ENA, HIGH);
  digitalWrite(motor2_ENB, HIGH);
  delay(TURN_DELAY);
  stopMotors();
}
void turnRight() {
  digitalWrite(motor1_IN1, LOW);
  digitalWrite(motor1_IN2, HIGH);
  digitalWrite(motor1_IN3, HIGH);
  digitalWrite(motor1_IN4, LOW);
  stopClean();
  digitalWrite(motor1_ENA, HIGH);
  digitalWrite(motor2_ENB, HIGH);
  delay(TURN_DELAY);
  stopMotors();
}
void rotate180() {
  turnRight();
  turnRight();
}
void buzzon()
{
  digitalWrite(buzzer, LOW);
}
void buzzoff()
{
  digitalWrite(buzzer, HIGH);
}
void lighton()
{
  digitalWrite(light, LOW);
}
void lightoff() {
  digitalWrite(light, HIGH);
}
