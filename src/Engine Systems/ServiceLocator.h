//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Service locator holds certain services that are meant to be globally accessed without making them into a singleton.
//The advantage is that we can decide how the instance is accessed and only provide the interface.

#ifndef ENTITYSYSTEMPONG_SERVICELOCATOR_H_
#define ENTITYSYSTEMPONG_SERVICELOCATOR_H_

#include "nullEntityManager.h"

class IEntityManager;

//Sample usage:
//  ServiceLocator::Initialize();
//  //Without a manager being injected, we will get an instance of nullEntityManager
//  IEntityManager *null_manager = ServiceLocator::GetEntityManager(); //nullEntityManager instance
//  EntityManager manager;  
//  ServiceLocator::ProvideEntityManager(&manager);
//  IEntityManager *actual_manager = ServiceLocator::GetEntityManager(); //EntityManager instance
class ServiceLocator {
public:
  //Initializes the services to initial versions, typically null-do-nothing types
  static void Initialize();

  //Gets an IEntityManager
  static IEntityManager* GetEntityManager();

  //Dependency inject an entity manager
  static void ProvideEntityManager(IEntityManager* manager);

private:
  static IEntityManager* entity_manager_;
  static nullEntityManager null_entity_manager_;
};

#endif//ENTITYSYSTEMPONG_SERVICELOCATOR_H_
