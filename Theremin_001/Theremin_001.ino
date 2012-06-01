#include <Tone.h>
Tone tone1;
//our array of note frequencies
int note[] = {
NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3,
NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4,
NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5,
NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_C7 };
int pingPin = 7;
int tonePin = 10;
int inches;
int pingDuration;
void setup()
{
tone1.begin(tonePin); //attach tone1 to tonePin
Serial.begin(9600);
}
void loop()
{
pingDuration = getPing(); //read the PING)))
inches = microsecondsToInches(pingDuration); //convert to inches
Serial.print(inches);
Serial.print("in, ");
Serial.println();
if (inches > 3 && inches < 34) //only play if distance is 4 to 33 inches
{
tone1.play(note[29 - (inches - 4)]);
} else if(tone1.isPlaying()) {
tone1.stop();
}
delay(100);
}
int getPing()
{
//send a 10us pulse to wake up the sonar
pinMode(pingPin, OUTPUT);
digitalWrite(pingPin, LOW);
delayMicroseconds(10);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
//get the raw value from the sonar, corresponding to the
//actual time of travel of the ultrasound waves
pinMode(pingPin, INPUT);
return pulseIn(pingPin, HIGH); //return this value
}
int microsecondsToInches(int microseconds)
{
// return the duration divided by 74, the time in milliseconds
// it takes sound to travel one inch out and back, then divided by two
// since we only want the inches to the obstacle.
return microseconds / 74 / 2;
}
