#include "LIS2MDLSensor.h"

DevI2C ext_i2c(D14,D15);
LIS2MDLSensor lis2mdl(ext_i2c);

int axes[3];

unsigned long myTime;
int phase = 0;

int maxvalue = -240;
int triggervalue = -400;
int range [] = {-200, -650};

void setup(){
    lis2mdl.init(NULL);
    Serial.begin(115200);
}

void loop(){  
    lis2mdl.getMAxes(axes);
    if ((axes[2] > maxvalue) && (phase == 0)) phase = 1;
    if ((axes[2] < triggervalue) && (phase == 1)) {
      phase = 2;
      myTime = millis();
    }
    if ((axes[2] > maxvalue) && (phase == 2)) phase = 3; 
    if ((axes[2] < triggervalue) && (phase == 3)) phase = 4;
    if ((axes[2] > maxvalue) && (phase == 4)) phase = 5; 
    if ((axes[2] < triggervalue) && (phase == 5)) {
      phase = 0;
      //Serial.printf("%d, ", (millis()-myTime));
    }
    // Step I - Overview
    //Serial.printf("%d, %d, %d\n", axes[0], axes[1], axes[2]);
    
    // Step II - Individual Channel Selection
    Serial.printf("%d, %d, %d\n", range[0], range[1], axes[2]);

    // Step III - State machine
    //if (phase > 1)
    //   Serial.printf("%d, %d, %d\n", millis()-myTime, axes[2], phase*250);
    //else
    //   Serial.printf("%d, %d, %d\n", 0, axes[2], phase*250);
    
    delay(1);
}
