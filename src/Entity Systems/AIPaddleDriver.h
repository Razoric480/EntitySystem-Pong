//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//System that controls the AI paddle, making it move towards the ball when it's coming its way

#ifndef ENTITYSYSTEMPONG_AIPADDLEDRIVERSYSTEM_H_
#define ENTITYSYSTEMPONG_AIPADDLEDRIVERSYSTEM_H_

#include "IEntitySystem.h"

class Paddle;
class Ball;

//See above. Controls the AI paddle.
//Sample usage:
//  AIPaddleDriver ai_driver;
//  ...
// while(main_game) { ai_driver.Process(delta_time); }
class AIPaddleDriver : IEntitySystem {
public:
  AIPaddleDriver();
  ~AIPaddleDriver();

  //Checks ball position and direction and begins to move towards it if required
  void Process( const double & dt );

private:
  //singleton declaror
  Paddle* ai_paddle_; //pointers to easily reference components that are needed by the system, optional
  Ball* ball_;
};

#endif//ENTITYSYSTEMPONG_AIADDLEDRIVERSYSTEM_H_
