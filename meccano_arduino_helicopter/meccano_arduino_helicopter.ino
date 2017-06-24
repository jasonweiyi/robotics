#include <IRremote.h>

#define greenPin 12   // Pin for the green LED light.
#define redPin 13     // Pin for the red LED light.
#define irPin 11      // Pin for IR receiver.

#define enA 10        // Pin for DT motor speed control, must be a PWM pin.
#define in1 9         // Pin to control motor direction. 
#define in2 8         // Pin to control motor direction.

#define GREEN_BUTTON 33454215   // The green button value from the particular remotor I'm using.
#define RED_BUTTON 33441975     // The red button value.
#define OK_BUTTON 33427695      // The ok button value.

// IR receiver related variable.
IRrecv irrecv(irPin);
decode_results results;

void setup() {
  irrecv.enableIRIn();
  
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

bool greenOn=false;   // Indicate whether the green LED is on.
bool redOn=false;     // Indicate whether the red LED is on.
bool powerOn=false;   // Indicate whether the DC motor/blade for the helicopter is running.

void blade(bool on) {
  powerOn=on;
  if(powerOn) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 40); 
  } else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);    
  }
}

void light(int pin, bool on) {
  digitalWrite(pin, on?HIGH:LOW);
  if(pin==greenPin) greenOn=on;
  if(pin==redPin) redOn=on;
}
 
void loop() { 
    while(true) {
        if (irrecv.decode(&results))
        {
          long result=results.value;
          switch(results.value) {
            case RED_BUTTON: light(redPin, !redOn); break;
            case GREEN_BUTTON: light(greenPin, !greenOn); break;
            case OK_BUTTON: blade(!powerOn); break;
            default: break;
          }
          irrecv.resume(); // Receive the next value
        }
    }   
}
