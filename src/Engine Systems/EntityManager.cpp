#include "EntityManager.h"
#include "../Components/IComponent.h"
#include "../Types.h"

EntityManager::EntityManager() : lowest_unassigned_entity_id_(1) {
}

EntityManager::~EntityManager() {
  ResetManager();
}

IComponent* EntityManager::GetComponent( const int &entity, const ComponentTypes &component_type ) {
  //Attempt to find the component type and store it into an iterator
  map<ComponentTypes, map<unsigned int, IComponent*>>::iterator store_it = component_store_.find(component_type);

  //If the iterator is at the end, it wasn't there
  if( store_it == component_store_.end() ) {
    //No such component found in the table at all
    return NULL;
  }

  //Store the located map, and then store in a second iterator the entity ID
  map<unsigned int, IComponent*> store = store_it->second;
  map<unsigned int, IComponent*>::iterator result_it = store.find(entity);

  //If the iterator is at the end, it wasn't there
  if(result_it == store.end()) {
    //Entity does not have that component
    return NULL;
  }

  //Grab the component and return it
  IComponent* result = result_it->second;

  return result;
}

vector<IComponent*> EntityManager::GetAllComponentsOfType( const ComponentTypes &component_type ) {
  //empty vector of components to return
  vector<IComponent*> components;
  //try to locate the component type map and store its position in the iterator
  map<ComponentTypes, map<unsigned int, IComponent*>>::iterator store_it = component_store_.find(component_type);
  
  if( store_it == component_store_.end() ) {
    //no such components, so we just return the empty vector.
    return components;
  }

  //Grab the map and begin to iterate through it
  map<unsigned int, IComponent*> store = store_it->second;
  map<unsigned int, IComponent*>::iterator it = store.begin();
  
  //We store each entry in there and then return the resulting filled vector
  for(; it != store.end(); it++) {
    components.push_back( it->second );
  }

  return components;
}

vector<unsigned int> EntityManager::GetAllEntitiesPossessingComponent( const ComponentTypes &component_type ) {
  vector<unsigned int> entities;
  
  //attempt to grab the iterator map of the right type
  map<ComponentTypes, map<unsigned int, IComponent*>>::iterator store_it = component_store_.find(component_type);
  
  if( store_it == component_store_.end() ) {
    //no such component type, so we return the empty vector
    return entities;
  }
  
  //iterate through the result, and fill the vector with the keys (entities) instead of values
  map<unsigned int, IComponent*> store = store_it->second;
  map<unsigned int, IComponent*>::iterator it = store.begin();
  
  for(; it != store.end(); it++ ) {
    entities.push_back( it->first );
  }

  //return resulting vector
  return entities;
}

void EntityManager::AddComponent( const unsigned int &entity, IComponent *component, const bool &replace ) {
  //try to find if a particular component type already exists
  map<ComponentTypes, map<unsigned int, IComponent*>>::iterator store_it = component_store_.find(component->type());

  //if it does not, we assign a spot in the map for it
  if( store_it == component_store_.end() ) {
    component_store_[component->type()] = map<unsigned int, IComponent*>();  
    
  }
  else {
    //if it already exists, we check if the component is already there
    map<unsigned int, IComponent*>::iterator result_it = store_it->second.find( entity );

    //if it already exists, and we choose not to replace, then do nothing (default)
    if( result_it != store_it->second.end() ) {
      if( !replace ) {
        return;
      }
    }
  }

  //store the component with the entity key
  component_store_[component->type()][entity] = component;
}

unsigned int EntityManager::CreateEntity() {
  //lock guard
  std::lock_guard<std::mutex> _(CreateEntityMutex());

  int new_id = GenerateNewEntityID();

  //if the new id is an error
  if( new_id < 1 ) {
    return 0;
  }

  //add the new id and return it
  all_entities_.insert(new_id);

  return new_id;
}

std::mutex& EntityManager::CreateEntityMutex() {
  static std::mutex m;
  return m;
}

void EntityManager::KillEntity( const unsigned int &entity ) {
  //remove an entry from the entity set
  all_entities_.erase(entity);
}

std::mutex& EntityManager::GenerateNewEntityIDMutex() {
  static std::mutex m;
  return m;
}

int EntityManager::GenerateNewEntityID() {
  //lock guard
  std::lock_guard<std::mutex> _(GenerateNewEntityIDMutex());

  //if the lowest id is less than the max for unsigned integers, return the current one then increment it
  if( lowest_unassigned_entity_id_ < UINT_MAX ) {
    return lowest_unassigned_entity_id_++;
  }
  
  //otherwise, run through the current entities list and find one that does not exist
  for( int i=1; i< UINT_MAX; i++ ) {
    if( all_entities_.find(i) == all_entities_.end() ) {
      return i;
    }
  }

  //error. too many entities!
  return 0;
}

void EntityManager::ResetManager() {
  //iterate through the first map
  map<ComponentTypes, map<unsigned int, IComponent*>>::iterator it = component_store_.begin();

  //and for each nested map, iterate through them and delete their components
  for(; it != component_store_.end(); it++ ) {
    map<unsigned int, IComponent*> nested = it->second;
    map<unsigned int, IComponent*>::iterator nested_it = nested.begin();

    for(; nested_it != nested.begin(); nested_it++ ) {
      KillEntity(nested_it->first);
      if(nested_it->second) {
        delete nested_it->second;
        nested_it->second = 0;
      }
    }
  }
  //clear the main map
  component_store_.clear();

  //clear entities
  all_entities_.clear();
  //reset lowest ID
  lowest_unassigned_entity_id_ = 1;
}