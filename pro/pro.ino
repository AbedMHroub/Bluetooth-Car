int carSpeed = 75; // maybe changed after testing
int incValue = 10; // maybe changed after testing (increment & decrement)
char command;
 
#define left_forward 4
#define left_reverse 5
#define right_forward 6
#define right_reverse 7
#define enableA 11 // left
#define enableB 3 // right

#include <Servo.h>

#define echoPin 12 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 13 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

  
void setup() {
 
  pinMode(left_forward, OUTPUT);   //left motors forward
  pinMode(left_reverse, OUTPUT);   //left motors reverse
  pinMode(right_forward, OUTPUT);   //right motors forward
  pinMode(right_reverse, OUTPUT);   //right motors reverse
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  // check if valid here and if acceptable to set it before direction! :)) 
  // if no, we will add the speed command in forward(), backword(), left() and right() functions.
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
 
  analogWrite(enableA, carSpeed);
  analogWrite(enableB, carSpeed);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);
 
}
 
void loop() {
 
  // interrupt for ultrasonic ?
  // what should we do if two charachters is clicked ?
  // is it valid to call analogWrite () in setup() as a default speed ?
  servoLR();
  ultrasonic();
  if (Serial.available() > 0) {
 
    command = Serial.read(); 
    // Change pin mode only if new command is different from previous.   
    // Serial.println(command);
    switch(command){
      case 'F':  
        forward();
        break;
      case 'B':  
        backward();
        break;
      case 'L':  
        left();
        break;
      case 'R':
        right();
        break;
      case 'S':
        stopCar();
        break;
      case '+':
       increaseSpeed();
       break;
      case '-':
       decreaseSpeed();
       break;
       default: // if unwanted charachter
       // nothing to do
       break;
      }
      
      
  }
}
 
//move forward(all motors rotate in forward direction)
void forward() {
  Serial.println("Hello F");
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_reverse, HIGH);
  digitalWrite(right_reverse, LOW);
}
 
//move reverse (all motors rotate in reverse direction)
void backward() {
  Serial.println("Hello B");
  digitalWrite(right_forward, LOW);
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_reverse, LOW);
  digitalWrite(right_reverse, HIGH);
}
 
//turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
void left() {
  Serial.println("Hello L");
  digitalWrite(right_forward, LOW);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_reverse, HIGH);
  digitalWrite(right_reverse, LOW); 
}
 
//turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
void right() {
  Serial.println("Hello R");
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_reverse, LOW);
  digitalWrite(right_reverse, LOW);
}
 
void stopCar() {
  Serial.println("Hello STOP");
  digitalWrite(left_forward, LOW);
  digitalWrite(left_reverse, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_reverse, LOW);
}
 
void increaseSpeed() {
  if (carSpeed + incValue <= 225) {
    carSpeed += incValue;
    analogWrite(enableA, carSpeed);
    analogWrite(enableB, carSpeed);
  }       
} 
 
void decreaseSpeed() {
   if (carSpeed - incValue >= 0) {
     carSpeed -= incValue;
     analogWrite(enableA, carSpeed);
     analogWrite(enableB, carSpeed);
   }          
} 


void servoLR() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(6);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(6);                       // waits 15ms for the servo to reach the position
  }
}

void ultrasonic() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(  (distance >= 0) && (distance <= 40)  ) 
  {
    stopCar();
  } 
 }
