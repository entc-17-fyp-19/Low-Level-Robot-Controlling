#include <Servo.h>;
#define baseservoL 6
#define armservoL 7
#define baseservoR 8
#define armservoR 9
Servo baseL_servo;
Servo armL_servo;
Servo baseR_servo;
Servo armR_servo;

int armL_pos_1 = 0;
int armL_pos_2 = 0;
int armR_pos_1 = 0;
int armR_pos_2 = 0;

void setup() {
  // put your setup code here, to run once:
  baseL_servo.attach(baseservoL);
  armL_servo.attach(armservoL);
  baseR_servo.attach(baseservoR);
  armR_servo.attach(armservoR);
  baseL_servo.write(0);
  armL_servo.write(0);
  baseR_servo.write(0);
  armR_servo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  Arm_L_pos(0, 0);
  delay(2000);
  Arm_L_pos(30, 0);
  delay(2000);
  Arm_L_pos(30, 30);
  delay(2000);
  Arm_L_pos(0, 30);
  delay(2000);
}

//void Arm_L_pos(int theta_1, int theta_2, float max_speed){
//for (int i = armL_pos_1; i<= theta_1; i++){
//    baseL_servo.write(i);
//    delay(5);
//  }
//  armL_pos_1 = theta_1;
//  
//  for (int i = armL_pos_2; i<= theta_2; i++){
//    armL_servo.write(i);
//    delay(5);
//  }
//  armL_pos_2 = theta_2;
//}

//void Arm_R_pos(int theta_1, int theta_2, float max_speed){
//for (int i = armR_pos_1; i<= theta_1; i++){
//    baseR_servo.write(i);
//    delay(5);
//  }
//  armR_pos_1 = theta_1;
//  
//  for (int i = armL_pos_2; i<= theta_2; i++){
//    armR_servo.write(i);
//    delay(5);
//  }
//  armR_pos_2 = theta_2;
//}

void Arm_L_pos(int theta_1, int theta_2){
  baseL_servo.write(theta_1);
  delay(10);
  armL_servo.write(theta_2);
  delay(10);
}

void Arm_R_pos(int theta_1, int theta_2){
  baseR_servo.write(theta_1);
  delay(10);
  armR_servo.write(theta_2);
  delay(10);
}
