// https://github.com/mrdcrowley/ultimate_machine

#include <Bounce.h> // debounce for clean input from switch
#include <LowPower.h> // save energy for batteries
#include <Servo.h>  // servo

#define BUTTON 2  // switch is on pin 2
Servo myservo;
Bounce bouncer = Bounce( BUTTON, 5 ); // Instantiate a Bounce object with a 5 millisecond debounce time
int pos = 0; // variable to store the servo position							
const int SPEED = 1; // how fast to move the servo (1 = fastest)
int status; // pin status (HIGH or LOW)
long previousMillis = 0;        // will store last time LED was updated
int shutdownDelay = 3000;

  
void wakeUp() { }

void goToSleep() {
  unsigned long currentMillis = millis();
  
  Serial.println( currentMillis );
  Serial.println( previousMillis );
  
  if ( currentMillis - previousMillis > shutdownDelay ) {
    Serial.println( "goodnight" );
    previousMillis = currentMillis;
    LowPower.powerDown( SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
}


void setup() {
  myservo.attach( 9 ); // attach the servo on pin 9 to the servo object
  pinMode( BUTTON, INPUT );
  Serial.begin(9600);
  
  attachInterrupt(0, wakeUp, CHANGE);
}

void loop() {
  goToSleep();
  bouncer.update(); // Update the debouncer
  status = bouncer.read(); // Get the update value
  
//  Serial.println(status);
    
  if ( status == 0 ) { // switch turned on, move finger up to turn off switch
    for( pos = pos; pos>=1; pos-=1 ) { // middle value of 1 is all the way out
      myservo.write( pos );  // move the servo to current position
      delay( SPEED );
    }
  } else { // switched turned off, go back in
    for( pos = pos; pos < 130; pos += 1 ) { // middle value of 180 is all the way in
      myservo.write( pos );
      delay( SPEED );
    }
  }
  
  
}
