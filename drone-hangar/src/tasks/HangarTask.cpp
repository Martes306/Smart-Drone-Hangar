#include "HangarTask.h"

HangarTask::HangarTask(ServoMotor *hangarDoor, ProximitySensor *droneDistanceDetector, PresenceSensor *dronePresenceDetector)
{
    this->hangarDoor = hangarDoor;
    this->droneDistanceDetector = droneDistanceDetector;
    this->dronePresenceDetector = dronePresenceDetector;
    state = INSIDE;
    justEntered = true;
}

HangarTask::tick()
{
    switch (state)
    {
    case INSIDE:
        if (checkAndSetJustEntered())
        {
            log("Drone is inside the hangar");
            hangarDoor->setPosition(0);
        }
        break;
    case TAKEOFF:
        if (checkAndSetJustEntered())
        {
            log("Drone is taking off");
            hangarDoor->setPosition(90);
        }
        if (!dronePresenceDetector->isDetected())
        {
            setState(OUTSIDE);
        }
        break;
    case OUTSIDE:
        if (checkAndSetJustEntered())
        {
            log("Drone is outside the hangar");
            hangarDoor->setPosition(90);
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
