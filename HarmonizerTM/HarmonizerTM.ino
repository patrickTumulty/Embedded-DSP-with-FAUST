#include <Audio.h>
#include "Harmonizer.h" 


Harmonizer harmonizer;
AudioInputI2S in; // input of audio shield 
AudioOutputI2S out; // output of audio shield
AudioControlSGTL5000 audioShield;
AudioConnection patchChord0 (in, 0, harmonizer, 0);
AudioConnection patchChord1 (harmonizer, 0, out, 0);


int stepVals[] = { 78, 156, 234, 312, 390, 468, 546, 624, 702, 780, 858, 936, 1023 };
int inputValsUp[] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
//int inputValsUp[] = {0, 1, 2, 3, 4, 5 ,6 ,7, 8, 9, 10, 11, 12};
int inputValsUp2[] = {24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12};
//int inputValsUp2[] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
int inputValsDown[] = {0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12};

bool once = true;
bool change = true;
int holdLV = 1025;
int holdHV1 = 1025;
int holdHV2 = 1025;
float holdWD = 1025;
float holdWacky = 1025;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  AudioMemory(6); // usually 6 is good 
  audioShield.enable();
  audioShield.volume(0.25);
}

void loop() {
  int buttonIn = analogRead(A18);
  int LVin = analogRead(A17);
  int HV1in = analogRead(A16);
  int HV2in = analogRead(A15);
  int dryWetIn = int(analogRead(A14) * 0.0967); 
  int LVval = KnobReturn(LVin, stepVals, inputValsDown);
  int HV1val = KnobReturn(HV1in, stepVals, inputValsUp);
  int HV2val = KnobReturn(HV2in, stepVals, inputValsUp2);

  check4ChangeLV(LVval);
  check4ChangeHV1(HV1val);
  check4ChangeHV2(HV2val);
  check4ChangeWD(dryWetIn);

  
  if (buttonIn < 50){
    if (once){
      if (change){
        Serial.println("Off");
        change = false; 
      }
      else {
        Serial.println("On");
        change = true;
      }
      once = false;
    }
  }
  else {
        once = true;
  }
  delay(100);
}


int KnobReturn(int sensor, int valRange[], int returnVals[]){
  if (sensor < valRange[0]){
      return returnVals[0];
  }
  else if (valRange[0] < sensor & sensor < valRange[1]){
    return returnVals[1];
  }
  else if (valRange[1] < sensor & sensor < valRange[2]){
    return returnVals[2];
  }
  else if (valRange[2] < sensor & sensor < valRange[3]){
    return returnVals[3];
  }
  else if (valRange[3] < sensor & sensor < valRange[4]){
    return returnVals[4];
  }
  else if (valRange[4] < sensor & sensor < valRange[5]){
    return returnVals[5];
  }
  else if (valRange[5] < sensor & sensor < valRange[6]){
    return returnVals[6];
  }
  else if (valRange[6] < sensor & sensor < valRange[7]){
    return returnVals[7];
  }
  else if (valRange[7] < sensor & sensor < valRange[8]){
    return returnVals[8];
  }
  else if (valRange[8] < sensor & sensor < valRange[9]){
    return returnVals[9];
  }
  else if (valRange[9] < sensor & sensor < valRange[10]){
    return returnVals[10];
  }
  else if (valRange[10] < sensor & sensor < valRange[11]){
    return returnVals[11];
  }
  else if (valRange[11] < sensor & sensor <= valRange[12]){
    return returnVals[12];
  }
}

void check4ChangeHV2(int value){
  if (holdHV2 == 1025){
    holdHV2 = value;
  }
  else if (holdHV2 != value){
    holdHV2 = value;
    harmonizer.setParamValue("UV2", value);
    Serial.println(value);
  }
}

void check4ChangeHV1(int value){
  if (holdHV1 == 1025){
    holdHV1 = value;
  }
  else if (holdHV1 != value){
    holdHV1 = value;
    harmonizer.setParamValue("UV1", value);
    Serial.println(value);
  }
}

void check4ChangeLV(int value){
  if (holdLV == 1025){
    holdLV = value;
  }
  else if (holdLV != value){
    holdLV = value;
    harmonizer.setParamValue("LV", value);
    Serial.println(value);
  }
}
//
//void check4ChangeWD(float value){
//  if (change){
//    if (holdWacky == 1025){
//      holdWacky = value;
//    }
//    else if (holdWacky != value){
//        holdWacky = value;
//        harmonizer.setParamValue("Wacky", value*0.01); 
//        Serial.println(value);
//      }
//    }
//  else {
//    if (holdWD == 1025){
//      holdWD = value;
//    }
//    else if (holdWD != value){
//       if (value == 0.0){
//        holdWD = 1.0;
//      }
//      else{
//        holdWD = value;
//        harmonizer.setParamValue("Wet/Dry", value*0.01); 
//        Serial.println(value);
//      }
//    }
//  }   
//}

void check4ChangeWD(int value){
  if (holdWD == 1025){
    holdWD = value;
  }
  else if (holdWD != value){
    if (value == 0){
      holdWD = 0.1;
    }
    else{
      holdWD = value;
      harmonizer.setParamValue("Wet/Dry", value*0.01);
      Serial.println(value);
    } 
  }
}
