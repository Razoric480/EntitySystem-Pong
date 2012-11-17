#include "Score.h"

Score::Score() : current_score_(0) {
}

ComponentTypes Score::type() {
  return COMP_SCORE;
}

void Score::Deserialize( const pugi::xml_node &node ) {
}

IComponent* CreateScore() {
  return new Score();
}