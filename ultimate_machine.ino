// https://github.com/mrdcrowley/ultimate_machine

#include <Bounce.h> // debounce for clean input from switch
#include <LowPower.h> // save energy for batteries
#include <Servo.h>  // servo

#define SWITCH 2  // switch is on pin 2
Servo myservo;
Bounce bouncer = Bounce( SWITCH, 1 ); // Instantiate a Bounce object with a 5 millisecond debounce time
int pos = 0; // variable to store the servo position
int status; // pin status (HIGH or LOW)
long previousMillis = millis();        // will store last time LED was updated
int shutdownDelay = 3000;      // go to sleep after 3 seconds

void setup() {
  myservo.attach( 9 ); // attach the servo on pin 9 to the servo object
  pinMode( SWITCH, INPUT );
  Serial.begin(57600);
  
  attachInterrupt(0, wakeUp, CHANGE);
}

void loop() {
  bouncer.update(); // Update the debouncer
  status = bouncer.read(); // Get the update value
    
  if ( status == 0 ) { // switch turned on, move finger up to turn off switch
    for( pos = pos; pos >= 1; pos -= 1 ) { // middle value of 1 is all the way out
      myservo.write( pos );  // move the servo to current position
      Serial.println( pos );
    }
  } else { // switched turned off, go back in
    for( pos = pos; pos <= 139; pos += 1 ) { // middle value of 180 is all the way in
      myservo.write( pos );
      Serial.println( pos );
    }
  }
  
  if ( bouncer.duration() > shutdownDelay ) {
    Serial.println("night");
    LowPower.powerDown( SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
}


void wakeUp() { }
