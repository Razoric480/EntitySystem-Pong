//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Has a hand in all components. It checks to make the ball bounce off of paddles and bounce or score on the borders

#ifndef ENTITYSYSTEMPONG_COLLISION_H_
#define ENTITYSYSTEMPONG_COLLISION_H_

#include "IEntitySystem.h"

class Ball;
class Border;
class Paddle;

//See above. Checks for collisions between components and modifies score.
//Sample usage:
//  Collision collision;
//  ...
// while(main_game) { collision.Process(delta_time); }
class Collision : IEntitySystem {
public:
  //Checks the movement of the ball, position of paddles and borders, and bounces the ball accordingly of scores
  void Process( const double &dt );

private:
  //Helper function. Sets the direction of the ball, and optionally makes it accelerate.
  void BounceBall( int intended_h_direction, int intended_v_direction, const bool &accelerate, Ball* ball );
  bool CheckPaddle( Ball* ball, Paddle* paddle ); //Checks whether the ball has hit the paddle. Calls bounceball
  bool CheckBorder( Ball* ball, Border* border ); //Checks whether the ball has hit a border. Balls bounceball and scores appropriately
};

#endif//ENTITYSYSTEMPONG_COLLISION_H_
