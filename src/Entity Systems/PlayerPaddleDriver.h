//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Checks the input map and controls the player paddle accordingly

#ifndef ENTITYSYSTEMPONG_PLAYERPADDLEDRIVERSYSTEM_H_
#define ENTITYSYSTEMPONG_PLAYERPADDLEDRIVERSYSTEM_H_

#include "IEntitySystem.h"

class Paddle;

//See above. Controls the player paddle.
//Sample usage:
//  PlayerPaddleDriver player_driver;
//  ...
// while(main_game) { player_driver.Process(delta_time); }
class PlayerPaddleDriver : IEntitySystem {
public:
  PlayerPaddleDriver();
  ~PlayerPaddleDriver();

  //Checks the input map and moves by the paddle speed appropriately
  void Process( const double & dt );

private:
  Paddle* paddle_;
};

#endif//ENTITYSYSTEMPONG_PLAYERPADDLEDRIVERSYSTEM_H_
