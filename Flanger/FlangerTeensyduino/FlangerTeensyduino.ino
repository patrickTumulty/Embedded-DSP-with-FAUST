#include <Audio.h>
#include "FlangerTD.h"

FlangerTD flangerTd;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchChord0 (in, 0, flangerTd, 0);
AudioConnection patchChord1 (flangerTd, 0, out, 0);

int FrequencyKnob = A17;
int WetDryKnob = A16;
int DepthKnob = A15;

int freqVal = 0;
float wdVal = 0;
float depthVal = 0;

void setup() {
 
  AudioMemory(6); // usually 6 is good 
  audioShield.enable();
  audioShield.volume(0.25);
  Serial.begin(9600);
  pinMode(FrequencyKnob, INPUT);
  pinMode(WetDryKnob, INPUT);
  pinMode(DepthKnob, INPUT);
}

void loop() {
  
  freqVal = analogRead(FrequencyKnob);
  if (freqVal == 0)
  {
    freqVal = 0.5;
  }
  else 
  {
    freqVal *= 0.048;
  }
  
  wdVal = analogRead(WetDryKnob);
  if (wdVal == 0)
  {
    wdVal = 0.01;
  }
  else 
  {
    wdVal *= 0.00096;
  }

  
  depthVal = analogRead(DepthKnob);
  if (depthVal == 0)
  {
    depthVal = 0.1;
  }
  else
  {
    depthVal *= 0.00096;
  }

  flangerTd.setParamValue("Fq", freqVal);
  flangerTd.setParamValue("Wet", wdVal);
  flangerTd.setParamValue("Depth", depthVal);
  
  delay(10);
}
