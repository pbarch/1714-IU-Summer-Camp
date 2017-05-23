/*
 * JackPlateChain.h - Library for Daisy Chain Reaction for Dendrite
 * Created By Kevin Lam, May 19, 2017
 * Released for IU SummerCamp
 */

#ifndef JackPlateChain_h
#define JackPlateChain_h
#include <Arduino.h>        //Include for Pin Mapping on Teensy

// Pin Mappings for Node 3.2, Index starting at 0. I.E. Pin number 1 on P0 Port is port_pin[0][0]
const int port_pin[4][8] = {{3,  4,  5, 20, A16, A11, A2, A3},
                            {25, 32, 6, 21, A17, A13, A15, A20},
                            {9, 10, 22, 23,  14,  A1, A18, A19},
                            {7,  8,  6, 11,  12,  13, 18, 19}};


class JackPlateChain { //Class to dictate behaviour of daisy-chained Jack Plates

  private:
    const int TIME_ON = 1000;           //Time in milliseconds turned on for actuator on Jack Plate
    const int PROXIMITY_RANGE = 500;    //Minimum value needed to trigger a detection for sensor on Jack Plate
    int initializedPort;                //Corresponding port on Node
    int restingDelay = 30000;           //Resting time in milliseconds needed for shape memory alloy to cool down before being contracted again
    int previousTimeSinceActuation[4];  //Holder for last time actuator was on
    int currentTime;                    //Holder for current time

    //Checks if time from last actuation of position number has exceeded restingDelay
    bool hasRestTimeElapsed(int actuatorNumber);
    
  public:

    //Intialize object to corresponding to appropriate port on Node
    JackPlateChain (int port);

    //Takes time in seconds, turns on first SMA if rested, then waits successiveTime, then turns on next if rested while turning off current and so on... Input 0 as parameter for quick succession
    void propogateAllActuators (float successiveTime);

	  //Takes position number of JackPlate/SMA, turns on corresponding SMA if rested for TIME_ON
	  void turnOnActuator(int actuatorNumber);

    //Takes position number of Jack Plate/IRSensor, returns if the specified sensor is activated past PROXIMITY_RANGE. Sensor Number 1 corresponds to first Jack Plate connected to Node, and so on...
    bool checkIRSensorActivated(int sensorNumber);

    //Takes position number of Jack Plate/IRSensor, returns raw value from IR Sensor. Sensor Number 1 corresponds to first Jack Plate connected to Node, and so on...
    int rawIRSensorValue(int sensorNumber);
    
};

#endif
