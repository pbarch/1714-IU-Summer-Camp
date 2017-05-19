#include "NodeComm.h"

int FORWARD = 0;
int BACKWARD = 1;

NodeComm comms = NodeComm();

void setup() {
  comms.initComm();
  // put your setup code here, to run once:

}

void loop() {

  comms.sendComm(BACKWARD, LOW);
  // put your main code here, to run repeatedly:

}
