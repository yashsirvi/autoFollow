3#include <AccelStepper.h>
#include <math.h>

#define dirPin1 2
#define stepPin1 3

#define dirPin2 4
#define stepPin2 5

#define dirPin3 6
#define stepPin3 7

#define dirPin4 8
#define stepPin4 9

#define motorInterfaceType 1

//! placeholder values, modify them later
const float max_x = 10; 
const float max_y = 10; 

#define SPEED 1000 
#define ACCELERATION 500 
#define DIA 5.9
#define PI 3.14159

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

  */

  /*
      stepper.move(steps);
      while (stepper.distanceToGo() != 0) {
        stepper.setSpeed(someSpeed);   
        stepper.runSpeed();
      }

  */


#define numSteppers 4

AccelStepper stepper1 = AccelStepper(motorInterfaceType, stepPin1, dirPin1);
AccelStepper stepper2 = AccelStepper(motorInterfaceType, stepPin2, dirPin2);
AccelStepper stepper3 = AccelStepper(motorInterfaceType, stepPin3, dirPin3);
AccelStepper stepper4 = AccelStepper(motorInterfaceType, stepPin4, dirPin4);

AccelStepper* steppers[numSteppers] = {
  &stepper1, 
  &stepper2, 
  &stepper3, 
  &stepper4,   
};

void setup() {
  // Set the maximum speed and acceleration:
   for(int i = 0; i < numSteppers; i++){
        steppers[i]->setMaxSpeed(SPEED);
        steppers[i]->setAcceleration(ACCELERATION);
       // steppers[i]->disableOutputs();
    }
}

void loop() {

  /*
    TODO: figure out whether the current code will keep updating 
    Otherwise we will have to do a move() method as well within moveMotors()
    Time, velocity, distance relation (mainly just get the time)  
  */

  // this is the velocity obtained from calculations according to raspi


  float vx_from_pi = 5.1; //random placeholder constant, replace it
  float vy_from_pi = 6.2; // -- "" -- 

  moveMotors(vx_from_pi,vy_from_pi,0);

}

float VtoSPS(float v){
  return 200*v/(PI*DIA);
}


void moveMotors(float vx, float vy, float w){

  // x, y, w in cm/s (w is most probably 0)
  float v1 = 2*(-sqrt(2)*vx+sqrt(2)*vy+w)/4; 
  float v2 = 2*(-sqrt(2)*vx-sqrt(2)*vy+w)/4;
  float v3 = 2*(sqrt(2)*vx-sqrt(2)*vy+w)/4;
  float v4 = 2*(sqrt(2)*vx+sqrt(2)*vy+w)/4;

  float s1 = VtoSPS(v1);
  float s2 = VtoSPS(v2);
  float s3 = VtoSPS(v3);
  float s4 = VtoSPS(v4);

  stepper1.setSpeed(s1);
  stepper2.setSpeed(s2);
  stepper3.setSpeed(s3);
  stepper4.setSpeed(s4);  

  for(int i = 0; i < numSteppers; i++){
      steppers[i]->runSpeed();
    }

}
