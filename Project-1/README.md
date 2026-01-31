# We will create two tasks:

1. LED Flashing Task: This task will toggle an LED on and off every second.
2. Temperature Reading Task: This task will read from a temperature sensor (like the DHT11) every 2 seconds and send the data to the Serial Monitor

# Components:
ESP32 board

DHT11 temperature and humidity sensor

LED and a suitable resistor (220Ω)

Jumper wires and a breadboard

# Connect the components as follows:
Connect the LED to GPIO Pin 2 through a resistor.

Connect the DHT11 sensor data pin to GPIO 4, VCC to 3.3V, and GND to ground.


# Task

  // Create Task for LED blinking
  xTaskCreate(LEDTask, "LED Task", 1000, NULL, 1, NULL);
  
  // Create Task for temperature reading
  xTaskCreate(TemperatureTask, "Temperature Task", 1000, NULL, 1, NULL);

  # Delay

  vTaskDelay is used for delay
