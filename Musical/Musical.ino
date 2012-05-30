#include <Tone.h>

Tone tone1;
//our array of note frequencies
int note[] = {
NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3,
NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4,
NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5,
NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_C7 };
int tonePin = 10;
void setup()
{
  tone1.begin(tonePin); //attach tone1 to tonePin
}
void loop()
{
  for (int i = 0; i <29; ++i)
  {
    tone1.play(note[i]);
    delay(100);
  }
}
