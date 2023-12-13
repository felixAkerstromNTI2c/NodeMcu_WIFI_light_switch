#include "arduino_secrets.h"
/*
  Felix Åkerström 2C
  Tillämpad programmering
  Trådlös strömbrytare
  Kodens fuktion är att rotera två servo-motorer som stänger av ljusströmbrytaren i klassrummet. Motorerna roterar när man trycker på
  strömbrytaren på Arduino IoT Cloud hemsidan, eller i Arduio IoT Cloud appen. Kod och funktioner som har att göra med att koppla
  till WIFI är automatiskt genererade av Arduino IoT Cloud.
  
*/

#include "thingProperties.h"
#include <Servo.h>
Servo myservo1;
Servo myservo2;

void setup() {
  Serial.begin(9600);
  delay(1500);
  myservo1.attach(5); // servo 1 signal pin
  myservo2.attach(4); // servo 2 signal pin

  // kör funktionen thingProperties.h
  // "loggar in" på Nodemcu-brädan
  initProperties();

  // Anslut till Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // funktion för att hämta mer information om nätverksstatuset och koppling till IoT Cloud
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update(); // leta efter nytt värde på IoT Cloud
}

// funktion som körs när nytt värde har tagits emot från IoT Cloud
void onSwitchChange()  {
  if (_switch_) { 
    updateServo(35);
  }
  else {
    updateServo(0);
  }
}
// funktion för hur servomotorerna ska rotera i förhållande till varandra
void updateServo(int vinkel) {
  myservo1.write(35 + vinkel); 
  myservo2.write(vinkel);
}
