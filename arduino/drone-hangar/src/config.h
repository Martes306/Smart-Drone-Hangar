#ifndef __CONFIG__
#define __CONFIG__

#define TEMP_SENSOR_PIN A0
#define LCD_SDA A4
#define LCD_SCL A5
#define PIR_PIN 2
#define DISTANCE_ECHO_PIN 3
#define DISTANCE_TRIGGER_PIN 4
#define BT_RESET 6
#define MOTOR_PIN 9
#define L1 10
#define L2 11
#define L3 12

#define DISTANCE_TEMP 100

#define D1 30
#define T1 5000 // T1 in millisecondi   
#define D2 20
#define T2 3000 // T2 in millisecondi
#define T3 3000
#define T4 5000
#define TEMP1 50
#define TEMP2 60
#define BT 5000

typedef enum
{
    INSIDE,
    TAKEOFF,
    OUTSIDE,
    LANDING
} hangar_state;

typedef enum
{
    NO_ALARM,
    PRE_ALARM,
    ALARM
} alarm_state;

extern bool blinking;
extern bool drone_wants_to_takeoff;
extern bool drone_wants_to_land; 

#endif