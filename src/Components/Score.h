//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Component that holds the current score for a given entity.

#ifndef ENTITYSYSTEMPONG_SCORE_H_
#define ENTITYSYSTEMPONG_SCORE_H_

#include "IComponent.h"
#include "../Types.h"

//See above for description.
//Sample usage:
//  { Score* score = new Score();
//  entity_manager->addComponent( entity, score ); }
//  Score* score = entity_manager->GetComponent( entity, COMP_SCORE );
class Score : public IComponent {
public:
  //constructor
  Score();

  //Deserializes any pertinent data from an xml_node
  void Deserialize( const pugi::xml_node &node );

  //returns COMP_SCORE
  ComponentTypes type();

  int current_score_;
};

//Creates a score component and returns its pointer
IComponent* CreateScore();

#endif//ENTITYSYSTEMPONG_SCORE_H_
