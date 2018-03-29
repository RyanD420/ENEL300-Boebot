
#include <Servo.h> // servo motor library
#include <StopWatch.h> // timer library

Servo servoLeft; // defining left and right motors
Servo servoRight;
int turnRightTime = 758; // due to motor discrepancy different times for right turns through tests we found these to be the best
int turnLeftTime = 760;
StopWatch sw_millis; // time away from wall
StopWatch sw_total; // total time of the parallel to wall stage

void setup() 
{
  Serial.begin(9600);
//MIDDLE DISTANCE SENSOR 
 pinMode(7, INPUT); pinMode(8, OUTPUT);
//LEFT DISTANCE SENSOR
 pinMode(9, INPUT); pinMode(10, OUTPUT);
//RIGHT DISTANCE SENSOR
 pinMode(2, INPUT); pinMode(3, OUTPUT); // all for telling arduino what pins are for each sensor
 
 tone(4, 3000, 1000); 
 delay(1000); 
 servoLeft.attach(12); //servo pins
 servoRight.attach(11); // servo pins
 
 servoLeft.writeMicroseconds(1500);
 servoRight.writeMicroseconds(1500);


 int irMiddle = irDetect(8, 7, 38000); // Check for object on middle
 int irLeft = irDetect(10, 9, 38000); // Check for object on left
 int irRight = irDetect(3,2, 38000); // Check for objects on right
 
 rightwall(); // different stages, know which sensor to check what to do at each stage etc.
 delay(300); // trouble shooting stage
 parallel();
 stop(300); // for troubleshooting which stage
 cups();
 lastcup();
}
void loop()
{
  
}


void parallel() // follows wall and does turn around wall
{
  sw_total.start();
  int irLeft = irDetect(10, 9, 38000); // Check for object on left
  int irRight = irDetect(3,2, 38000); // Check for objects on right
  int irMiddle = irDetect(8, 7, 38000); // Check for object on middle
  while(1)
  {
    irLeft = irDetect(10, 9, 38000);
    irRight = irDetect(3,2, 38000);
    irMiddle = irDetect(8, 7, 38000); //re initialize
    if((irLeft !=0 && sw_millis.elapsed()>2000) || (irRight==0 && sw_total.elapsed()>9000)) // if the time it doesn't detect the wall is greater than 9 and if the right sensor detecting (first cup) break from the parallel function
    {
      break;
    }
    if(irLeft==0)
    {
      sw_millis.reset(); // reset timer if it does detect so it knows it isn't past the wall yet
    }
    if(irLeft!=0 && sw_millis.elapsed()<2000) // if time that it doesn't detect the wall less than 2 turn left slightly to be more parallel to wall
    {
      sw_millis.start();
      turnLeft(250);
      delay(40);
    }
    forward(50); // loop the forward so it constantly checks for the left sensor and knows which state it is in
    delay(20);
  }
}

void rightwall()
{
  int irMiddle = irDetect(8, 7, 38000); 
  
    while(irMiddle != 0) // while doesn't detect middle move forward
    {
        irMiddle = irDetect(8, 7, 38000); // update irMiddle
        forward(50);
    }
    forward(50); //turn right 90 degrees
    turnRight(660); 
    stop(300);
}
void cups()
{
  int irLeft = irDetect(10, 9, 38000);
   int irRight = irDetect(3,2, 38000);
   int irMiddle = irDetect(8, 7, 38000); //re initialize
   int counter=0;
   
  while(1)
  {
   
    irLeft = irDetect(10, 9, 38000);
    irRight = irDetect(3,2, 38000);
    irMiddle = irDetect(8, 7, 38000); // update sensors
    if(irRight!=0) // turn right if not detecting right cup
    {
      turnRight(200); // pivot right slightly to align itself between cups
      delay(10);
      
      counter++; //count the number of times it tries to align itself
      
      irLeft = irDetect(10, 9, 38000);
      irRight = irDetect(3,2, 38000); //update sensors
      
      if(irLeft==0 && irRight==0 && counter > 3) //if left and right sensors detecting break because its between the first cup and wall, counter to ensure it doesn't break due to the wall and cup
      {
        stop(3000); //to know which stage it is on ( troubleshooting )
        break;
      }
    }
    forward(10); //forwawrd between pivots
    delay(30);
  }
}

void lastcup()
{
  int irMiddle = irDetect(8, 7, 38000); // Check for object on middle
  while(irMiddle!=0) // detect middle if doesn't see last cup move forward
  {
    irMiddle = irDetect(8, 7, 38000); // Check for object on middle
    forward(50); // move forward up to last cup
  }
  turnRight(660); // go around the cup in a rectangle shaped path
  stop(10);
  forward(1000);
  delay(10);
  turnLeft(660);
  stop(10);
  forward(2000);
  delay(10);
  turnLeft(660);
  stop(10);
  forward(1000);
  delay(10);
  turnRight(660);
  while(1)
  {
    irMiddle = irDetect(8, 7, 38000); // Check for object on middle
    forward(50); // forward to move up to back wall 
    if (irMiddle==0) // if detects back wall break
    {
      break;
    }
  }
  forward(100); // sensor detects too early so force the boebot to go forward slightly
  stop(10000); // stop in the zone
}

void pivotLeft(int time)
{
  servoLeft.writeMicroseconds(1700); // turn left motor only
  servoRight.writeMicroseconds(1500); // keep still
  delay(time);
}

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
 tone(irLedPin, frequency, 8); // IRLED 38 kHz for at least 1 ms
 delay(1); // Wait 1 ms
 int ir = digitalRead(irReceiverPin); // IR receiver -> ir variable
 delay(1); // Down time before recheck
 return ir; // Return 1 no detect, 0 detect
}

void forward(int time) // Forward function
{
 servoLeft.writeMicroseconds(1596); // Left wheel counterclockwise
 servoRight.writeMicroseconds(1300); // Right wheel clockwise
 delay(time); // Maneuver for time ms
}

void turnLeft(int time) // Left turn function
{
 servoLeft.writeMicroseconds(1300); // Left wheel clockwise
 servoRight.writeMicroseconds(1300); // Right wheel clockwise
 delay(time); // Maneuver for time ms

}

void turnRight(int time) // Right turn function
{
 servoLeft.writeMicroseconds(1700); // Left wheel counterclockwise
 servoRight.writeMicroseconds(1650); // Right wheel counterclockwise
 delay(time); // Maneuver for time ms
}

void backward(int time) // Backward function
{
 servoLeft.writeMicroseconds(1400); // Left wheel clockwise
 servoRight.writeMicroseconds(1700); // Right wheel counterclockwise
 delay(time); // Maneuver for time ms
} 

void halforward(int time) // Forward function
{
 servoLeft.writeMicroseconds(1600); // Left wheel counterclockwise
 servoRight.writeMicroseconds(1400); // Right wheel clockwise
 delay(time); // Maneuver for time ms
}

void stop(int time) // Backward function
{
 servoLeft.writeMicroseconds(1500); // Left wheel clockwise
 servoRight.writeMicroseconds(1500); // Right wheel counterclockwise
 delay(time); // Maneuver for time ms
} 
