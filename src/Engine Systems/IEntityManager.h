#ifndef ENTITYSYSTEMPONG_IENTITYMANAGER_H_
#define ENTITYSYSTEMPONG_IENTITYMANAGER_H_

#include <vector>
#include "../Types.h"

class IComponent;

class IEntityManager {
public:
  virtual IComponent* GetComponent( const int &entity, const ComponentTypes &component_type ) = 0;
  virtual std::vector<IComponent*> GetAllComponentsOfType( const ComponentTypes &component_type ) = 0;
  virtual std::vector<unsigned int> GetAllEntitiesPossessingComponent( const ComponentTypes &component_type ) = 0;
  virtual void AddComponent( const unsigned int &entity, IComponent* component, const bool &replace ) = 0;
  virtual unsigned int CreateEntity() = 0;
  virtual void KillEntity( const unsigned int &entity ) = 0;
  virtual void ResetManager() = 0;
};

#endif//ENTITYSYSTEMPONG_IENTITYMANAGER_H_
