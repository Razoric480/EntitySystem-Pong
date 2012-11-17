//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Uses the winmm.dll timeGetTime method with a 1 millisecond precision setting to calculate delta time at the beginning and end of each frame.

#ifndef ENTITYSYSTEMPONG_GAMECLOCK_H_
#define ENTITYSYSTEMPONG_GAMECLOCK_H_

//Sample usage:
//  GameClock clock;
//  while(g_app_is_running) {
//    clock.StartFrame();
//    MyThing.Update( clock.delta_time() );
//    clock.EndFrame();
//  }
class GameClock {
public:
  //Sets the timeGetTime precision to 1 millisecond
  GameClock();
  //Resets the timeGetTime precision
  ~GameClock();

  //Sets the start time to the current time
  void StartFrame();
  //Sets the end time and calculates our delta time
  void EndFrame();

  //Gets the delta time as of this frame
  double delta_time();

private:
  double delta_time_; //Time since the last update
  double start_time_; //Time at start of frame
  double end_time_; //Time at end of frame
};

#endif//ENTITYSYSTEMPONG_GAMECLOCK_H_
