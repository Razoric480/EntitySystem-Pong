//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Uses the winmm.dll timeGetTime method with a 1 millisecond precision setting to calculate delta time at the beginning and end of each frame.

#ifndef ENTITYSYSTEMPONG_GAMECLOCK_H_
#define ENTITYSYSTEMPONG_GAMECLOCK_H_

class GameClock {
public:
  GameClock();
  ~GameClock();

  void StartFrame();
  void EndFrame();

  double delta_time();
  double total_time();

private:
  double total_time_;
  double delta_time_;
  double start_time_;
  double end_time_;
};

#endif//ENTITYSYSTEMPONG_GAMECLOCK_H_
