#ifndef CONFIG_H_
#define CONFIG_H_

#define HOUR_SERVO_PIN              (14) 
#define MINUTE_SERVO_PIN            (13)
#define PENDULUM_SENSE_PIN          (5)
#define PENDULUM_TRIGGER_PIN        (4)

#define TIME_SERVER_URL             "http://192.168.0.13:60000"

#define SSID_1                      "HUAWEI-B315-05B6"
#define PASS_1                      "J0HYJGN547T"

#define SSID_2                      "ujagaga"
#define PASS_2                      "ohana130315"

#define UDP_PORT                    (60000)
#define SYNC_TIMEOUT                (1000) 
#define MAX_SECONDS_PER_DAY         (86400ul)
#define SECONDS_PER_12_H            (MAX_SECONDS_PER_DAY / 2)
#define SECONDS_PER_MINUTE          (60)
#define MINUTES_PER_HOUR            (60)
#define SECONDS_PER_HOUR            (SECONDS_PER_MINUTE * MINUTES_PER_HOUR)
#endif
