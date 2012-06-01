
enum {
  kPinDriveSpeed = 3,
  kPinPing = 7,
  kPinTurnBrake = 8,
  kPinDriveBrake = 9,
  kPinTurnMotorSpeed = 11,
  kPinDriveMotor = 12,
  kPinTurnMotor = 13,
};

void setup() {
  
  //establish motor direction toggle pins
  pinMode(kPinDriveMotor, OUTPUT); //drive motor -- HIGH = forwards and LOW = backwards
  pinMode(kPinTurnMotor, OUTPUT); //turn motor -- HIGH = left and LOW = right
  
  //establish motor brake pins
  pinMode(kPinDriveBrake, OUTPUT); //brake (disable) the drive motor
  pinMode(kPinTurnBrake, OUTPUT); //brake (disable) the turn motor

  //Turns brake off for drive motor
  digitalWrite(kPinDriveBrake, LOW); 

  //Turns brake on for turn motor
  digitalWrite(kPinTurnBrake, HIGH); 

  //Sets initial speed of drive motor
  analogWrite(kPinDriveSpeed, 255);
  
  //Sets initial direction of drive motor
  digitalWrite(kPinDriveMotor, HIGH);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(kPinPing, OUTPUT);
  digitalWrite(kPinPing, LOW);
  delayMicroseconds(2);
  digitalWrite(kPinPing, HIGH);
  delayMicroseconds(5);
  digitalWrite(kPinPing, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(kPinPing, INPUT);
  duration = pulseIn(kPinPing, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);

  //
  //if objects are less than 12 inches away
  //the robot reverses and turns to the right
  //for 2 seconds
  //
  
  if (inches < 12){
    
    //brake drive motor and pause 1/10 second
    digitalWrite(kPinDriveBrake, HIGH);
    delay(100);

    //
    //setting turn motor
    //
    
    //turn off brake for turn motor 
    digitalWrite(kPinTurnBrake, LOW);

    //set turn motor direction
    digitalWrite(kPinTurnMotor, HIGH);

    //activate turn motor
    analogWrite(kPinTurnMotorSpeed, 255);
    
    //
    //setting drive motor
    //
    
    //turn off brake of drive motor
    digitalWrite(kPinDriveBrake, LOW); 
    
    //set drive motor backwards direction
    digitalWrite(kPinDriveMotor, LOW);
    
    //activate the drive motor
    analogWrite(kPinDriveSpeed, 200);

    
    //backup for 2 seconds
    delay(2000);
    
    //
    //stopping
    //
    
    //brake both motors
    digitalWrite(kPinTurnBrake, HIGH);
    digitalWrite(kPinDriveBrake, HIGH);
    
    
  }
  
  //
  //when nothing is within 12" 
  //the robot simply drives forwards
  //
  
  else{
    
    //
    //Setting drive motor
    //
    
    //set drive motor forward direction
    digitalWrite(kPinDriveMotor, HIGH);
    
    //turn off brake of drive motor
    digitalWrite(kPinDriveBrake, LOW);    
    
    //activate drive motor
    analogWrite(kPinDriveSpeed, 255);
  
  
  }
  
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
