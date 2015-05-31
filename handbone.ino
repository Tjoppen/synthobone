#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=160.1666717529297,141.1666717529297
AudioOutputI2S           i2s2;           //xy=319.16668701171875,130.16665649414062
AudioConnection          patchCord1(waveform1, 0, i2s2, 0);
AudioConnection          patchCord2(waveform1, 0, i2s2, 1);
// GUItool: end automatically generated code

AudioControlSGTL5000     sgtl5000_1;

const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);
  Serial1.begin(57600);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.9);
  
  waveform1.begin(0.9, 1000, WAVEFORM_SAWTOOTH);
  
  //pull-up
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);
  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
}


elapsedMillis volmsec=0;

void loop() {
  int a = analogRead(15);
  float f0 = 41.2;
  float f1 = 58.7;

  /*int mult = digitalRead(24) + 2*digitalRead(25) +
           4*digitalRead(26) + 8*digitalRead(27);*/
  int mult = digitalRead(27) + 2*digitalRead(26) +
           4*digitalRead(25) + 8*digitalRead(24);
  /*int mult = digitalRead(27) + 2*digitalRead(26) +
           3*digitalRead(25) + 4*digitalRead(24);*/

  if (mult == 15) {
    waveform1.amplitude(0);
  } else {
    waveform1.frequency((16-mult)*(f0+(f1-f0)*(a/1023.0)));
    waveform1.amplitude(0.9);
  }

  /*if (volmsec > 50) {
    float vol = a / 1023.0;
    sgtl5000_1.volume(vol); // <-- uncomment if you have the optional
    volmsec = 0;               //     volume pot on your audio shield
  }*/
}



