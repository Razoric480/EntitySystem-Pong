////© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Paddle holds information about player and AI paddle, including speed, position and whether it's under control by the player or AI

#ifndef ENTITYSYSTEMPONG_PADDLE_H_
#define ENTITYSYSTEMPONG_PADDLE_H_

#include "IComponent.h"
#include "../Types.h"

//See above for description.
//Sample usage:
//  { Paddle* paddle = new Paddle();
//  entity_manager->addComponent( entity, paddle ); }
//  Paddle* paddle = entity_manager->GetComponent( entity, COMP_PADDLE );
class Paddle : public IComponent {
public:
  //constructors
  Paddle( const bool &player_controlled );
  Paddle();

  //Uses the xml_node to get pertinent XML data
  void Deserialize( const pugi::xml_node &node );

  //Returns COMP_PADDLE
  ComponentTypes type();

  Vector2 position_; //floating point position for paddle position
  float speed_; //speed the paddle can move up or down
  bool player_controlled_; //true for controlled by player input, false for use on AI
  unsigned int height_; //height of the paddle
};

//Factory method that creates a paddle and returns an IComponent pointer
IComponent* CreatePaddle();

#endif//ENTITYSYSTEMPONG_PADDLE_H_
