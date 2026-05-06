#include "HangarTask.h"
#include <Arduino.h>

// aggiungere nel costruttore la varibile dell'allarme per poterla considerare prima di atterrare e prima di decollare

HangarTask::HangarTask(ServoMotor *hangarDoor, ProximitySensor *droneDistanceDetector, PresenceSensor *dronePresenceDetector, Led *led, hangar_state *hangarState, alarm_state *alarmState)
{
    this->hangarDoor = hangarDoor;
    this->droneDistanceDetector = droneDistanceDetector;
    this->dronePresenceDetector = dronePresenceDetector;
    this->led = led;
    this->hangarState = hangarState;
    this->alarmState = alarmState;

    state = INSIDE;
    justEntered = true;
    conditionStarted = false;
}

void HangarTask::tick()
{
    switch (state)
    {
    case INSIDE:
        if (checkAndSetJustEntered())
        {
            led->switchOn();
            hangarDoor->setPosition(0);
        }
        if (this->drone_wants_to_takeoff && *this->alarmState == NO_ALARM)
        {
            *drone_wants_to_takeoff = false;
            *hangarState = hangar_state::TAKEOFF;
            setState(TAKEOFF);
        }
        break;
    case TAKEOFF:
    { // è stato deciso che non esiste il caso in cui la manovra venga interrotta e si ritorni allo stato INSIDE: il drone rimane in takeOff fino a quando non ha finito la manovra
        if (checkAndSetJustEntered())
        {
            hangarDoor->setPosition(90);
        }
        // 1. Misurazione
        float dist = droneDistanceDetector->getDistance();

        // 2. Controllo Condizione
        if (dist > D1)
        {
            if (!conditionStarted)
            {
                // Inizia a contare il tempo
                conditionStarted = true;
                conditionStartTime = millis();
            }
            else
            {
                // Controlla quanto tempo è passato
                unsigned long elapsedTime = millis() - conditionStartTime;

                if (elapsedTime > T1)
                {
                    // TEMPO SCADUTO - AZIONE!
                    *hangarState = hangar_state::OUTSIDE; // Aggiorna la variabile dello stato dell' hangar per comunicare con l' LCD e fargli stampare messaggi

                    // Reset e transizione di stato
                    conditionStarted = false;
                    setState(OUTSIDE);
                }
            }
        }
        else
        {
            // Se la condizione viene a mancare prima dello scadere del tempo,
            // azzera il conteggio.
            conditionStarted = false;
        }
        break;
    }
    case OUTSIDE:
        if (checkAndSetJustEntered())
        {
            log("Drone is outside the hangar");
            hangarDoor->setPosition(0);
        }
        if (this->drone_wants_to_land && *this->alarmState == NO_ALARM)
        {
            *drone_wants_to_land = false;
            *hangarState = hangar_state::LANDING;
            setState(LANDING);
        }
        break;
    case LANDING:
        if (checkAndSetJustEntered())
        {
            hangarDoor->setPosition(90);
        }
        if (dronePresenceDetector->isDetected())
        {
            // 1. Misurazione
            float dist = droneDistanceDetector->getDistance();

            // 2. Controllo Condizione
            if (dist < D2)
            {
                if (!conditionStarted)
                {
                    // Inizia a contare il tempo
                    conditionStarted = true;
                    conditionStartTime = millis();
                }
                else
                {
                    // Controlla quanto tempo è passato
                    unsigned long elapsedTime = millis() - conditionStartTime;

                    if (elapsedTime > T2)
                    {
                        // TEMPO SCADUTO - AZIONE!
                        *hangarState = hangar_state::OUTSIDE; // Aggiorna la variabile dello stato dell' hangar per comunicare con l' LCD e fargli stampare messaggi

                        // Reset e transizione di stato
                        conditionStarted = false;
                        setState(OUTSIDE);
                    }
                }
            }
            else
            {
                // Se la condizione viene a mancare prima dello scadere del tempo,
                // azzera il conteggio.
                conditionStarted = false;
            }
        }

    default:
        break;
    }
}

void HangarTask::setState(StateOfHangar s)
{
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long HangarTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

bool HangarTask::checkAndSetJustEntered()
{
    bool bak = justEntered;
    if (justEntered)
    {
        justEntered = false;
    }
    return bak;
}
