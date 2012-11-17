#include "Border.h"

Border::Border( Vector2 position, const bool &horizontal, const int &facing ) : horizontal_(horizontal), position_(position), facing_(facing) {
}

Border::Border() : horizontal_(false), facing_(1) {
  position_.x = 0.0f;
  position_.y = 0.0f;
}

ComponentTypes Border::type() {
  return COMP_BORDER;
}

void Border::Deserialize( const pugi::xml_node &node ) {
  //we extract the necessary information out of the xml node and then store it in the object
  int facing = node.attribute("facing").as_int();
  bool horizontal = node.attribute("horizontal").as_bool();

  pugi::xml_node position = node.child("position");

  float x = position.attribute("x").as_float();
  float y = position.attribute("y").as_float();

  facing_ = facing;
  horizontal_ = horizontal;
  position_.x = x;
  position_.y = y;
}


IComponent* CreateBorder() {
  return new Border();
}