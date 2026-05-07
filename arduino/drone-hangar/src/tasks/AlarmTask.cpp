#include "AlarmTask.h"
#include <Arduino.h>

AlarmTask::AlarmTask(alarm_state *alarmState)
{
    setState(NOT_ALARMED);
    this->stateTimestamp = 0;

    this->alarmStateExternal = alarmState;
    this->resetButton = new ButtonImpl(BT_PIN);
    this->l3 = new Led(11);
}

void AlarmTask::tick()
{
    switch (state)
    {
    case NOT_ALARMED:
        *alarmStateExternal = NO_ALARM;
        if (condition)
        {
            /* code */
        }
        break;
    case PRE_ALARMED:
        *alarmStateExternal = PRE_ALARM;
        if (condition)
        {
            /* code */
        }
        break;
    case ALARMED:
        *alarmStateExternal = ALARM;
        if (condition)
        {
            /* code */
        }
        break;
    default:
        break;
    }
}