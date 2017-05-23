/*
 * NodeComm.cpp - Library for Simple Node to Node Communication via 8P Port
 * Created By Adam Francey, May 19, 2017
 * Released for IU Summer Camp
 * Philip Beesley Architect Inc. / Living Architecture Systems Group
 */


#include "NodeComm.h"

NodeComm::NodeComm(){

  pinMode(pins[BACK][GND], OUTPUT);
  pinMode(pins[FRONT][GND], OUTPUT);
  digitalWrite(pins[BACK][GND],LOW);
  digitalWrite(pins[FRONT][GND],LOW);

  //Serial2.begin
  
}

int NodeComm::checkComm(int source){
  // source: BACK or FRONT
  return digitalRead(pins[source][RX]);
  
}

void NodeComm::sendComm(int dest, int val){
  // dest: BACK or FRONT
  // val: HIGH or LOW
  digitalWrite(pins[dest][TX], val);
}
