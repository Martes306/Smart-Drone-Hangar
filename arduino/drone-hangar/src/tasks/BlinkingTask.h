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
  typedef enum
  {
    OFF,
    ON
  } blinkingState;

  void setState(blinkingState state);
  long elapsedTimeInState();
  void log(const String &msg);
  bool checkAndSetJustEntered();

  long stateTimestamp;
  bool justEntered;

  blinkingState state;
  bool *blinking;
  Led *pLed;
};

#endif