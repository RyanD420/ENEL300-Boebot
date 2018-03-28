
#include <Servo.h>
#include <StopWatch.h>

Servo servoLeft; 
Servo servoRight;
int turnRightTime = 758;
int turnLeftTime = 760;
int correctParallel = 7; // 15
int prevTime = 0;
StopWatch sw_millis;
StopWatch sw_total;

void setup() 
{
  Serial.begin(9600);
//MIDDLE DISTANCE SENSOR
 pinMode(7, INPUT); pinMode(8, OUTPUT);
//LEFT DISTANCE SENSOR
 pinMode(9, INPUT); pinMode(10, OUTPUT);
//RIGHT DISTANCE SENSOR
 pinMode(2, INPUT); pinMode(3, OUTPUT); 
 
 tone(4, 3000, 1000); 
 delay(1000); 
 servoLeft.attach(12); 
 servoRight.attach(11); 
 
 servoLeft.writeMicroseconds(1500);
 servoRight.writeMicroseconds(1500);


 int irMiddle = irDetect(8, 7, 38000); // Check for object on middle
 int irLeft = irDetect(10, 9, 38000); // Check for object on left
 int irRight = irDetect(3,2, 38000);
 
 rightwall();
 delay(300);
 parallel();
 stop(300);
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
  int irRight = irDetect(3,2, 38000);
  int irMiddle = irDetect(8, 7, 38000); // Check for object on middle
  int counter=0;

  while(1)
  {
    irLeft = irDetect(10, 9, 38000);
    irRight = irDetect(3,2, 38000);
    irMiddle = irDetect(8, 7, 38000);
    if((irLeft !=0 && sw_millis.elapsed()>2000) || (irRight==0 && sw_total.elapsed()>9000)) // if time it doesn't see wall > 9s and it detects on right break
    {
      break;
    }
    if(irLeft==0)
    {
      sw_millis.reset();
    }
    if(irLeft!=0 && sw_millis.elapsed()<2000) // if time it doesnt detect < 2s make turn left slightly
    {
      sw_millis.start();
      turnLeft(250);
      delay(40);
      counter++;
      
    }
    forward(50);
    delay(20);
  }
}

void rightwall()
{
  int irMiddle = irDetect(8, 7, 38000); 
  
    while(irMiddle != 0) // while doesn't detect middle move forward
    {
        irMiddle = irDetect(8, 7, 38000);
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
   int irMiddle = irDetect(8, 7, 38000);
   int counter=0;
   
  while(1)
  {
   
    irLeft = irDetect(10, 9, 38000);
    irRight = irDetect(3,2, 38000);
    irMiddle = irDetect(8, 7, 38000); 
    if(irRight!=0) // turn right if not detecting right cup
    {
      turnRight(200);
      delay(10);
      
      counter++;
      
      irLeft = irDetect(10, 9, 38000);
      irRight = irDetect(3,2, 38000);
      
      if(irLeft==0 && irRight==0 && counter > 3) //if left and right detecting break
      {
        stop(3000);
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
  while(irMiddle!=0) // detect middle if doesn't see move forward
  {
    irMiddle = irDetect(8, 7, 38000); // Check for object on middle
    forward(50);
  }
  turnRight(660); // go around
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
    forward(50);
    if (irMiddle==0)
    {
      break;
    }
  }
  forward(100);
  stop(10000);
}

void pivotLeft(int time)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1500); // Ri
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
