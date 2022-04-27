#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define L_Btn 40
#define R_Btn 42
#define U_Btn 44
#define D_Btn 46
#define M_Btn 48

#define LED1 22
#define LED2 24
#define LED3 26
#define LED4 28
#define LED5 30

#define Buzzer 50

// 1-User Mode, 2-Position, 3-Vision, 4-Localizing
int mode = 1;

// User Mode
int identified_tree_count = 0;
int fertilized_tree_count = 0;
int water_presentage = 100;
bool identified = false;
bool fertilizing = false;

//Position
// 1-LLH, 2-Odometry
int pos_mode = 1;
float Long = 0;
float Lat = 0;
float Height = 0;
float X = 0;
float Y = 0;
float Z = 0;
unsigned char RTK_status = "Fix";
float RTK_error = 0;

//Vision


//Localizing


U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();

  pinMode(L_Btn,INPUT);
  pinMode(R_Btn,INPUT);
  pinMode(U_Btn,INPUT);
  pinMode(D_Btn,INPUT);
  pinMode(M_Btn,INPUT);

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);

  pinMode(Buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // mode
//  if (L_Btn == HIGH){
//    while (L_Btn == HIGH){
//    }
//    if (mode < 4){
//      mode++;
//    }
//    else {
//      mode = 1;
//    }
//  }
//  if (R_Btn == HIGH){
//    while (R_Btn == HIGH){
//    }
//    if (mode > 2){
//      mode--;
//    }
//    else {
//      mode = 4;
//    }
//  }
//
//  //pos mode
//  if (mode == 2){
//    if (U_Btn == HIGH){
//      while (U_Btn == HIGH){
//      }
//      if (pos_mode == 1){
//        pos_mode = 2;
//      }
//      else {
//        pos_mode = 1;
//      }
//    }
//    if (D_Btn == HIGH){
//      while (D_Btn == HIGH){
//      }
//      if (pos_mode == 1){
//        pos_mode = 2;
//      }
//      else {
//        pos_mode = 1;
//      }
//    }
//  }

  User_Mode();
  delay(1000);
  User_Mode();
  delay(1000);
  User_Mode();
  delay(1000);
}

void User_Mode() {
  char str1[3];
  char str2[3];
  char str3[3];
  strcpy(str1, u8x8_u8toa(identified_tree_count, 2));
  strcpy(str2, u8x8_u8toa(fertilized_tree_count, 2));
  strcpy(str3, u8x8_u8toa(water_presentage, 3));
  
  u8g2.firstPage();
  u8g2.clearBuffer(); 
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(35,10,"User Mode");
//  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,23,"Trees identified  - ");
  u8g2.drawStr(100,23,str1);
  u8g2.drawStr(0,36,"Trees fertilized   - ");
  u8g2.drawStr(100,36,str2);
  u8g2.drawStr(0,49,"Water presentage - ");
  u8g2.drawStr(100,49,str3);
  u8g2.drawStr(117,49,"%");
  if (identified){
    u8g2.drawStr(0,62,"Identified New Tree");
  }
  else if (fertilizing){
    u8g2.drawStr(0,62,"Fertilizing...");
  }
  u8g2.sendBuffer();
}

void Position(int pos_mode) {
  char str1[5];
  char str2[5];
  char str3[5];
  char str4[5];
  char str5[5];
  char str6[5];
  char rtk_err[5];
  strcpy(str1, u8x8_u8toa(Long, 5));
  strcpy(str2, u8x8_u8toa(Lat, 5));
  strcpy(str3, u8x8_u8toa(Height, 5));
  strcpy(str4, u8x8_u8toa(X, 5));
  strcpy(str5, u8x8_u8toa(Y, 5));
  strcpy(str6, u8x8_u8toa(Z, 5));
  strcpy(rtk_err, u8x8_u8toa(RTK_error, 5));
  
  u8g2.firstPage();
  u8g2.clearBuffer(); 
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(40,10,"Position");

  if (pos_mode == 1){
    u8g2.drawStr(0,20,"Longitude - ");
    u8g2.drawStr(100,20,str1);
    u8g2.drawStr(0,30,"Latitude - ");
    u8g2.drawStr(100,30,str2);
    u8g2.drawStr(0,40,"Height - ");
    u8g2.drawStr(100,40,str3);
  }
  else {
    u8g2.drawStr(0,20,"X - ");
    u8g2.drawStr(100,20,str4);
    u8g2.drawStr(0,30,"Y - ");
    u8g2.drawStr(100,30,str5);
    u8g2.drawStr(0,40,"Z - ");
    u8g2.drawStr(100,40,str6);
  }
  u8g2.drawStr(0,50,"RTK Status - ");
  u8g2.drawStr(100,50,RTK_status);
  u8g2.drawStr(0,60,"RTK Error - ");
  u8g2.drawStr(100,60,rtk_err);
  u8g2.sendBuffer();
}
