#ifndef __CONTROL_PANEL_TASK__
#define __CONTROL_PANEL_TASK__

#include "kernel/Task.h"
#include <LiquidCrystal_I2C.h>
#include "devices/led/Led.h"

class ControlPanelTask : public Task
{

public:
    ControlPanelTask();
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

    LiquidCrystal_I2C* lcd;
    Led* l1;
};

#endif