// https://github.com/mrdcrowley/ultimate_machine

#include <Servo.h>  // servo stuff

#define SWITCH 2  // switch is on pin 2

Servo myservo;
int pos = 0; // change the servo position later
const int servoSpeed = 6; // 1 is fastest

long previousMillis = 0; // timer for starting shutdown
int shutdownDelay = 2000; // go to sleep after 2 seconds

byte previousState = HIGH; // what state was the button last time

void setup() {
  myservo.attach( 9 ); // attach the servo on pin 9
  pinMode( SWITCH, INPUT_PULLUP );
  Serial.begin( 9600 );
}

void loop() {
  
  byte buttonState = digitalRead(SWITCH); // find out where the switch is
  
  if (buttonState != previousState) { // switch moved
    
    previousMillis = millis(); // get the current time
    previousState = buttonState; // update switch status for comparing next time
    
    if (buttonState == LOW) { // turned on, move finger out
      for ( ; pos >= 1; pos -= 1 ) { // middle value of 1 is all the way out
        myservo.write( pos );  // move the servo to current position
        delay(servoSpeed); // movement speed
      }
    } else { // turned off, move finger back in
      for( ; pos <= 139; pos += 1 ) { // middle value of 180 is all the way in
        myservo.write( pos );
        delay(servoSpeed);
      }
    }
  }
   
}
