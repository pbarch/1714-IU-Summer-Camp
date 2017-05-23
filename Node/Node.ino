/*
 * Node.ino - Sample Usage Code for Dendrite
 * Created By Adam Francey, May 23, 2017
 * Collaborated with Kevin Lam
 * Released for IU Summer Camp
 * Philip Beesley Architect Inc. / Living Architecture Systems Group
 */

#include "NodeComm.h"
#include "JackPlateChain.h"

#define FORWARD                 0     // Port connected to Node/Dendrite to send instructions to
#define BACKWARD                1     // Port connected to Node/Dendrite to receive instructions from
#define NumJackPlatesOnChain    1     // The number of jack plates chained together
#define JackPlatePort           0     // The port in which the chain of jack plates is plugged into

JackPlateChain chain(JackPlatePort); // Initialize a chain of jack plates on port 0

NodeComm comms; // Initialize inter-node communication object

// Code inside setup() runs once when the Teensy powers on
void setup() {

  // Start serial communication for USB debugging
  Serial.begin(9600);
  Serial.println("Serial communication started");
  
}

// Code inside loop() repeats until the Teensy powers off
void loop() {

  //Check all IRSensors on Jack Plates for detection
  if (chain.checkIRSensorActivated(0) || chain.checkIRSensorActivated(1) || 
  chain.checkIRSensorActivated(2) || chain.checkIRSensorActivated(3))
  {
    comms.sendComm(FORWARD, 1);   //Sends communication to Node connected to Port 1
    chain.propogateAllActuators(0);
    comms.sendComm(FORWARD, 0);   //Terminates communciation
  }
  //Checks for communication in port set by BACKWARD
  if (comms.checkComm(BACKWARD)){

    //Waits for previousNode to complete propogateAllActuators
    delay(4000);
    
    comms.sendComm(FORWARD, 1);   //Sends communication to Node connected to Port 1
    chain.propogateAllActuators(0);
    comms.sendComm(FORWARD, 0);   //Terminates communciation
    
  }


  //sampleUsage();    //Remove initial forward brackets (//) to use function
  
}


// Example usage of functions in JackPlateChain and NodeComm
void sampleUsage(){

  // Loop through each plate
  // Check IR sensor, activate SMA, report back with serial USB
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

  // check for communication from the next node in the chain
  if (comms.checkComm(FORWARD) == HIGH){
    Serial.println("Incoming HIGH signal from next node");
  } else {
    Serial.println("Incoming LOW signal from next node");
  }

  // send a LOW signal to the previous node
  Serial.println("Sending LOW signal to previous node");
  comms.sendComm(BACKWARD,LOW);

  // send a HIGH singal to the next node
  Serial.println("Sending HIGH signal to next node");
  comms.sendComm(FORWARD, HIGH);
  
  
}
