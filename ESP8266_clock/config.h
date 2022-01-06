#ifndef CONFIG_H_
#define CONFIG_H_

#define LED_STRIP_PIN               (12)    
#define SERVO_PIN                   (14) 

#define TIME_SERVER_URL             "http://192.168.0.13:60000"

#define SSID_1                      "HUAWEI-B315-05B6"
#define PASS_1                      "J0HYJGN547T"

#define SSID_2                      "ujagaga"
#define PASS_2                      "ohana130315"

#define UDP_PORT                    (60000)
#define SYNC_TIMEOUT                (500) 
#define MAX_SECONDS_PER_DAY         (86400ul)
#define SECONDS_PER_12_H            (MAX_SECONDS_PER_DAY / 20)
#endif
