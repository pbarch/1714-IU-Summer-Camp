#include "NodeComm.h"
//#include "Adafruit_Neopixel.h"


NodeComm::NodeComm(){}
void NodeComm::initComm(){
  pinMode(pins[BACK][GND], OUTPUT);
  pinMode(pins[FRONT][GND], OUTPUT);
  digitalWrite(pins[BACK][GND],LOW);
  digitalWrite(pins[FRONT][GND],LOW);
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
