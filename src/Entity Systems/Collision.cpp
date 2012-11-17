#include "Collision.h"
#include <vector>
#include "../Types.h"
#include "../Components/Ball.h"
#include "../Components/Paddle.h"
#include "../Components/Score.h"
#include "../Components/Border.h"
#include "../Engine Systems/ServiceLocator.h"
#include "../Engine Systems/IEntityManager.h"

using std::vector;

void Collision::Process(const double &dt ) {
  IEntityManager *manager = ServiceLocator::GetEntityManager();

  //get all borders
  vector<IComponent*> borders = manager->GetAllComponentsOfType( COMP_BORDER );
  //get ball
  vector<IComponent*> vball = manager->GetAllComponentsOfType( COMP_BALL );
  //get paddles
  vector<IComponent*> paddles = manager->GetAllComponentsOfType( COMP_PADDLE );

  //no ball, no game
  if(vball.size() == 0 ) {
    return;
  }

  Ball *ball = dynamic_cast<Ball*>(vball[0]);

  //ball not active, no game
  if( !ball->active_ ) {
    return;
  }

  for( unsigned int i=0; i<paddles.size(); ++i) {
    if( CheckPaddle( ball, dynamic_cast<Paddle*>(paddles[i])) ) {
      //we had a bounce, return to not have to check redundent bounces
      return;
    }
  }

  //check borders
  for(unsigned int i=0; i<borders.size(); i++) {
    if( CheckBorder( ball, dynamic_cast<Border*>(borders[i])) ) {
      return;
    }
  }
}

void Collision::BounceBall( int intended_h_direction, int intended_v_direction, const bool &accelerate, Ball* ball ) {
  ball->horizontal_direction_ = intended_h_direction;
  ball->vertical_direction_ = intended_v_direction;
  if( accelerate ) {
    //TODO: remove hard coded value
    ball->speed_ += 4.0f;
  }
}

bool Collision::CheckPaddle( Ball* ball, Paddle* paddle ) {
  Vector2 pos = ball->position_;
  Vector2 ppos = paddle->position_;

  if( pos.x >= ppos.x - 1 && pos.x <= ppos.x + 1 ) {
    //ball is in the same zone as paddle 0, so check if it's within it
    if( pos.y >= ppos.y-paddle->height_ && pos.y <= ppos.y+paddle->height_ ) {
      //if so, we found a match. make ball bounce in opposite horizontal direction
      if( paddle->player_controlled_ ) {
        BounceBall( 2, ball->vertical_direction_, true, ball );
      }
      else {
        BounceBall( 1, ball->vertical_direction_, true, ball );
      }
      return true;
    }
  }

  return false;
}

bool Collision::CheckBorder( Ball* ball, Border* border ) {
  Vector2 pos = ball->position_;
  Vector2 bpos = border->position_;

  if( border->horizontal_ ) {
    if( border->facing_ == 1 ) {
      if( pos.y <= bpos.y ) {
        BounceBall( ball->horizontal_direction_, 1, false, ball );
        return true;
      }
    }
    else {
      if( pos.y >= bpos.y ) {
        BounceBall( ball->horizontal_direction_, 2, false, ball );
        return true;
      }
    }
  }
  //scoring side
  else {
    IEntityManager *manager = ServiceLocator::GetEntityManager();

    vector<unsigned int> entities = manager->GetAllEntitiesPossessingComponent( COMP_SCORE );
    int new_direction = 0;
    bool bouncing = false;
    int scoring_entity = 0;

    if( border->facing_ == 1 ) {
      if( pos.x >= bpos.x ) {
        bouncing = true;
        new_direction = 2;

        //get score for player
        if( entities.size() != 0 ) {
          Paddle* paddle = dynamic_cast<Paddle*>(manager->GetComponent( entities[0], COMP_PADDLE ));
          if( paddle ) {
            if( paddle->player_controlled_ ) {
              scoring_entity = entities[0];
            }
            else {
              scoring_entity = entities[1];
            }
          }
        }
      }
    }
    else {
      if( pos.x <= bpos.x ) {
        bouncing = true;
        new_direction = 1;

        //get score for AI
        if( entities.size() != 0 ) {

          Paddle* paddle = dynamic_cast<Paddle*>(manager->GetComponent( entities[0], COMP_PADDLE ));
          if(paddle) {
            if( paddle->player_controlled_ ) {
              scoring_entity = entities[1];
            }
            else {
              scoring_entity = entities[0];
            }
          }
        }
      }
    }

    if( bouncing ) {
      if( scoring_entity != 0 ) {
        Score* score = dynamic_cast<Score*>(manager->GetComponent( scoring_entity, COMP_SCORE ) );
        if( score ) {
          ++score->current_score_;
        }
      }
      ball->active_ = false;
      BounceBall( new_direction, ball->vertical_direction_, false, ball );

      return true;
    }
  }

  return false;
}