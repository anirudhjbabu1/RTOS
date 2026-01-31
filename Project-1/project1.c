#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <DHT.h>

#define DHTPIN 4          // Define the pin for the DHT11 sensor
#define DHTTYPE DHT11    // Define the type of sensor
#define LED_PIN 2        // Define the LED pin

DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT object

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();

  // Create Task for LED blinking
  xTaskCreate(LEDTask, "LED Task", 1000, NULL, 1, NULL);
  
  // Create Task for temperature reading
  xTaskCreate(TemperatureTask, "Temperature Task", 1000, NULL, 1, NULL);
}

void loop() {
  // Empty loop as tasks are handled by FreeRTOS
}

void LEDTask(void *pvParameters) {
  while (true) {
    digitalWrite(LED_PIN, HIGH); // Turn LED on
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    digitalWrite(LED_PIN, LOW); // Turn LED off
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}

void TemperatureTask(void *pvParameters) {
  while (true) {
    float h = dht.readHumidity(); // Read humidity
    float t = dht.readTemperature(); // Read temperature

    // Check if any reads failed and exit early
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      vTaskDelay(2000 / portTICK_PERIOD_MS); // Delay before next attempt
      continue;
    }

    // Print the values
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");

    vTaskDelay(2000 / portTICK_PERIOD_MS); // Delay for 2 seconds
  }
}
