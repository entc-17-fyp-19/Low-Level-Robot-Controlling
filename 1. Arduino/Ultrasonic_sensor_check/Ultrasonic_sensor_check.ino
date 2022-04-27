#define ECHO 9
#define TRIG 8

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(ECHO, INPUT);
pinMode(TRIG, OUTPUT);

digitalWrite(ECHO, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG, LOW);

  float dis = pulseIn(ECHO,HIGH, 30000);
  dis = (dis/2)*0.0343;

  if (dis != 0){
//    Serial.print(dis);
//    Serial.println("    cm");
    Serial.println("1");
  }
  else{
    Serial.println("0");
  }
  
}
