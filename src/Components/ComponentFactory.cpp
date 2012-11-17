#include "ComponentFactory.h"

void ComponentFactory::Register(const string &name, IComponent *(FactoryMethod)() ) {
  name_map_[name] = FactoryMethod;
}

IComponent* ComponentFactory::Create( const string &name ) {
  //we grab the function and use it to create the component. If we can't find it, we return NULL and no component is created.
  map<string, IComponent *(*)()>::iterator it = name_map_.find(name);

  if( it == name_map_.end() ) {
    return NULL;
  }

  return it->second();
}

ComponentFactory::ComponentFactory() {
}

ComponentFactory::~ComponentFactory() {
}