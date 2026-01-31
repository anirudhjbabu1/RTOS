Ultrasonic sensor send the measured distance via UART to the MCU

When the freeRTOS schedular run the ACC task + ACC flag was set by bluetooth, If the distance is from 10cm to 50 cm, the car moves with adaptive speed, and If the distance is more than 50 cm, the car moves with maximum speed.
