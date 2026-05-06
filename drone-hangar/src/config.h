#ifndef __CONFIG__
#define __CONFIG__

#define BT_PIN 2
#define L1 13
#define L2 12
#define L3 11
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

bool blinking; 

#endif