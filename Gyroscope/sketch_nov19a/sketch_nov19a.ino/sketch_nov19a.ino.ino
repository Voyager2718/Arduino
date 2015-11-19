#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
bool blinkState = false;
int gxa[4]={0},gya[4]={0},gza[4]={0};
int axa[4]={0},aya[4]={0},aza[4]={0};
int now = 0;

void now_plus_1(int &now){
  if(now==3)
    now=0;
  else
    now += 1;
}

int avg(int array_of_4[4]){
  int a = (int)((array_of_4[0]+array_of_4[1]+array_of_4[2]+array_of_4[3])/4);
  if(a == -1 || a == 1)
    a = 0;
  return a;
}
 
void setup() {
  Wire.begin();
  Serial.begin(38400);
  accelgyro.initialize();
}
void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  axa[now]=gx/16384;
  aya[now]=gy/16384;
  aza[now]=gz/16384;
  
  gxa[now]=gx/131;
  gya[now]=gy/131;
  gza[now]=gz/131;
  
  now_plus_1(now);
  Serial.print("a/g:\t");
  Serial.print(avg(axa)); Serial.print("\t");
  Serial.print(avg(aya)); Serial.print("\t");
  Serial.print(avg(aza)); Serial.print("\t");
  Serial.print(avg(gxa)); Serial.print("\t");
  Serial.print(avg(gya)); Serial.print("\t");
  Serial.println(avg(gza));
  blinkState = !blinkState;
  delay(0);
}
