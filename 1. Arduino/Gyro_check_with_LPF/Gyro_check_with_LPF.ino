#include "MPU9250.h"

MPU9250 mpu; // You can also use MPU9255 as is

float x = 0;
float x_1 = 0;
float x_2 = 0;
float x_3 = 0;
float x_4 = 0;
float y = 0;
float y_1 = 0;
float y_2 = 0;
float g_x = 0;
float g_y = 0;
float g_z = 0;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);
    
    mpu.setup(0x68);  // change to your own address
    delay(5000);

    // calibrate anytime you want to
    mpu.calibrateAccelGyro();
    mpu.calibrateMag();
}

void loop() {
    if (mpu.update()) {
      long t = micros();
      x = mpu.getYaw();
      g_x = mpu.getMagX();
      g_y = mpu.getMagY();
      g_z = mpu.getMagZ();
      
      delay(1);
      // Kaiser 
      //y = -0.034779620592694*x + 0.244821337487594*x_1 + 0.600000000000000*x_2 + 0.244821337487594*x_3 - 0.034779620592694*x_4;
      //y = -0.018284728613279*x + 0.254251115914084*x_1 + 0.55*x_2 + 0.254251115914084*x_3 - 0.018284728613279*x_4;
      
      // Butterworth 20 Hz, 988 samples/s
      //y = x/269.802 + 2*x_1/269.802 + x_2/269.802 + 491.188*y_1/269.802 - 225.386*y_2/269.802;
      
      // Butterworth 15 Hz, 988 samples/s
      y = x/469.535 + 2*x_1/469.535 + x_2/469.535 + 875.814*y_1/469.535 - 410.279*y_2/469.535;
      
      x_4 = x_3;
      x_3 = x_2;
      x_2 = x_1;
      x_1 = x;
      y_2 = y_1;
      y_1 = y;
      //Serial.println(micros() - t);
      Serial.print(x);
      Serial.print(' ');
      Serial.println(y);
      Serial.print(g_x);
      Serial.print(',');
      Serial.print(g_y);
      Serial.print(',');
      Serial.println(g_z);
    }
}
