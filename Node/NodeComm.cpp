/*
 * NodeComm.cpp - Library for Simple Node to Node Communication via 8P Port
 * Created By Adam Francey, May 19, 2017
 * Released for IU Summer Camp
 * Philip Beesley Architect Inc. / Living Architecture Systems Group
 */


#include "NodeComm.h"

NodeComm::NodeComm(){

  pinMode(pins[BACKWARD][GND], OUTPUT);
  pinMode(pins[BACKWARD][TX], OUTPUT);
  pinMode(pins[BACKWARD][RX], INPUT);
  pinMode(pins[FORWARD][GND], OUTPUT);
  pinMode(pins[FORWARD][TX], OUTPUT);
  pinMode(pins[FORWARD][RX], INPUT);
  digitalWrite(pins[BACKWARD][GND],LOW);
  digitalWrite(pins[FORWARD][GND],LOW);

  //Serial2.begin
  
}

int NodeComm::checkComm(int source){
  // source: BACKWARD or FORWARD
  return digitalRead(pins[source][RX]);
  
}

void NodeComm::sendComm(int dest, int val){
  // dest: BACKWARD or FORWARD
  // val: HIGH or LOW
  digitalWrite(pins[dest][TX], val);
}
