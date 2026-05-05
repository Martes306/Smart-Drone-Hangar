#ifndef __HANGAR_TASK__
#define __HANGAR_TASK__

#include "kernel/Task.h"
#include "devices/ServoMotor/ServoMotor.h"
#include "devices/pir/PresenceSensor.h"
#include "devices/ProximitySensor/ProximitySensor.h"
#include <WString.h>

class HangarTask : public Task
{

public:
    HangarTask(ServoMotor *hangarDoor, ProximitySensor *droneDistanceDetector, PresenceSensor *dronePresenceDetector);
    void tick();

private:
    void setState(int state);
    long elapsedTimeInState();
    void log(const String &msg);

    bool checkAndSetJustEntered();

    enum
    {
        INSIDE,
        TAKEOFF,
        OUTSIDE,
        LANDING
    } state;
    long stateTimestamp;
    bool justEntered;

    ServoMotor* hangarDoor;
    ProximitySensor* droneDistanceDetector;
    PresenceSensor* dronePresenceDetector;
};

#endif