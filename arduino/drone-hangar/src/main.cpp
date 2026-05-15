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

void setup()
{
    MsgService.init();
    sched.init(50); 

    blinking = false;
    alarm_state alarmState = NO_ALARM;
    hangar_state hangarState = INSIDE;

    Task* blinkingTask = new BlinkingTask(&blinking);
    Task* alarmTask = new AlarmTask(&alarmState);
    Task* communicationTask = new CommunicationTask();
    Task* controlPanelTask = new ControlPanelTask(&hangarState, &alarmState, &blinking);
    Task* hangarTask = new HangarTask(&hangarState, &alarmState);
}

void loop()
{
}