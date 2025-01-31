#include <LSM6DS3.h>
#include "Wire.h"

LSM6DS3 lilIMU(I2C_MODE, 0x6A);
float currentAccMagnitude = 0;//In G's
int counter = 0;
int sampleRate = 1000;//HZ
int boostThreshold = 5;//G's
int boostTimeMS = 250;//Length of time to feel g's before going "AAHHHAHA"

int onTime = 1;//Time Camera is on in minutes after detecting boost



void setup() {
    Serial.begin(115200); 
    lilIMU.begin();
    sampleRate = (1/sampleRate)*1000;// converts HZ to MS to wait at end of loop, hoping that its fast enough to not mater
}

void loop(){
    currentAccMagnitude = pow(lilIMU.readFloatAccelX(), 2) + pow(lilIMU.readFloatAccelY(), 2) + pow(lilIMU.readFloatAccelZ(), 2);
    Serial.println(currentAccMagnitude);
    if (currentAccMagnitude > pow(boostThreshold, 2)) {
        counter++;
    }
    else if (counter > 0){
         counter--;
    }
    if (counter > boostTimeMS/sampleRate){
        counter = 0;
        Serial.println("BOOST");
        delay(onTime*60000);//Min to MS
    }
    delay(sampleRate);
}
