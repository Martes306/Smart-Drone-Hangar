#include "ControlPanelTask.h"
#include "config.h"
#include <Arduino.h>

ControlPanelTask::ControlPanelTask(hangar_state *hangarState, alarm_state *alarmState, bool *blinking)
{
    state = INSIDE;
    stateTimestamp = 0;
    justEntered = false;

    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    lcd->init();
    lcd->backlight();
    this->blinking = blinking;
    this->hangarState = hangarState;
    this->alarmState = alarmState;
}

void ControlPanelTask::tick()
{
    if (*alarmState == ALARM)
    {
        setState(ALARM);
    }
    else
    {
        switch (*hangarState)
        {
        case INSIDE:
            setState(INSIDE);
            break;
        case TAKEOFF:
            setState(TAKEOFF);
            break;
        case OUTSIDE:
            setState(OUTSIDE);
            break;
        case LANDING:
            setState(LANDING);
            break;
        default:
            break;
        }
    }
    
    switch (state)
    {
    case INSIDE:
        if (checkAndSetJustEntered())
        {
            setState(INSIDE);
            *blinking = false;
            lcd->clear();
            lcd->setCursor(0, 0);
            lcd->print("INSIDE");
        }
        break;
    case TAKEOFF:
        if (checkAndSetJustEntered())
        {
            setState(TAKEOFF);
            *blinking = true;
            lcd->clear();
            lcd->setCursor(0, 0);
            lcd->print("TAKEOFF");
        }
        break;
    case OUTSIDE:
        if (checkAndSetJustEntered())
        {
            setState(OUTSIDE);
            *blinking = false;
            lcd->clear();
            lcd->setCursor(0, 0);
            lcd->print("OUTSIDE");
        }
        break;
    case LANDING:
        if (checkAndSetJustEntered())
        {
            setState(LANDING);
            *blinking = false;
            lcd->clear();
            lcd->setCursor(0, 0);
            lcd->print("LANDING");
        }
        break;
    case ALARM:
        if (checkAndSetJustEntered())
        {
            setState(ALARM);
            *blinking = false;
            lcd->clear();
            lcd->setCursor(0, 0);
            lcd->print("ALARM");
        }
        break;
    default:
        break;
    }
}

void ControlPanelTask::setState(lcdState state)
{
    this->state = state;
    stateTimestamp = millis();
    justEntered = true;
}

long ControlPanelTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

bool ControlPanelTask::checkAndSetJustEntered()
{
    bool bak = justEntered;
    if (justEntered)
    {
        justEntered = false;
    }
    return bak;
}