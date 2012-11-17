//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Controls the ball component

#ifndef ENTITYSYSTEMPONG_BALLDRIVER_H_
#define ENTITYSYSTEMPONG_BALLDRIVER_H_

#include "IEntitySystem.h"

class Ball;

//See above. Controls the ball.
//Sample usage:
//  BallDriver ball_driver;
//  ...
// while(main_game) { ball_driver.Process(delta_time); }
class BallDriver : IEntitySystem {
public:
  BallDriver();
  ~BallDriver();

  //Moves the ball based on its direction, position and speed
  void Process( const double &dt );

private:
  //friend function
  Ball* ball_; //easy reference pointer
};

#endif//ENTITYSYSTEMPONG_BALLDRIVER_H_
