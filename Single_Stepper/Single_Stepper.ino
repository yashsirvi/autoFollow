/* Example sketch to control a stepper motor with TB6560 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */

/*
  Options: 
    1. Look for some alternative with constant speed (0 accln)
    2. Use conventional method (without library)

    Make algorithms for both cases 

    Confirm 6 switches meaning
*/

// Include the AccelStepper library:
#include <AccelStepper.h>
#include <math.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1

#define SPEED 3000
#define ACCELERATION 500
#define DIAM 5.9
#define PI 3.14159

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed and acceleration:
  Serial.begin(19200);
  stepper.setMaxSpeed(SPEED);
  stepper.setAcceleration(ACCELERATION);
  //stepper.setSpeed(1000);
}

void loop() {
  // // // Set the target position:=
  //stepper.setSpeed(+2000);
  //Serial.println("Here1");
  //Serial.println(stepper.speed());

  //stepper.stop();
  // // Run to target position with set speed and acceleration/deceleration:
  // stepper.runToPosition();

   //delay(1000);
  //stepper.setSpeed(3000);
  //stepper.move(4000);
  //Serial.println("Here2");
  //Serial.println(stepper.speed());
  //stepper.runToPosition();
  // // Move back to zero:

  // delay(1000);
  
  stepper.move(2000);
  stepper.run();

  // float coords_x[]={0,1,2,3,4,5,6,7,8};
  // float coords_y[]={0,0.5,1,2,3,4,6,7,8};

  // for(int i=0;i<7;i++){
  //   float x = coords_x[i+1]-coords_x[i];
  //   float y = coords_y[i+1]-coords_y[i];
  //   moveToPos(x,y,0);
  //   delay(500);
  // }
  // float s = 500;
  // stepper.setSpeed(s);
  // stepper.runSpeed();
}

float VtoSPS(float v){

  // (sps)/(microsteps) = rps 
  //  sps*60/200*(steps option) = rpm
  // => 0.3*sps/(steps option) = rpm
  
  // steps/sec *  0.3 = rpm 
  // rpm * 2pir(cm)/60 = velocity (cm/s)

  // sps * 0.3 * pi * d(cm) / 60 = v 
  // sps = v * 60 / (0.3*pi*d) = 200v/pid

  return (v*200)/(PI*DIAM);
}

void moveToPos(float x, float y, float w){
  // x, y, w in cm/s (w is most probably 0)
  float v = (-sqrt(2)*x+sqrt(2)*y+w)/4; 
  float s = VtoSPS(v);
  stepper.setSpeed(s);
  stepper.runSpeed();
  // maybe runSpeedToPosition 
  // setCurrentPosition
  // moveToPo..
  // but what is position?
}

