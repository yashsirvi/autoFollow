#include<math.h>

// Define stepper motor connections and steps per revolution:
#define numSteppings 32

#define stepsPerRevolution 200*numSteppings

#define dirPin1 2
#define stepPin1 3

#define dirPin2 4
#define stepPin2 5

#define dirPin3 7
#define stepPin3 6

#define dirPin4 8
#define stepPin4 9

//! placeholder values, modify them later
const float max_x = 10; 
const float max_y = 10; 
 
#define DIA 5.9
#define PI 3.14159

#define numSteppers 4

  /*
    max speed = 2.5 m/s = 250 
    corresponding RPM = 809.262
    corresponding steps per second = 2697.541

    Calculations: 

        (sps)/(microsteps) = rps 
        sps*60/(200*(steps option)) = rpm
        => 0.3*sps/(steps option) = rpm
  
        steps/sec *  0.3 = rpm 
        rpm * 2pir(cm)/60 = velocity (cm/s)

        sps * 0.3 * pi * d(cm) / 60 = v 
        sps = v * 60 / (0.3*pi*d) = 200v/pi*d

        Observations: 
          on doubling step, delayMicroSeconds amount got halved 
          example: for 32 steppings, 12.5 worked best 

          number of iterations of for loop controls time of spinning / no. of revolutions 
        
  */


void setup() {
  // Declare pins as output:
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);

  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  
  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);

}

void loop() {

  float x_from_pi = 5.1; //random placeholder constant, replace it
  float y_from_pi = 6.2; // -- "" -- 

  moveMotors(x_from_pi,y_from_pi,0);

}

void move(int stepPin, int dirPin, int pulses, int speed, int direction){
  
  // direction = 1 -> clockwise
  // direction = 2 -> anticlockwise
  digitalWrite(dirPin, direction);

  // 1 iteration of for loop = 1 microstep of motor

  // 1 microstep -> 800*K/numSteppings microseconds 
  // 200*numSteppings microsteps = 1 revolution -> 800K microseconds
  // 1 revolution in 800K microseconds 
  // (10^6/800K) revolutions per second 
  //  10^4*pi*d/(8K) cm (or m) per second
  // 
  
  float k = 1250*PI*DIA/speed;

  // TODO: adjust speed
  // also try stepper.step() method of accelstepper

   for (int i = 0; i < pulses; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(400*k/numSteppings);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(400*k/numSteppings);
  }

}

int dir(float speed){
  return speed>0;
}

void moveMotors(float x,float y,float w){

  float v1 = 2*(-sqrt(2)*vx+sqrt(2)*vy+0.5*DIA*w)/4; 
  float v2 = 2*(-sqrt(2)*vx-sqrt(2)*vy+0.5*DIA*w)/4;
  float v3 = 2*(sqrt(2)*vx-sqrt(2)*vy+0.5*DIA*w)/4;
  float v4 = 2*(sqrt(2)*vx+sqrt(2)*vy+0.5*DIA*w)/4;

  // these are like the proportionality constants 
  // speed can be assigned by multiplying it with a suitable constant 
  // suitable constant = ?
  
  float suitable_constant;
  int pulses=10*stepsPerRevolution;
  
  move(dirPin1,stepPin1,pulses,v1,dir(v1));
  move(dirPin2,stepPin2,pulses,v2,dir(v2));
  move(dirPin3,stepPin3,pulses,v3,dir(v3));
  move(dirPin4,stepPin4,pulses,v4,dir(v4));

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

