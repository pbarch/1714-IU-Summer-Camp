//Global variables
#define SMA_PIN           9     //Pin # for SMA PWM on P2
#define LED_PIN           13    //Pin # for on-board Teensy LED
#define IR_PIN            14    //Pin # for analog-in IR on P2
#define TIME_ON           1     //In Seconds (Less than 1.5s)
#define TIME_OFF          30    //In Seconds (At least 30s)
#define DUTY_CYCLE        75    //Percentage (0% = 0V, 100% = 3.3V)
#define PROXIMITY_RANGE   500   //Sensing Range from IR Sensor (Default is 500)

void setup() {
  // Declarations for Sensor and Actuator Pins
  pinMode(SMA_PIN,OUTPUT);
  pinMode(LED_PIN,OUTPUT); // On-Board Indicator LED
  pinMode(IR_PIN,INPUT);

  //Initialize SMA to resting position
  analogWrite(SMA_PIN,0);

  //Intialize Serial Communication
  Serial.begin(9600);
}

void loop() {
  //Detect Presence for Actuator Movement
  if (analogRead(IR_PIN) > PROXIMITY_RANGE) {

    //Contract SMA by applying current
    analogWrite(SMA_PIN,map(DUTY_CYCLE, 0, 100, 0, 255)); //75% duty cycle = 191, 50% = 127, etc.
    digitalWrite(LED_PIN,HIGH);
    Serial.println("SMA ON");
    delay(TIME_ON*1000); // SMA ON time (ms)

    //Disable current, causing SMA to move to resting position
    //digitalWrite(SMA_PIN,LOW);
    analogWrite(SMA_PIN,0);
    digitalWrite(LED_PIN,LOW);
    Serial.println("SMA OFF");
    delay(TIME_OFF*1000); // SMA OFF time (ms)
    
  }
  
}



