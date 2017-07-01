#include <Servo.h>

Servo myservo;  
int pos = 0; 

void setup() {
  // Attached servo to a PWM pin.
  myservo.attach(10);
}

void loop() {
  // This is the center for my servo. I will be different for yours.
  int center=73;
  int range=20;
  myservo.write(73);
  
  delay(1000);

  while(true) {
    for(pos=-range; pos <=range;pos+=1) {
      myservo.write(center+pos);  
      delay(30);
    }
    for(pos=range; pos <=-range;pos-=1) {
      myservo.write(center+pos);  
      delay(30);
    }       
  }
}
