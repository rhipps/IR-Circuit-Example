#include <IRremote.h>

int RECV_PIN = 11; // define input pin on Arduino 
IRrecv irrecv(RECV_PIN);  // decode_results class is defined in IRremote.h

constexpr long remoteButtons[] = {
  16738455, //Zero Button
  16724175, //One Button
  16718055, //Two Button
  16753245  //Power Button
};

typedef struct LED {
  int outPin;
  bool isOn;
} LED;

LED GREEN_LED = {8, false };
LED RED_LED = {9, false };
LED BLUE_LED = {10, false };

void setup() { 
  Serial.begin(9600); 
  irrecv.enableIRIn(); // Start the receiver 
  
  //Setup the LED output pins
  pinMode(GREEN_LED.outPin, OUTPUT);
  pinMode(RED_LED.outPin, OUTPUT);
  pinMode(BLUE_LED.outPin, OUTPUT);
} 

//Check if the LED is on or off and toggle it
void toggleLed(LED *led) {
  if (led->isOn){
    digitalWrite(led->outPin, LOW);
    Serial.println("OFF");
  } else {
    digitalWrite(led->outPin, HIGH);
    Serial.println("ON");
  }
  led->isOn = !(led->isOn);
}

void turnOffLed(LED *led) {
  digitalWrite(led->pin, LOW);
  led->isOn = false;
}

void loop() { 
  if (irrecv.decode()) {
    
    irrecv.printIRResultShort(&Serial);
    
    switch(irrecv.results.value){
      case remoteButtons[0]:
        Serial.println("GREEN GREEN GREEN");
        toggleLed(&GREEN_LED);
      break;
      case remoteButtons[1]:
        Serial.println("RED RED RED");
        toggleLed(&RED_LED);
      break; 
      case remoteButtons[2]:
        Serial.println("BLUE BLUE BLUE");
        toggleLed(&BLUE_LED);
      break;
      case remoteButtons[3]:
        Serial.println("Turn them off");
        turnOffLed(&GREEN_LED);
        turnOffLed(&RED_LED);
        turnOffLed(&BLUE_LED);
      break; 
      default:
        Serial.println(irrecv.getProtocolString());
        Serial.println(irrecv.results.value);
        Serial.println("Not a registered button");
    }
    Serial.println(); 
    
    irrecv.resume(); // Receive the next value 
  }
  delay (100); // small delay to prevent reading errors
}
