//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//EntityManager holds entities and their components in a hash map. It is a singleton with global access used by EntitySystems to update components.

#ifndef ENTITYSYSTEMPONG_ENTITYMANAGER_H_
#define ENTITYSYSTEMPONG_ENTITYMANAGER_H_

#include "IEntityManager.h"
#include <vector>
#include <map>
#include "../Types.h"
#include <set>

using std::vector;
using std::set;
using std::map;

class IComponent;

//EntityManager holds entities and components with helper functions to access specific components. Entities are unique non-negative IDs associated with a number of components.
//Sample usage:
//  EntityManager manager;
//  ServiceLocator::ProvideEntityManager(&manager);
//  unsigned int entity = manager.CreateEntity();
//  manager.AddComponent( entity, new NewComponent() );
//  NewComponent *comp = dynamic_cast<NewComponent*>( manager.GetComponent( entity, SPECIFIC_TYPE_COMPONENT ) );
class EntityManager : public IEntityManager {
public:
  EntityManager();
  ~EntityManager();

  //Gets a given component pointer from a given entity. Returns as the base type IComponent that can be casted appropriately.
  //Returns NULL if no entities have such a component or if the given entity does not have that component type.
  IComponent* GetComponent( const int &entity, const ComponentTypes &component_type );
  //Returns a vector of pointers of all components of a given type.
  vector<IComponent*> GetAllComponentsOfType( const ComponentTypes &component_type );
  //Returns a vector of entity IDs of a given component type.
  vector<unsigned int> GetAllEntitiesPossessingComponent( const ComponentTypes &component_type );
  //Adds the given component to the entity. The replace bool indicates whether to replace the existing component, if one of that type is already assigned to that entity.
  //WARNING: If choosing to replace with a new entity, this will not clean up the already existing component.
  void AddComponent( const unsigned int &entity, IComponent *component, const bool &replace = false );
  //Creates a new, unique entity
  unsigned int CreateEntity();
  //Removes a given entity from the entities list, freeing its ID for re-use.
  void KillEntity( const unsigned int &entity );
  //Destroys all components and frees all entities, bringing the manager back to its standard state.
  void ResetManager();

private:

  //Generates a unique entity non-negative ID.
  int GenerateNewEntityID();

  unsigned int lowest_unassigned_entity_id_; //lowest current unassigned ID
  set<unsigned int> all_entities_; //list of all the current entity IDs
  map<ComponentTypes, map<unsigned int, IComponent*>> component_store_; //map of components assigned to entities
};

#endif//ENTITYSYSTEMPONG_ENTITYMANAGER_H_
