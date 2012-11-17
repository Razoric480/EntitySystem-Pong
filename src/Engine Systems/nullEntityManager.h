//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Implementation of IEntityManager that does nothing. Note that this could still cause issues due to return values.

#ifndef TPYEINFOTEST_NULLENTITYMANAGER_H_
#define TPYEINFOTEST_NULLENTITYMANAGER_H_

#include "IEntityManager.h"

class nullEntityManager : public IEntityManager {
public:
  IComponent* GetComponent( const int &entity, const ComponentTypes &component_type ) { return NULL; }
  std::vector<IComponent*> GetAllComponentsOfType( const ComponentTypes &component_type ) { return std::vector<IComponent*>(); }
  std::vector<unsigned int> GetAllEntitiesPossessingComponent( const ComponentTypes &component_type ) { return std::vector<unsigned int>(); }
  void AddComponent( const unsigned int &entity, IComponent* component, const bool &replace ) {}
  unsigned int CreateEntity() { return 0; }
  void KillEntity( const unsigned int &entity ) {}
  void ResetManager() {}
};

#endif//TPYEINFOTEST_NULLENTITYMANAGER_H_