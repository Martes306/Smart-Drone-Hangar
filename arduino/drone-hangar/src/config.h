#ifndef __CONFIG__
#define __CONFIG__

#define BT_PIN 2
#define L1 13
#define L2 12
#define L3 11
#define MOTOR_PIN 9
#define PIR_PIN 8
#define DISTANCE_ECHO_PIN 7
#define DISTANCE_TRIGGER_PIN 6

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

bool blinking;
extern bool drone_wants_to_takeoff;
extern bool drone_wants_to_land; 

#endif