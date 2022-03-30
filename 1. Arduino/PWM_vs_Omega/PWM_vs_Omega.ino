void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
float PWM(w,motor){
  float pwm;
  if (w == 0){
    pwm = 0; 
  }
  if (motor == "L"){
    pwm = 2.54647926*pow(w,2) + 23.38200899*w + 26.15273771;
  }
  else{
    pwm = 3.92203389*pow(w,2) + 12.97286726*w + 26.98219747;
  }
  return pwm;
}

float Omega(pwm,motor){
  float omega;
  if (motor == "L"){
    if (pwm <= 22){
      omega = 0;
    }
    else{
      omega = -0.0000692232693*pow(pwm) + 0.0420306750*pwm + -1.01616927;
    }
  }
  if (motor == "R"){
    if (pwm <= 23){
      omega = 0;
    }
    else{
      omega = -0.000141526413*pow(pwm) + 0.0570553215*pwm + -1.28250616;
    }
  } 
}
