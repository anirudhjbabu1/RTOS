#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Define high-priority handles
QueueHandle_t xSensorQueue;

typedef struct {
    float distance;
    float velocity;
} SensorData_t;

// --- Task 1: Sensor Processing (Medium Priority) ---
void vSensorTask(void *pvParameters) {
    SensorData_t sensorReadings;
    for (;;) {
        // In reality, this would read from a CAN bus or SPI (Radar/LiDAR)
        sensorReadings.distance = read_radar_distance(); 
        sensorReadings.velocity = read_radar_velocity();

        xQueueSend(xSensorQueue, &sensorReadings, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(20)); // Run at 50Hz
    }
}

// --- Task 2: Emergency Braking Logic (High Priority) ---
void vBrakingTask(void *pvParameters) {
    SensorData_t data;
    const float CRITICAL_TTC = 1.2f;

    for (;;) {
        // Wait for data from the sensor task
        if (xQueueReceive(xSensorQueue, &data, portMAX_DELAY)) {
            float ttc = data.distance / data.velocity;

            if (ttc < CRITICAL_TTC && data.velocity > 0) {
                // IMMEDIATE ACTION: Trigger Hardware Interrupt/GPIO for Brakes
                GPIO_Write(BRAKE_ACTUATOR_PIN, HIGH);
                printf("EMERGENCY BRAKE ACTIVATED\n");
            }
        }
    }
}

int main(void) {
    xSensorQueue = xQueueCreate(5, sizeof(SensorData_t));

    // Priority 3 is higher than Priority 2
    xTaskCreate(vSensorTask, "Sensor", 1000, NULL, 2, NULL);
    xTaskCreate(vBrakingTask, "BrakeLogic", 1000, NULL, 3, NULL);

    vTaskStartScheduler();
    for (;;);
}
