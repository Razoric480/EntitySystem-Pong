#ifndef ENTITYSYSTEMPONG_SERVICELOCATOR_H_
#define ENTITYSYSTEMPONG_SERVICELOCATOR_H_

#include "nullEntityManager.h"

class IEntityManager;

class ServiceLocator {
public:
  static void Initialize();

  static IEntityManager* GetEntityManager();

  static void ProvideEntityManager(IEntityManager* manager);

private:
  static IEntityManager* entity_manager_;
  static nullEntityManager null_entity_manager_;
};

#endif//ENTITYSYSTEMPONG_SERVICELOCATOR_H_
