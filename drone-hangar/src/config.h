#ifndef __CONFIG__
#define __CONFIG__

#define BT_PIN 2
#define LED_PIN 13
#define MOTOR_PIN 9

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

#endif