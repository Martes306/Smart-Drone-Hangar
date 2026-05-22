#include "AlarmTask.h"
#include "devices/Button/ButtonImpl.h"
#include "devices/temperature/TempSensorLM35.h"
#include <Arduino.h>

AlarmTask::AlarmTask(alarm_state *alarmState)
{
    setState(NOT_ALARMED);
    this->stateTimestamp = 0;

    this->alarmStateExternal = alarmState;
    *alarmStateExternal = NO_ALARM;
    this->resetButton = new ButtonImpl(BT_RESET);
    this->l3 = new Led(L3);
    this->tempSensor = new TempSensorTMP36(TEMP_SENSOR_PIN);
}

void AlarmTask::tick()
{
    checkAndSetJustEntered();
    switch (state)
    {
    case NOT_ALARMED:
        l3->switchOff();
        getTemperature();
        if (temp > TEMP1)
        {
            if (elapsedTimeInState() > T3)
            {
                setState(PRE_ALARMED);
                *alarmStateExternal = PRE_ALARM;
            }
        }
        break;
    case PRE_ALARMED:
        l3->switchOff();
        getTemperature();
        if (temp > TEMP2)
        {
            if (elapsedTimeInState() > T4)
            {
                setState(ALARMED);
                *alarmStateExternal = ALARM;
            }
        }
        else if (temp < TEMP1)
        {
            setState(NOT_ALARMED);
            *alarmStateExternal = NO_ALARM;
        }
        break;
    case ALARMED:
        l3->switchOn();
        getTemperature();
        if (resetButton->isPressed() && temp < TEMP2)
        {
            l3->switchOff();
            setState(NOT_ALARMED);
            *alarmStateExternal = NO_ALARM;
        }
        break;
    default:
        break;
    }
}

void AlarmTask::getTemperature()
{
    temp = tempSensor->getTemperature();
}

void AlarmTask::setState(alarmState state)
{
    this->state = state;
    stateTimestamp = millis();
    justEntered = true;
}

long AlarmTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

bool AlarmTask::checkAndSetJustEntered()
{
    bool bak = justEntered;
    if (justEntered)
    {
        justEntered = false;
    }
    return bak;
}