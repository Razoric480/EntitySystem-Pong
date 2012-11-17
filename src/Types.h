//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Header file that holds various useful types that are used throughout the game code.

#ifndef ENTITYSYSTEMPONG_TYPES_H_
#define ENTITYSYSTEMPONG_TYPES_H_

#define NULL 0

//An enum that holds all types of possible components in the system. They are used to call particular
//types of components through entity manager and for instances to identify themselves.
enum ComponentTypes {
  COMP_BALL,
  COMP_PADDLE,
  COMP_BORDER,
  COMP_SCORE,
};

//Vector2 struct, most basic with no helper functions
struct Vector2 {
  float x;
  float y;
};

#endif//ENTITYSYSTEMPONG_TYPES_H_
