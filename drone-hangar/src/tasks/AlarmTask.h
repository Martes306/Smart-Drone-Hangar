#ifndef __ALARM_TASK__
#define __ALARM_TASK__

#include "kernel/Task.h"
#include "devices/Button/ButtonImpl.h"
#include "devices/led/Led.h"
#include "config.h"

class AlarmTask : public Task
{
public:
    AlarmTask(alarm_state *alarmState);
    void tick();

private:
    typedef enum
    {
        NOT_ALARMED,
        PRE_ALARMED,
        ALARMED
    } alarmState;

    void setState(alarmState state);
    long elapsedTimeInState();
    void log(const String &msg);
    bool checkAndSetJustEntered();

    long stateTimestamp;
    bool justEntered;

    
    alarmState state;
    alarm_state *alarmStateExternal;
    ButtonImpl *resetButton;
    Led *l3;
};
#endif