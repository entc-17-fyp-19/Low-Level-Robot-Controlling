#define ECHO 8
#define TRIG 9

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

  float dis = pulseIn(ECHO,HIGH, 200000);
  dis = (dis/2)*0.0343;

  Serial.print(dis);
  Serial.println("    cm");
  delay(50);
}
