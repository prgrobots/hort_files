// Constants
const int flowMeterPin = 14; // GPIO 14 (D5 on most ESP8266 boards)
const float pulsesPerLiter = 350.0; // Pulses per liter for the flow meter

// Variables
volatile unsigned long pulseCount = 0; // Volatile to allow modification in the ISR
unsigned long lastPrintTime = 0; // Time of the last print

// Interrupt Service Routine (ISR) to count pulses
void ICACHE_RAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200); // Initialize Serial Monitor
  pinMode(flowMeterPin, INPUT_PULLUP); // Set flow meter pin as input with internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(flowMeterPin), pulseCounter, FALLING); // Attach interrupt to the ISR
}

void loop() {
  unsigned long currentTime = millis();

  // Print flow rate every 2 seconds
  if (currentTime - lastPrintTime >= 2000) {
    lastPrintTime = currentTime;
    unsigned long elapsedTime = currentTime - lastPrintTime;

    // Prevent division by zero
    if (elapsedTime == 0) {
      elapsedTime = 1; // Set to a small non-zero value to avoid division by zero
    }

    // Calculate flow rate in liters per minute
    float flowRate = 0.0;
    if (pulseCount > 0) {
      flowRate = ((float)pulseCount / pulsesPerLiter) * 60000.0 / elapsedTime;
    }

    Serial.print("Flow Rate: ");
    if (isnan(flowRate)) {
      Serial.println("NaN"); // Print "NaN" if the result is not a number
    } else if (isinf(flowRate)) {
      Serial.println("Inf"); // Print "Inf" if the result is infinity
    } else {
      Serial.print(flowRate/10000, 2); // Print with 2 decimal places
      Serial.println(" L/m");
    }

    pulseCount = 0; // Reset pulse count for the next interval
  }
}