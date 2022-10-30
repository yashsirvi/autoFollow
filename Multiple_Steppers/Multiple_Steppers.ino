// Get info from analog pins on speed of motor 

// Include the AccelStepper library:
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

#define motorInterfaceType 1

#define SPEED 1000 
#define ACCELERATION 500 
#define DIAM 5.9
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

void setup() {
  // Set the maximum speed and acceleration:
   for(int i = 0; i < numSteppers; i++){
        steppers[i]->setMaxSpeed(SPEED);
        steppers[i]->setAcceleration(ACCELARATION);
    }
}

void loop() {
  // random test
  for(int i=0;i<10;i++){
    moveToPos(1,1+i,0);
  }
}

float VtoSPS(float v){
  // steps/sec *  0.03 = rpm 
  // rpm * 2pir(cm)/60 = velocity (cm/s)

  // sps * 0.03 * pi * d(cm) / 60 = v 
  // sps = v * 60 / (0.03*pi*d) = 2000v/pid

  return (v*2000)/(PI*DIAM);
}

void moveToPos(float x, float y, float w){
  // x, y, w in cm/s (w is most probably 0)
  float v1 = (-sqrt(2)*x+sqrt(2)*y+w)/4; 
  float v2 = (-sqrt(2)*x-sqrt(2)*y+w)/4;
  float v3 = (+sqrt(2)*x-sqrt(2)*y+w)/4;
  float v4 = (sqrt(2)*x+sqrt(2)*y+w)/4;

  s1 = VtoSPS(v1);
  s2 = VtoSPS(v2);
  s3 = VtoSPS(v3);
  s4 = VtoSPS(v4);

  stepper1.setSpeed(s1);
  stepper2.setSpeed(s2);
  stepper3.setSpeed(s3);
  stepper4.setSpeed(s4);  
  
  for(int i = 0; i < numSteppers; i++){
      steppers[i]->runSpeed();
    }

}
