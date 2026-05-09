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
