#define PWM 10
#define in1 4
#define in2 5
#define en 3

void setup() {
  // put your setup code here, to run once:
  pinMode(PWM, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en, OUTPUT);
}

void loop() {  
   digitalWrite(en, HIGH);
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   for (int i = 0;i<6;i++){
      analogWrite(PWM, 250);
      delay(1000);
      analogWrite(PWM, 0);
      delay(5000);
   }

  while(1){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(PWM, 0);
  }
}
