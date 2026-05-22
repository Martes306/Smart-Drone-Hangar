#include <Arduino.h>
#include "config.h"
#include "kernel/Scheduler.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"
#include "tasks/BlinkingTask.h"
#include "tasks/AlarmTask.h"
#include "tasks/CommunicationTask.h"
#include "tasks/ControlPanelTask.h"
#include "tasks/HangarTask.h"

Scheduler sched;

/* Global variables declared extern in config.h */
bool blinking;
bool drone_wants_to_takeoff;
bool drone_wants_to_land;

/* Shared states */
alarm_state alarmState = NO_ALARM;
hangar_state hangarState = INSIDE;

void setup()
{
    MsgService.init();
    MsgService.sendMsg("Arduino Hangar System Booting...");
    
    sched.init(50); 
    MsgService.sendMsg("Scheduler initialized.");

    blinking = false;
    drone_wants_to_land = false;
    drone_wants_to_takeoff = false;

    MsgService.sendMsg("Initializing tasks...");
    Task* blinkingTask = new BlinkingTask(&blinking);
    blinkingTask->init(100);
    Task* alarmTask = new AlarmTask(&alarmState);
    alarmTask->init(100);
    Task* communicationTask = new CommunicationTask(&hangarState, &alarmState, &drone_wants_to_takeoff, &drone_wants_to_land);
    communicationTask->init(100);
    Task* controlPanelTask = new ControlPanelTask(&hangarState, &alarmState, &blinking);
    controlPanelTask->init(100);
    Task* hangarTask = new HangarTask(&hangarState, &alarmState, &drone_wants_to_takeoff, &drone_wants_to_land);
    hangarTask->init(100);

    sched.addTask(blinkingTask);
    sched.addTask(alarmTask);
    sched.addTask(communicationTask);
    sched.addTask(controlPanelTask);
    sched.addTask(hangarTask);  
}

void loop()
{
    sched.schedule();
}