#include <AccelStepper.h>
#include <math.h>

#define dirPin1 2
#define stepPin1 3

#define dirPin2 4
#define stepPin2 5

#define dirPin3 6
#define stepPin3 7

#define dirPin4 8
#define stepPin4 9

#define numSteppings 4 //might have to change this to 8/16/32 to increase speed

#define motorInterfaceType 1

#define SPEED 1000 
#define ACCELERATION 500 
#define DIA 5.9
#define PI 3.14159

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

void setup()
{  
    for(int i=0;i<numSteppers;i++){
      stepper[i]->setMaxSpeed(200.0*numSteppings);
      stepper[i]->setAcceleration(100.0*numSteppings);
    }
    // stepper1.setMaxSpeed(200.0*numSteppings);
    // stepper1.setAcceleration(100.0*numSteppings);
    // //stepper1.moveTo(-1000000);
    
    // stepper2.setMaxSpeed(200.0*numSteppings);
    // stepper2.setAcceleration(100.0*numSteppings);
    // //stepper2.moveTo(1000000);
    
    // stepper3.setMaxSpeed(200.0*numSteppings);
    // stepper3.setAcceleration(100.0*numSteppings);
    // //stepper3.moveTo(1000000); 

    // stepper4.setMaxSpeed(200.0*numSteppings);
    // stepper4.setAcceleration(100.0*numSteppings);
    // //stepper4.moveTo(-1000000); 
}
 
void loop()
{
    moveMotors(0,100,0);
    // 4 microsteppings is working 
}

float VtoSPS(float v){
  return 200*v/(PI*DIA);
}


void moveMotors(float vx, float vy, float w){

  // x, y, w in cm/s (w is most probably 0)
  float v1 = (-sqrt(2)*vx+sqrt(2)*vy+0.5*DIA*w)/4; 
  float v2 = (-sqrt(2)*vx-sqrt(2)*vy+0.5*DIA*w)/4;
  float v3 = (sqrt(2)*vx-sqrt(2)*vy+0.5*DIA*w)/4;
  float v4 = (sqrt(2)*vx+sqrt(2)*vy+0.5*DIA*w)/4;

  float s1 = VtoSPS(v1);
  float s2 = VtoSPS(v2);
  float s3 = VtoSPS(v3);
  float s4 = VtoSPS(v4);

  stepper1.setSpeed(s1*numSteppings);
  stepper2.setSpeed(s2*numSteppings);
  stepper3.setSpeed(s3*numSteppings);
  stepper4.setSpeed(s4*numSteppings);  

  for(int i = 0; i < numSteppers; i++){
      steppers[i]->move(-1000); //Check this (might have to change - to + for all or some motors)
      steppers[i]->runSpeed();
    }

}
