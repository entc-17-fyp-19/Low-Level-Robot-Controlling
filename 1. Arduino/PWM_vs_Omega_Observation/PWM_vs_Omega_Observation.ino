#define PWM_1 5
#define in1_1 23
#define in2_1 25
#define PWM_2 4
#define in1_2 27
#define in2_2 29

#define LM_INT1 20
#define RM_INT1 19
#define LM_INT2 14
#define RM_INT2 15

#define cpr 19200 // count per round

volatile long counter_L = 0;
volatile long counter_R = 0;
volatile float Omega_L = 0;
volatile float Omega_R = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(PWM_1, OUTPUT);
  pinMode(in1_1, OUTPUT);
  pinMode(in2_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(in1_2, OUTPUT);
  pinMode(in2_2, OUTPUT);

  pinMode(RM_INT2, INPUT);
  pinMode(LM_INT2, INPUT);
  
  pinMode(LM_INT1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LM_INT1), counterL, RISING);

  pinMode(RM_INT1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RM_INT1), counterR, RISING);
}

void loop() {  
  Serial.println("Forward Direction");
  
  for (int i= 0; i<=200; i++){
    digitalWrite(in1_1, LOW);
    digitalWrite(in2_1, HIGH);
    analogWrite(PWM_1, i);
    digitalWrite(in1_2, LOW);
    digitalWrite(in2_2, HIGH);
    analogWrite(PWM_2, i);
    Serial.print(i);
    Serial.print(" ");
    velocity();
    delay(200);
  }

  for (int i= 200; i>=0; i--){
    digitalWrite(in1_1, LOW);
    digitalWrite(in2_1, HIGH);
    analogWrite(PWM_1, i);
    digitalWrite(in1_2, LOW);
    digitalWrite(in2_2, HIGH);
    analogWrite(PWM_2, i);
    Serial.print(i);
    Serial.print(" ");
    velocity();
    delay(200);
  }

  Serial.println("Reverse Direction");
  
  for (int i= 0; i<=200; i++){
    digitalWrite(in1_1, HIGH);
    digitalWrite(in2_1, LOW);
    analogWrite(PWM_1, i);
    digitalWrite(in1_2, HIGH);
    digitalWrite(in2_2, LOW);
    analogWrite(PWM_2, i);
    Serial.print(i);
    Serial.print(" ");
    velocity();
    delay(200);
  }

  for (int i= 200; i>=0; i--){
    digitalWrite(in1_1, HIGH);
    digitalWrite(in2_1, LOW);
    analogWrite(PWM_1, i);
    digitalWrite(in1_2, HIGH);
    digitalWrite(in2_2, LOW);
    analogWrite(PWM_2, i);
    Serial.print(i);
    Serial.print(" ");
    velocity();
    delay(200);
  }
}

void counterL() {
  int int2 = digitalRead(LM_INT2);

  if(int2 < 0){
    counter_L++;
  }else{
    counter_L--;
  }
}

void counterR() {
  int int2 = digitalRead(RM_INT2);

  if(int2 < 0){
    counter_R++;
  }else{
    counter_R--;
  }
}

void velocity(){
  counter_L = 0;
  counter_R = 0;
  delay(1000);
  Omega_L = (2*PI*counter_L)/cpr;
  Omega_R = (2*PI*counter_R)/cpr;
  Serial.print(Omega_L);
  Serial.print(" ");
  Serial.print(counter_L);
  Serial.print(" ");
  Serial.println(Omega_R);
  Serial.print(" ");
  Serial.println(counter_R);
}
