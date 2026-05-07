#ifndef __CONFIG__
#define __CONFIG__

#define BT_PIN 2
#define L1 13
#define L2 12
#define L3 11
#define MOTOR_PIN 9

#define D1 30
#define T1 5000 // T1 in millisecondi   
#define D2 20
#define T2 3000 // T2 in millisecondi

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