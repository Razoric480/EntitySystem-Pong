#include "Ball.h"

Ball::Ball() : horizontal_direction_(2), vertical_direction_(1), base_speed_(50.0f), active_(true) {
  speed_ = base_speed_;
  position_.x = 50.0f;
  position_.y = 50.0f;
}

ComponentTypes Ball::type() {
  return COMP_BALL;
}

void Ball::Deserialize( const pugi::xml_node &node ) {
}


IComponent* CreateBall() {
  return new Ball();
}