/*
 * NodeComm.h - Library for Simple Node to Node Communication via 8P Port
 * Created By Adam Francey, May 19, 2017
 * Released for IU Summer Camp
 * Philip Beesley Architect Inc. / Living Architecture Systems Group
 */

#include <Arduino.h>

class NodeComm{

    int transmitter = false;
    int p1_ground = 25;
    int p2_ground = 9; 
    int p1_rx = 32;
    int p1_tx = 6;
    int p2_rx = 22;
    int p2_tx = 10;
    int ledPin = 13;

    
    int BACK = 1; //p2
    int FRONT = 0; //p1
    int GND = 0;
    int RX = 1;
    int TX = 2;
    int pins[2][3] = {{p1_ground,p1_rx,p1_tx},{p2_ground, p2_rx, p2_tx}};

    //SoftwareSerial backwardSerial(pins[BACK][RX], pins[BACK][TX]); 
    //SoftwareSerial forwardSerial(pins[FRONT][RX], pins[FRONT][TX]);

  public:
    NodeComm();
    int checkComm(int source);
    void sendComm(int dest, int val);
  
  };
