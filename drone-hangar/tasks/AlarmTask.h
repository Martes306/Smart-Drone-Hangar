#ifndef __ALARM_TASK__
#define __ALARM_TASK__

#include "kernel/Task.h"
#include "devices/Button/Button.h"
#include "devices/led/Led.h"

class AlarmTask : public Task
{
public:
    AlarmTask();
    void tick();

private:
    void setState(int state);
    long elapsedTimeInState();
    void log(const String &msg);

    bool checkAndSetJustEntered();

    enum
    {
        NOT_ALARMED,
        PRE_ALARMED,
        ALARMED
    } state;
    long stateTimestamp;
    bool justEntered;

    Button *resetButton;
    Led *l3;
};
#endif