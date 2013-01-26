// https://github.com/mrdcrowley/ultimate_machine

#include <Bounce.h> // debounce for clean input from switch
#include <LowPower.h> // save energy for batteries
#include <Servo.h>  // servo

const int SWITCH = 2; // Use pin 2 as wake up pin					
const int SPEED = 1; // how fast to move the servo (1 = fastest)
Servo myservo;
Bounce bouncer = Bounce( SWITCH, 5 ); // Instantiate a Bounce object with a 5 millisecond debounce time
int pos = 0; // variable to store the servo position		

void wakeUp()
{
    // Just a handler for the pin interrupt.
}

void setup() {
  myservo.attach( 9 ); // attach the servo on pin 9 to the servo object
  
    attachInterrupt(0, wakeUp, CHANGE); // Allow wake up pin to trigger interrupt on low.
  pinMode( SWITCH, INPUT );
  Serial.begin( 9600 );
}

void loop() {
        
  bouncer.update(); // Update the debouncer
  int status = bouncer.read(); // Get the update value

  if ( status == LOW ) { // switch turned on, move finger up to turn off switch
    for ( pos = pos; pos>=1; pos-=1 ) { // middle value of 1 is all the way out
      myservo.write( pos );  // move the servo to current position
      delay( SPEED );
      Serial.print( pos );
      Serial.print( "Low\n" );
    }
  } else { // switched turned off, go back in
    for( pos = pos; pos < 130; pos += 1 ) { // middle value of 180 is all the way in
      myservo.write( pos );
      delay( SPEED );
      Serial.print( pos );
      Serial.print( "High\n" );
    }
          
        // Enter power down state with ADC and BOD module disabled.
        // Wake up when wake up pin is low.
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
}
