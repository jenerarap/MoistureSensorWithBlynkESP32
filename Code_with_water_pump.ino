#define BLYNK_TEMPLATE_ID "TMPL6S9Ogtz9l"
#define BLYNK_TEMPLATE_NAME "plantwatering"
#define BLYNK_AUTH_TOKEN "EIZvCCTky96b35NwXP8GayFeg1qHtUbw"

#define BLYNK_PRINT Serial  
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "EIZvCCTky96b35NwXP8GayFeg1qHtUbw";  // Replace with your Blynk token
char ssid[] = "TDV-OGRENCI";         // Replace with your Wi-Fi SSID
char pass[] = "TDV.062023";          // Replace with your Wi-Fi Password

#define MOISTURE_SENSOR_PIN 35  // Moisture sensor input pin
#define PUMP_RELAY_PIN 5        // Relay for water pump (use GPIO5)
#define VIRTUAL_PIN V1          // Virtual pin for moisture data
#define PUMP_VIRTUAL_PIN 5     // Virtual pin for Blynk switch

BlynkTimer timer;

// Read moisture sensor data and send to Blynk
void sendSensorData() {
  int moistureValue = analogRead(MOISTURE_SENSOR_PIN);  // Read sensor value
  int moisture_final = map(moistureValue, 4095, 0, 0, 100);
  int moisture_data = map(moisture_final, 0, 45, 0, 100);
  
  Serial.print("Moisture Level: ");
  Serial.println(moisture_data);
  
  Blynk.virtualWrite(VIRTUAL_PIN, moisture_data);  // Send data to Blynk
}

// Blynk function to control the water pump
BLYNK_WRITE(PUMP_VIRTUAL_PIN) {
  int pumpState = param.asInt();  // Get switch value from Blynk app
  digitalWrite(PUMP_RELAY_PIN, pumpState);  // Turn pump ON/OFF
  Serial.print("Pump state: ");
  Serial.println(pumpState);
}

void setup() {
  Serial.begin(115200);
  pinMode(PUMP_RELAY_PIN, OUTPUT);  // Set relay pin as output
  digitalWrite(PUMP_RELAY_PIN, LOW); // Ensure pump is OFF at startup

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendSensorData);  // Read sensor every 2 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}
   