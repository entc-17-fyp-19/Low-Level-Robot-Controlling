#define PWM 5
#define in1 23
#define in2 25

void setup() {
  // put your setup code here, to run once:
  pinMode(PWM, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {  
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   analogWrite(PWM, 50);
   delay(2000);

  while(1){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(PWM, 0);
  }
}
