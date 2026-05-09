#include "BlinkingTask.h"
#include "config.h"
#include <Arduino.h>

BlinkingTask::BlinkingTask(Led *pLed, bool *blinking)
{
    this->pLed = pLed;
    this->blinking = blinking;
    this->justEntered = true;
    setState(OFF);
}

void BlinkingTask::tick()
{
    checkAndSetJustEntered();
    if (*blinking == true)
    {
        switch (state)
        {
        case OFF:
            pLed->switchOff();
            if (elapsedTimeInState() > BT)
            {
                setState(ON);
            }
            break;
        case ON:
            pLed->switchOn();
            if (elapsedTimeInState() > BT)
            {
                setState(OFF);
            }
            break;
        default:
            break;
        }
    }
}

void BlinkingTask::setState(blinkingState state)
{
    this->state = state;
    stateTimestamp = millis();
    justEntered = true;
}

long BlinkingTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

bool BlinkingTask::checkAndSetJustEntered()
{
    bool bak = justEntered;
    if (justEntered)
    {
        justEntered = false;
    }
    return bak;
}
