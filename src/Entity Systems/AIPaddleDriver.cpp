#include "AIPaddleDriver.h"
#include "../Components/Ball.h"
#include "../Components/Paddle.h"
#include <vector>
#include "../Engine Systems/ServiceLocator.h"
#include "../Engine Systems/IEntityManager.h"

using std::vector;

AIPaddleDriver::AIPaddleDriver() : ball_(NULL), ai_paddle_(NULL) {
}

AIPaddleDriver::~AIPaddleDriver() {
}

void AIPaddleDriver::Process( const double & dt ) {

  if( !ball_ ) {
      IEntityManager *manager = ServiceLocator::GetEntityManager();

    //get ball component
    vector<unsigned int> entities = manager->GetAllEntitiesPossessingComponent(COMP_BALL);

    if(entities.size() != 0 ) {
      ball_ = dynamic_cast<Ball*>(manager->GetComponent( entities[0], COMP_BALL ));
    }
    else {
      return;
    }
  }
  if( !ai_paddle_ ) {
    IEntityManager *manager = ServiceLocator::GetEntityManager();

    //get paddle component
    vector<IComponent*> components = manager->GetAllComponentsOfType(COMP_PADDLE);

    if(components.size() != 0 ) {
      if( ((Paddle*)components[0])->player_controlled_ ) {
        ai_paddle_ = dynamic_cast<Paddle*>(components[1]);
      }
      else {
        ai_paddle_ = dynamic_cast<Paddle*>(components[0]);
      }
    }
    else {
      return;
    }
  }
  //check ball direction
  //if going right
  if( ball_->horizontal_direction_ == 2 ) {
    //try to match Y
    if( ai_paddle_->position_.y < ball_->position_.y ) {
      ai_paddle_->position_.y += (float)( ai_paddle_->speed_ * dt );
    }
    if( ai_paddle_->position_.y >= ball_->position_.y ) {
      ai_paddle_->position_.y -= (float)( ai_paddle_->speed_ * dt );
    }

    //clamp
    if( ai_paddle_->position_.y <= ai_paddle_->height_ ) {
      ai_paddle_->position_.y = (float)ai_paddle_->height_;
    }

    //TODO: remove hard coded values
    if( ai_paddle_->position_.y >= 100-ai_paddle_->height_ ) {
      ai_paddle_->position_.y = 100.0f-(float)ai_paddle_->height_;
    }
  }
}

