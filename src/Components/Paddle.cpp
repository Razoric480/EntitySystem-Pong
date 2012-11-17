#include "Paddle.h"

Paddle::Paddle( const bool &player_controlled ) : speed_(50.0f), player_controlled_(player_controlled), height_(4) {
  if( player_controlled_ ) {
    position_.x = 5.0f;
    position_.y = 50.0f;
  }
  else {
    position_.x = 95.0f;
    position_.y = 50.0f;
  }
}

Paddle::Paddle() : speed_(50.0f), player_controlled_(false), height_(4) {
  position_.x = 0.0f;
  position_.y = 0.0f;
}

ComponentTypes Paddle::type() {
  return COMP_PADDLE;
}

void Paddle::Deserialize( const pugi::xml_node &node ) {
  //we grab the XML attributes out of the xml node and store them appropriately
  bool player_controlled = node.attribute("player_controlled").as_bool();
  player_controlled_ = player_controlled;

  if( player_controlled_ ) {
    position_.x = 5.0f;
    position_.y = 50.0f;
  }
  else {
    position_.x = 95.0f;
    position_.y = 50.0f;
  }
}

IComponent* CreatePaddle() {
  return new Paddle();
}