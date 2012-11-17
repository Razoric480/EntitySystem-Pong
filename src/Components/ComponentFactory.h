//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Object that creates components by given string name using factory methods. This is used to be able to deserialize from raw files instead of hard coding.

#ifndef ENTITYSYSTEMPONG_COMPONENTFACTORY_H_
#define ENTITYSYSTEMPONG_COMPONENTFACTORY_H_

#include <map>
#include <string>

using std::string;
using std::map;

class IComponent;

//Sample usage:
//ComponentFactory factory;
//factory.Register( "Ball", CreateBall );
//...
//IComponent* ball = factory.Create("Ball");
class ComponentFactory {
public:
  ComponentFactory();
  ~ComponentFactory();

  //Registers a function pointer with the return type IComponent* with no arguments to the map of functions and keys it to that given name
  void Register(const string &name, IComponent *(FactoryMethod)() );
  //Calls the given function using the given name, if it exists. If it does not, returns NULL
  IComponent* Create( const string &name );

private:
  //Map of name, factory functions
  map<string, IComponent *(*)()> name_map_;
};

#endif//ENTITYSYSTEMPONG_COMPONENTFACTORY_H_
