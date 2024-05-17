const int analogPin1 = A0; 
const int analogPin2 = A1; 
const int flowMeter1 = 13;    // Output for flowmeter pulses 1
const int flowMeter2 = 12;    // and 2

unsigned long previousMillis1 = 0; 
unsigned long previousMillis2 = 0; 

int flowState1 = LOW; 
int flowState2 = LOW; 

long interval1 = 0; // Blink interval for LED 1
long interval2 = 0; // Blink interval for LED 2

int counter = 0; // Counter to control the frequency of printing newlines

void setup() {
  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);
  pinMode(flowMeter1, OUTPUT);
  pinMode(flowMeter2, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // Read analog values from pins
  int sensorValue1 = analogRead(analogPin1);
  int sensorValue2 = analogRead(analogPin2);

  // Map analog values to blink intervals
  interval1 = map(sensorValue1, 0, 1023, 0, 350); // set based on actual flowmeter 
  interval2 = map(sensorValue2, 0, 1023, 0, 350); // 1L was 350 pulses

  // Print analog values and blink rates
  Serial.print("Analog Value 1: ");
  Serial.print(sensorValue1);
  Serial.print("\tAnalog Value 2: ");
  Serial.print(sensorValue2);
  Serial.print("\tLED 1 Blink Rate: ");
  Serial.print(interval1);
  Serial.print("\tLED 2 Blink Rate: ");
  Serial.print(interval2);

  // Increment counter
  counter++;

  // Print a newline every 5 iterations
  if (counter >= 5) {
    Serial.println();
    counter = 0; // Reset counter
  }

  // Flow meter pulse 1
  unsigned long currentMillis1 = millis();
  if (currentMillis1 - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis1;
    flowState1 = !flowState1;
    digitalWrite(flowMeter1, flowState1);
  }

  // Flowmeter pulse 2
  unsigned long currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis2;
    flowState2 = !flowState2;
    digitalWrite(flowMeter2, flowState2);
  }
}
