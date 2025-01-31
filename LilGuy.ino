#include "LSM6DS3.h"
#include "Wire.h"

LSM6DS3 lilIMU(I2C_MODE, 0x6A);
float totalAcc = 0;
int threashold = 0;
int sampleRate = 10; //ms delay per cycle (should be low AF)
int boostTime = 250;//Length of time to feel g's before going "AAHHHAHA"
int boostThreshold = 15;//G's


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Call .begin() to configure the IMUs
lilIMU.begin();
}

void loop(){
    totalAcc = sqrt(pow(lilIMU.readFloatAccelX(), 2) + pow(lilIMU.readFloatAccelY(), 2) + pow(lilIMU.readFloatAccelZ(), 2));
    Serial.println(totalAcc);
    delay(10);
    if (totalAcc >= boostThreshold) {
        threashold++;
    }
    else if (threashold > 0){
        threashold--;
    }
    if (threashold >= boostTime/sampleRate){
        threashold = 0;
        Serial.println("BOOST");
        delay(1000);
    }
    
}