float PWM_ex = 0;
float Omega_ex = 0;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  PWM_ex = PWM(2.0,"L");
  Omega_ex = Omega(100,"L");
}
float PWM(float w,char motor){
  float pwm;
  if (w <= 0.1){
    pwm = 0; 
    if (motor == "L"){
      pwm = -1.9765702*pow(w,2) + 34.70570173*w + 24.1273073;
    }
    else{
      pwm = -5.55509933*pow(w,2) + 43.87695327*w + 22.18873416;
    }
  }
  return pwm;
}

float Omega(int pwm,char motor){
  float omega;
  if (motor == "L"){
    if (pwm <= 18){
      omega = 0;
    }
    else{
      omega = -0.0000764041454*pow(pwm,2) + 0.0236812568*pwm - 0.596754982;
    }
  }
  if (motor == "R"){
    if (pwm <= 17){
      omega = 0;
    }
    else{
      omega = -0.000192967539*pow(pwm,2) + 0.00873435835*pwm - 0.246137506;
    }
  } 
}
