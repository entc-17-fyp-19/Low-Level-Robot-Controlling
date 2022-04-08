#include "MPU9250.h"

MPU9250 mpu; // You can also use MPU9255 as is

float yaw = 0;
float yaw_1 = 0;
float yaw_2 = 0;
float yaw_3 = 0;
float yaw_4 = 0;
float YAW = 0;
float YAW_1 = 0;
float YAW_2 = 0;

float acc_x = 0;
float acc_x_1 = 0;
float acc_x_2 = 0;
float acc_x_3 = 0;
float acc_x_4 = 0;
float ACC_X = 0;
float ACC_X_1 = 0;
float ACC_X_2 = 0;

float vel_x = 0;

float g_x = 0;
float g_y = 0;
float g_z = 0;

float acc_y = 0;
float acc_z = 0;

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
      yaw = mpu.getYaw();
      acc_x = mpu.getAccX();
      acc_y = mpu.getAccY();
      acc_z = mpu.getAccZ();
      g_x = mpu.getMagX();
      g_y = mpu.getMagY();
      g_z = mpu.getMagZ();
      
      delay(1);
      // Butterworth 20 Hz, 988 samples/s
      //YAW = yaw/269.802 + 2*yaw_1/269.802 + yaw_2/269.802 + 491.188*YAW_1/269.802 - 225.386*YAW_2/269.802;
      
      // Butterworth 15 Hz, 988 samples/s
      YAW = yaw/469.535 + 2*yaw_1/469.535 + yaw_2/469.535 + 875.814*YAW_1/469.535 - 410.279*YAW_2/469.535;
      
      yaw_4 = yaw_3;
      yaw_3 = yaw_2;
      yaw_2 = yaw_1;
      yaw_1 = yaw;
      YAW_2 = YAW_1;
      YAW_1 = YAW;

      // Accelerometer
      ACC_X = acc_x/469.535 + 2*acc_x_1/469.535 + acc_x_2/469.535 + 875.814*ACC_X_1/469.535 - 410.279*ACC_X_2/469.535;
      
      acc_x_4 = acc_x_3;
      acc_x_3 = acc_x_2;
      acc_x_2 = acc_x_1;
      acc_x_1 = acc_x;
      ACC_X_2 = ACC_X_1;
      ACC_X_1 = ACC_X;

      // velocities
      vel_x += acc_x;
      
      //Serial.println(micros() - t);
      
//      Serial.print(yaw);
//      Serial.print(' ');
//      Serial.println(YAW);
//      Serial.print(g_x);
//      Serial.print(',');
//      Serial.print(g_y);
//      Serial.print(',');
//      Serial.println(g_z);
//      Serial.print(acc_x);
//      Serial.print(',');
//      Serial.print(ACC_X);
//      Serial.print(',');
//      Serial.print(acc_y);
//      Serial.print(',');
      Serial.println(acc_z);
    }
}
