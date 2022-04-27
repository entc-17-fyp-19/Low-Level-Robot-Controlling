#define TRIG_F A6
#define ECHO_F A7
#define TRIG_L A8
#define ECHO_L A9
#define TRIG_R A10
#define ECHO_R A11

void setup() {
pinMode(ECHO_F, INPUT);
pinMode(TRIG_F, OUTPUT);
pinMode(ECHO_L, INPUT);
pinMode(TRIG_L, OUTPUT);
pinMode(ECHO_R, INPUT);
pinMode(TRIG_R, OUTPUT);

digitalWrite(ECHO_F, HIGH);
digitalWrite(ECHO_L, HIGH);
digitalWrite(ECHO_R, HIGH);
}

void loop() {
Obstacle_detect();
delay(1000);
}

int Obstacle_detect(){
  digitalWrite(TRIG_F, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_F, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_F, LOW);

  digitalWrite(TRIG_L, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_L, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_L, LOW);

  digitalWrite(TRIG_R, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_R, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_R, LOW);

  float dis_F = pulseIn(ECHO_F,HIGH, 200000);
  dis_F = (dis_F/2)*0.0343;

  float dis_L = pulseIn(ECHO_L,HIGH, 200000);
  dis_L = (dis_L/2)*0.0343;

  float dis_R = pulseIn(ECHO_R,HIGH, 200000);
  dis_R = (dis_R/2)*0.0343;

  if (dis_R < 200 || dis_F < 200 || dis_L < 200){
    return (1);
  }
  else{
    return (0);
  }
}
