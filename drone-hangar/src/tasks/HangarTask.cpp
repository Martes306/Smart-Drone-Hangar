#include "HangarTask.h"
#include <Arduino.h>

//aggiungeree nel costruttore la varibile dell'allarme per poterla considerare prima di atterrare e prima di decollare

HangarTask::HangarTask(ServoMotor *hangarDoor, ProximitySensor *droneDistanceDetector, PresenceSensor *dronePresenceDetector, Led *led, hangar_state *hangarState)
{
    this->hangarDoor = hangarDoor;
    this->droneDistanceDetector = droneDistanceDetector;
    this->dronePresenceDetector = dronePresenceDetector;
    this->led = led;
    this->hangarState = hangarState;

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
        if (true) {                                 // Condizione di decollo (es. drone rilevato vicino alla porta)      DA FARE!!!!!     
            *this->hangarState = hangar_state::TAKEOFF;                                         //va controllato prima di cambiare stato se la variabile d'allarme non è già in pre-allarme o allarme            
            setState(TAKEOFF);

        }
        break;
    case TAKEOFF: {                                // è stato deciso che non esiste il caso in cui la manovra venga interrotta e si ritorni allo stato INSIDE: il drone rimane in takeOff fino a quando non ha finito la manovra
        if (checkAndSetJustEntered())
        {
            hangarDoor->setPosition(90);
        }
        // 1. Misurazione
        float dist = droneDistanceDetector->getDistance();

        // 2. Controllo Condizione
        if (dist > D1) {
            if (!conditionStarted) {
                // Inizia a contare il tempo
                conditionStarted = true;
                conditionStartTime = millis(); 
            } else {
                // Controlla quanto tempo è passato
                unsigned long elapsedTime = millis() - conditionStartTime;
                
                if (elapsedTime > T1) { 
                    // TEMPO SCADUTO - AZIONE!
                    *hangarState = hangar_state::OUTSIDE; // Aggiorna la variabile dello stato dell' hangar per comunicare con l' LCD e fargli stampare messaggi
                    
                    // Reset e transizione di stato
                    conditionStarted = false;
                    setState(OUTSIDE);
                }
            }
        } else {
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
        if (droneDistanceDetector->getDistance() < 20)
        {
            setState(LANDING);
        }
        break;
    case LANDING:
        if (checkAndSetJustEntered())
        {
            log("Drone is landing");
            hangarDoor->setPosition(0);
        }
        if (dronePresenceDetector->isDetected())
        {
            setState(INSIDE);
        }
        break;
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
