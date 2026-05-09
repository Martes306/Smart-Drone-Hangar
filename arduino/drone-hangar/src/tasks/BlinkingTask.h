#ifndef __BLINKING_TASK__
#define __BLINKING_TASK__

#include "kernel/Task.h"
#include "devices/led/Led.h"
#include <Arduino.h>

class BlinkingTask : public Task
{

public:
  BlinkingTask(Led *pLed, bool *blinking);
  void tick();

private:
  void setState(int state);
  long elapsedTimeInState();
  void log(const String &msg);

  bool checkAndSetJustEntered();

  enum
  {
    OFF,
    ON
  } state;
  long stateTimestamp;
  bool justEntered;

  bool *blinking;
  Led *pLed;
};

#endif