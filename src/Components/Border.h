//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Border is a component and holds pertinent information to determine orientation, facing and position

#ifndef ENTITYSYSTEMPONG_BORDER_H_
#define ENTITYSYSTEMPONG_BORDER_H_

#include "IComponent.h"
#include "../Types.h"

//See above for description.
//Sample usage:
//  { Border* border = new Border();
//  entity_manager->addComponent( entity, border ); }
//  Border* border = entity_manager->GetComponent( entity, COMP_BORDER );
class Border : public IComponent {
public:
  //Constructor that initializes the object with given data right away.
  Border( Vector2 position, const bool &horizontal, const int &facing  );
  //Empty constructor that uses default data.
  Border();

  //returns COMP_BORDER
  ComponentTypes type();
  
  //Uses any pertinent XML data from the xml_node.
  void Deserialize( const pugi::xml_node &node );

  bool horizontal_; //True for horizontal border (bounces ball), false for vertical (scores)
  int facing_; //1 for up/right, 2 for down/left
  Vector2 position_; //x,y floating point position.
  //Uses only one value from it depending on type, x for vertical and y for horizontal. implied to be infinte length/height
};

//Factory method that creates a border and returns its pointer.
IComponent* CreateBorder();

#endif//ENTITYSYSTEMPONG_BORDER_H_
