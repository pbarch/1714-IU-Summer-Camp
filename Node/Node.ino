#include "NodeComm.h"

int FORWARD = 0;
int BACKWARD = 1;

// the number of jack plates chained together
int NumJackPlatesOnChain = 1;

// the port the the chain of jack plates is plugged into
int JackPlatePort = 0;

// instantiate a chain of jack plates on port 0
JackPlateChain chain(JackPlatePort);

// instantiate inter-node communication object
NodeComm comms;

// sample code that could go inside loop()
void sampleUsage(){

  // loop through each plate
  // check IR sensor, activate SMA, report back with serial USB
  for (int plate = 0; plate < NumJackPlatesOnChain; plate++){

    // example: checking if a sensor has been triggered
    if (chain.checkIRSensorActivated(plate)){
      Serial.print("IR sensor activated on plate ");
      Serial.println(plate);
    }

    // example: checking raw value of IR sensor
    Serial.print("IR sensor value on plate ");
    Serial.print(plate);
    Serial.print(": "); 
    Serial.println(chain.rawIRSensorValue(plate));


    // example: activating SMA
    Serial.print("Activating SMA on plate ");
    Serial.println(plate);
    chain.turnOnActuator(plate);
    
  }

  // check for communication from the previous node in the chain
  if (comms.checkComm(BACKWARD) == HIGH){
    Serial.println("Incoming HIGH signal from previous node");
  } else {
    Serial.println("Incoming LOW signal from previous node");
  }

  if (comms.checkComm(FORWARD) == HIGH){
    Serial.println("Incoming HIGH signal from next node");
  } else {
    Serial.println("Incoming LOW signal from next node");
  }

  // send a LOW signal to the previous node
  Serial.println("Sending LOW signal to previous node")
  comms.sendComm(BACKWARD,LOW);

  // send a HIGH singal to the next node
  Serial.println("Sending HIGH signal to next node");
  comms.sendComm(FOWARD, HIGH);
  
  
}

// code inside setup() runs once when the Teensy powers on
void setup() {

  // start serial communication for USB debugging
  Serial.begin(57600);
  Serial.println("Serial communication started")
  
  //initialize inter-node communication
  comms.initComm();

}

// code inside loop() repeats until the Teensy powers off
void loop() {

  sampleUsage();

}
