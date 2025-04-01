#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial  
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>


char auth[] = "BLYNK_AUTH_TOKEN";  // Replace with your Blynk token
char ssid[] = "Wifi Name";         // Replace with your Wi-Fi SSID
char pass[] = "Wifi Password";     // Replace with your Wi-Fi Password

#define MOISTURE_SENSOR_PIN 35  
#define VIRTUAL_PIN V1        

BlynkTimer timer;

void sendSensorData() {
  int moistureValue = analogRead(MOISTURE_SENSOR_PIN); // Read sensor value
 int moisture_final = map(moistureValue, 4095, 0, 0, 100);
 int moisture_data = map(moisture_final, 0, 45, 0, 100);
  Serial.print(" ADC Value: ");
  Serial.println(moisture_data);
  
  Blynk.virtualWrite(VIRTUAL_PIN, moisture_data); // Send data to Blynk
}

void setup() {
  Serial.begin(115200); 
  Blynk.begin(auth, ssid, pass);

  timer.setInterval(2000L, sendSensorData); 
}

void loop() {
  Blynk.run();  
  timer.run();  
}