#include "BallDriver.h"
#include "../Components/Ball.h"
#include "../Types.h"
#include <vector>
#include <map>
#include <windows.h>
#include "../Components/Score.h"
#include "../Engine Systems/ServiceLocator.h"
#include "../Engine Systems/IEntityManager.h"

using std::map;
using std::vector;

extern map<unsigned char, bool> g_input_map;

BallDriver::BallDriver() : ball_(NULL) {
}

BallDriver::~BallDriver() {
}

void BallDriver::Process( const double &dt ) {
  if( !ball_ ) {
    IEntityManager *manager = ServiceLocator::GetEntityManager();

    vector<IComponent*> components = manager->GetAllComponentsOfType(COMP_BALL);

    if(components.size() != 0 ) {
      ball_ = dynamic_cast<Ball*>(components[0]);
    }
    else {
      return;
    }
  }

  if( !ball_->active_ ) {
    IEntityManager *manager = ServiceLocator::GetEntityManager();

    if( g_input_map[VK_SPACE] ) {
      ball_->position_.x = 50.0f;
      ball_->position_.y = 50.0f;
      ball_->speed_ = ball_->base_speed_;
      ball_->active_ = true;

      //reset scores
      vector<IComponent*> scores = manager->GetAllComponentsOfType( COMP_SCORE );

      bool reset_scores = false;

      for( unsigned int i=0; i<scores.size(); i++ ) {
        Score* score = dynamic_cast<Score*>(scores[i]);
        if(score->current_score_ == 9 ) {
          reset_scores = true;
          break;
        }
      }

      if(reset_scores ) {
        for( unsigned int i=0; i<scores.size(); i++ ) {
          Score* score = dynamic_cast<Score*>(scores[i]);
          score->current_score_ = 0;
        }
      }
    }
    return;
  }

  float distance_h = (float)( (ball_->speed_/2) * dt );
  float distance_v = distance_h;

  if( ball_->horizontal_direction_ == 1 ) {
    distance_h *= -1.0f;
  }
  if( ball_->vertical_direction_ == 2 ) {
    distance_v *= -1.0f;
  }

  ball_->position_.x += distance_h;
  ball_->position_.y += distance_v;

}