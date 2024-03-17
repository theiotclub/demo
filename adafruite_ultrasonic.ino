// Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
//#include "config.h"
#include "AdafruitIO_WiFi.h"


/************************ Example Starts Here *******************************/


#define TRIGGER D5   // D1 (GPIO 4) to Trigger
#define ECHO    D6   // D2 (GPIO 5) to Echo 
#define WIFI_SSID "Psr"
#define WIFI_PASS "satishrao"
#define IO_USERNAME "satishrao"
#define IO_KEY "543edaea183545e7a5fbcc6de40d2006"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// set up the 'digital' feed
AdafruitIO_Feed *digital = io.feed("digital");
int last;

void setup() {

  // set button pin as an input
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  // start the serial connection
  Serial.begin(115200);
   last =0;
  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // grab the current state of the button.
  // we have to flip the logic because we are
  // using a pullup resistor.
  int distance = readDistance();
  
  // save the current state to the 'digital' feed on adafruit io
  Serial.print("sending button -> ");
  Serial.println(distance);
  if(last != distance) { 
      digital->save(distance);
      last = distance;
  }
  delay(5000);
}

int readDistance() {
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  int duration = pulseIn(ECHO, HIGH);
  return (duration/2) / 29.1;
}
