#ifndef CONFIG_H_
#define CONFIG_H_

#define HOUR_SERVO_PIN              (14) 
#define MINUTE_SERVO_PIN            (15)
#define PENDULUM_SENSE_PIN          (4)
#define PENDULUM_TRIGGER_PIN        (5)
#define LED_PIN                     (2)

#define SSID_1                      "OhanaCode"
#define PASS_1                      "0hana0ffice"

#define SSID_2                      "ujagaga"
#define PASS_2                      "ohana130315"

#define UDP_PORT                    (60000)
#define SYNC_TIMEOUT                (1000) 
#define MAX_SECONDS_PER_DAY         (86400ul)
#define SECONDS_PER_12_H            (MAX_SECONDS_PER_DAY / 2)
#define SECONDS_PER_MINUTE          (60)
#define MINUTES_PER_HOUR            (60)
#define SECONDS_PER_HOUR            (SECONDS_PER_MINUTE * MINUTES_PER_HOUR)

// For OTA update
#define DEVICE_NAME                 "OC_ESP_CLOCK"

// For debugging purposes.
//#define TEST_SWEEP

#endif
