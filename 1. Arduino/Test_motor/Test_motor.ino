#define PWM_1 5
#define in1_1 23
#define in2_1 25
#define PWM_2 4
#define in1_2 27
#define in2_2 29

void setup() {
  // put your setup code here, to run once:
  pinMode(PWM_1, OUTPUT);
  pinMode(in1_1, OUTPUT);
  pinMode(in2_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(in1_2, OUTPUT);
  pinMode(in2_2, OUTPUT);
}

void loop() {  
  for (int i= 0; i<=255; i++){
    digitalWrite(in1_1, LOW);
    digitalWrite(in2_1, HIGH);
    analogWrite(PWM_1, i);
    digitalWrite(in1_2, LOW);
    digitalWrite(in2_2, HIGH);
    analogWrite(PWM_2, i);
    delay(200);
  }

  for (int i= 255; i>=0; i--){
    digitalWrite(in1_1, LOW);
    digitalWrite(in2_1, HIGH);
    analogWrite(PWM_1, i);
    digitalWrite(in1_2, LOW);
    digitalWrite(in2_2, HIGH);
    analogWrite(PWM_2, i);
    delay(200);
  }

  while(1){
    digitalWrite(in1_1, LOW);
    digitalWrite(in2_1, LOW);
    analogWrite(PWM_1, 0);
    digitalWrite(in1_2, LOW);
    digitalWrite(in2_2, LOW);
    analogWrite(PWM_2, 0);
  }
}
