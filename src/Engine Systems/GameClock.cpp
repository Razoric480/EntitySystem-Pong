#include "GameClock.h"
#include <Windows.h>

GameClock::GameClock() : start_time_(0.0), end_time_(0.0), delta_time_(0.0), total_time_(0.0) {
  timeBeginPeriod(1);
}

GameClock::~GameClock() {
  timeEndPeriod(1);
}

void GameClock::StartFrame() {
  start_time_ = timeGetTime();
}

void GameClock::EndFrame() {
  end_time_ = timeGetTime();

  delta_time_ = ( end_time_ - start_time_ ) / 1000.0;

  total_time_ += delta_time_;

  if(delta_time_ > 1.0) {
    delta_time_ = 1.0;
  }
}

double GameClock::delta_time() {
  return delta_time_;
}

double GameClock::total_time() {
  return total_time_;
}