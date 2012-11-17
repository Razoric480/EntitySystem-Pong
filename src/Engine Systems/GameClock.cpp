#include "GameClock.h"
#include <Windows.h>

GameClock::GameClock() : start_time_(0.0), end_time_(0.0), delta_time_(0.0) {
  //sets the precision to milliseconds
  timeBeginPeriod(1);
}

GameClock::~GameClock() {
  //resets the precision
  timeEndPeriod(1);
}

void GameClock::StartFrame() {
  //gets the time for the start of the frame
  start_time_ = timeGetTime();
}

void GameClock::EndFrame() {
  //gets the end time and calculate our delta time. since we get total milliseconds, we divide by 1000 to get our seconds-based delta.
  end_time_ = timeGetTime();

  delta_time_ = ( end_time_ - start_time_ ) / 1000.0;

  //clamp to 1 second, otherwise debugging could be a nightmare as the delta jumps to 20+ seconds
  if(delta_time_ > 1.0) {
    delta_time_ = 1.0;
  }
}

double GameClock::delta_time() {
  return delta_time_;
}