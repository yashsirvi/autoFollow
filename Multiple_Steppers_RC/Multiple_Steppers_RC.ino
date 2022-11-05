#include <AccelStepper.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <math.h>

#define PRINT_DEBUG
#define SIGNAL_TIMEOUT 500 

const uint64_t pipeIn = 0xF9E8F0F0E1LL;
RF24 radio(8, 9);
unsigned long lastRecvTime = 0;


int  xAxis, yAxis;
int motorSpeedA = 0;
int motorSpeedB = 0;


struct PacketData
{
  byte xAxisValue;
  byte yAxisValue;
  byte p1;
  byte p2;
} receiverData;

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
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening(); //start the radio receiver

  #ifdef PRINT_DEBUG
  Serial.begin(115200);
  #endif
  for(int i=0;i<numSteppers;i++){
    stepper[i]->setMaxSpeed(200.0*numSteppings);
    stepper[i]->setAcceleration(100.0*numSteppings);
  }
}
 
void loop()
{
     if (radio.isChipConnected() && radio.available())
  {
    radio.read(&receiverData, sizeof(PacketData));

    yAxis = receiverData.p1;
    xAxis = receiverData.p2;

    float LRval = map(xAxis,0,255,-250,250);
    float FBval = map(yAxis,0,255,-250,250);

    moveMotors(LRval,FBval,0);

  }   
  
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

  // might have to change move amount 
  // might have to change direction of movement (move()) as -ve speed is not resulting in reverse motion
  

  for(int i = 0; i < numSteppers; i++){
      steppers[i]->move(-1000); //Check this (might have to change - to + for all or some motors)
      steppers[i]->runSpeed();
    }

}
