//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Ball component holds information pertinent to the pong ball as a component, including position, speed and direction.

#ifndef ENTITYSYSTEMPONG_BALL_H_
#define ENTITYSYSTEMPONG_BALL_H_

#include "IComponent.h"
#include "../Types.h"

//See above for description.
//Sample usage:
//  { Ball* ball = new Ball();
//  entity_manager->addComponent( entity, ball ); }
//  Ball* ball = entity_manager->GetComponent( entity, COMP_BALL );
class Ball : public IComponent {
public:
  Ball();

  //Returns COMP_BALL
  ComponentTypes type();

  //Deserializes pertinent XML data, if any, that might be stored for the component to be initialized with uniquely. Takes a pugi::xml_node.
  void Deserialize( const pugi::xml_node &node );

  unsigned short horizontal_direction_; //1 for left, 2 for right
  unsigned short vertical_direction_; //1 for up, 2 for down
  Vector2 position_; //float x y for position
  float speed_; //speed the ball moves. Note that this is split into two and used for two directions
  float base_speed_; //The base speed when the ball is to be re-initialized
  bool active_; //Whether the ball is active or not
};

//Factory method that creates a new ball and returns its pointer
IComponent* CreateBall();

#endif//ENTITYSYSTEMPONG_BALL_H_
