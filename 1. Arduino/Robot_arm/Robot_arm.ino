#include <Servo.h>;
#define boxservo 6
Servo box_servo;
void setup() {
  // put your setup code here, to run once:
  box_servo.attach(boxservo);
  box_servo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i <= 100; i++){
    box_servo.write(i);
    delay(10);
  }
  for (int i=100; i >= 0; i--){
    box_servo.write(i);
    delay(10);
  }
}
