#include <Servo.h>;
#define boxservo 7
Servo box_servo;
void setup() {
  // put your setup code here, to run once:
  box_servo.attach(boxservo);
  box_servo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i <= 10; i++){
    box_servo.write(i);
    delay(10);
  }
  delay(1000);
  for (int i=10; i >= 0; i--){
    box_servo.write(i);
    delay(10);
  }
  delay(5000);
}
