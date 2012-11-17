#include "ComponentFactory.h"

void ComponentFactory::Register(const string &name, IComponent *(FactoryMethod)() ) {
  name_map_[name] = FactoryMethod;
}

IComponent* ComponentFactory::Create( const string &name ) {
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