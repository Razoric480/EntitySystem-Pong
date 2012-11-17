//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Abstract interface to derive components from. Each component should know how to deserialize themselves from a pugi xml node and return their type as an ENUM

#ifndef ENTITYSYSTEMPONG_ICOMPONENT_H_
#define ENTITYSYSTEMPONG_ICOMPONENT_H_

#include "../Types.h"
#include <pugixml\pugixml.hpp>

class IComponent {
public:
  virtual ~IComponent() {}

  //Implemented and returns its type
  virtual ComponentTypes type() = 0;

  //Deserializes itself according to the contents of a xml_node
  virtual void Deserialize( const pugi::xml_node &node ) = 0;
};

#endif//ENTITYSYSTEMPONG_ICOMPONENT_H_
