// Valid Pin Combinations (Trigger,Echo ) are (D0,D1), (D1,D2), (D3,D2) , (D5,D6),(D6,D7),(D7,D8)
// Invalid combination (D2,D3) , (D2,D4) - Reset problem occurs , (D4,D3)


// Ultra Sonic pins:
#define TRIGGER D5   // D1 (GPIO 4) to Trigger
#define ECHO    D6   // D2 (GPIO 5) to Echo 

void setup() {
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  
  Serial.begin(115200);
 
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

void loop() {
  int distance = readDistance();
  Serial.println(distance);
  delay(1000);
}
