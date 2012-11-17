#include "PlayerPaddleDriver.h"
#include <map>
#include <Windows.h>
#include "../Components/Paddle.h"
#include "../Engine Systems/ServiceLocator.h"
#include "../Engine Systems/IEntityManager.h"
#include <vector>

using std::map;
using std::vector;

extern map<unsigned char, bool> g_input_map;

PlayerPaddleDriver::PlayerPaddleDriver() : paddle_(NULL) {
}

PlayerPaddleDriver::~PlayerPaddleDriver() {
}

void PlayerPaddleDriver::Process( const double & dt ) {
  if( paddle_ == NULL ) {

    vector<IComponent*> paddles = ServiceLocator::GetEntityManager()->GetAllComponentsOfType( COMP_PADDLE );

    if( paddles.size() == 0 ) {
      return;
    }

    if( ((Paddle*)paddles[0])->player_controlled_ ) {
      paddle_ = dynamic_cast<Paddle*>(paddles[0]);
    }
    else {
      paddle_ = dynamic_cast<Paddle*>(paddles[1]);
    }

  }

  if( g_input_map[VK_UP] ) {
    //get player paddle component and move up
    paddle_->position_.y -= (float)(paddle_->speed_ * dt );

    if( paddle_->position_.y <= paddle_->height_ ) {
      paddle_->position_.y = (float)paddle_->height_;
    }
  }
  if( g_input_map[VK_DOWN] ) {
    //get player paddle component and move down

    paddle_->position_.y += (float)(paddle_->speed_ * dt);

    if( paddle_->position_.y >= 100-paddle_->height_ ) {
      paddle_->position_.y = 100.0f-(float)paddle_->height_;
    }
  }
}

