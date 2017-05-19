/*
 * JackPlateChain.cpp - Library for Daisy Chain Reaction for Dendrite
 * Created By Kevin Lam, May 19, 2017
 * Released for IU Summer Camp
 */

#include "JackPlateChain.h"

JackPlateChain::JackPlateChain(int port){
  
  initializedPort = port;

  //Initializes timer values
  currentTime = millis();
  for (int i = 0; i < 4; i++){
    previousTimeSinceActuation[i] = currentTime - restingDelay;  //To ensure the first actuation does not have to occur after time denoted by restingDelay
  }

  //Declaring Pins as Outputs for Actuation
  pinMode(port_pin[initializedPort][0], OUTPUT);
  pinMode(port_pin[initializedPort][1], OUTPUT);
  pinMode(port_pin[initializedPort][2], OUTPUT);
  pinMode(port_pin[initializedPort][3], OUTPUT);
  
}

void JackPlateChain::propogateAllActuators(float successiveTime){

  //Checks if time is positive to avoid issues with delay, defaults to 0
  if(successiveTime < 0){
    successiveTime = 0;
  }

  //Checks if actuator has rested, then turns it on for TIME_ON, then turns on the next actuator while powering of the current one
  for (int i = 0; i < 4; i++){

    if ((*this).hasRestTimeElapsed(i)){
      digitalWrite(port_pin[initializedPort][i], HIGH);
    }
    delay(TIME_ON);
    digitalWrite(port_pin[initializedPort][i], LOW);
    delay(successiveTime);
  }
  
}


void JackPlateChain::turnOnActuator(int actuatorNumber){
	
	//Checks if actuator has rested, then turns it on for TIME_ON before turning it off
	if ((*this).hasRestTimeElapsed(actuatorNumber)){
		digitalWrite(port_pin[initializedPort][actuatorNumber], HIGH);
		delay(TIME_ON);
		digitalWrite(port_pin[initializedPort][actuatorNumber], LOW);
	}
	
}

bool JackPlateChain::checkIRSensorActivated(int sensorNumber){

  sensorNumber += 3; //For proper pin mapping. I.E. First sensor plugged in is pin number 5 on the port. Pin number 5 has an index of 4.

  //Checks if IR Sensor is triggered
  if (analogRead(port_pin[initializedPort][sensorNumber] > PROXIMITY_RANGE)){
      
      return true;
      
  }

  return false;
}

int JackPlateChain::rawIRSensorValue(int sensorNumber){

  sensorNumber += 3; //For proper pin mapping. I.E. First sensor plugged in is pin number 5 on the port. Pin number 5 has an index of 4.

  return analogRead(port_pin[initializedPort][sensorNumber]);
  
}

bool JackPlateChain::hasRestTimeElapsed(int actuatorNumber){

  //Checks if time from last actuation is greater than restingDelay
  currentTime = millis();
  if (currentTime - previousTimeSinceActuation[actuatorNumber] > restingDelay) {
    previousTimeSinceActuation[actuatorNumber] = currentTime;
    return true;
  }
  return false;
  
}
