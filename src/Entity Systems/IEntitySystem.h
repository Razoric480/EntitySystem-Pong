//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Base interface to derive systems from. All systems have a process function that is called.

#ifndef ENTITYSYSTEMPONG_IENTITYSYSTEM_H_
#define ENTITYSYSTEMPONG_IENTITYSYSTEM_H_

class IEntitySystem {
public:
  virtual ~IEntitySystem() {}

  virtual void Process( const double &dt ) = 0;
};

#endif//ENTITYSYSTEMPONG_IENTITYSYSTEM_H_
