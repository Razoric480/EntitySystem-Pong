#include <iostream>
#include "Engine Systems/EntityManager.h"
#include "Types.h"
#include <vector>
#include "Components/Ball.h"
#include "Components/Paddle.h"
#include "Engine Systems/ConsoleHandler.h"
#include "Components/Border.h"
#include "Entity Systems/AIPaddleDriver.h"
#include "Entity Systems/PlayerPaddleDriver.h"
#include "Entity Systems/Collision.h"
#include "Entity Systems/BallDriver.h"
#include <map>
#include "Engine Systems/GameClock.h"
#include "Components/Score.h"
#include <fstream>
#include <sstream>
#include <pugixml\pugixml.hpp>
#include "Components/ComponentFactory.h"
#include "Engine Systems/ServiceLocator.h"

using namespace std;

void ConsoleProc( INPUT_RECORD *record );

void Draw( ConsoleHandler* console );

bool g_app_running = true;

map<unsigned char, bool> g_input_map;

const string LOCAL_DATA = "../data/";

void RegisterFactories(ComponentFactory *factory) {
  //register our factory methods, which are located with the respective component. This will allow us to use XML to parse by name.
  factory->Register( "Ball", CreateBall );
  factory->Register( "Score", CreateScore );
  factory->Register( "Paddle", CreatePaddle );
  factory->Register( "Border", CreateBorder );
}

int main() {

  ServiceLocator::Initialize();

  ComponentFactory factory;
  RegisterFactories(&factory);

  ConsoleHandler console(80, 50, "Pong", ConsoleProc );
  GameClock clock;

  EntityManager manager;
  ServiceLocator::ProvideEntityManager(&manager);

  //Deprecated code in favour of using XML to automate generation of entities.
  /*
  //one ball
  unsigned int ball = manager->CreateEntity();
  manager.AddComponent( ball, new Ball() );

  //two paddles
  unsigned int player = manager.CreateEntity();
  manager.AddComponent( player, new Paddle(true) );
  manager.AddComponent( player, new Score() );

  unsigned int ai = manager.CreateEntity();
  manager.AddComponent( ai, new Paddle(false) );
  manager.AddComponent( ai, new Score() );

  //4 borders
  //top
  Vector2 pos = { 50.0f, 99.0f };
  Border* border = new Border( pos, true, 2 );
  unsigned int border_ent = manager.CreateEntity();
  manager.AddComponent( border_ent, border );
  //bottom
  pos.y = 1.0f;
  border = new Border( pos, true, 1 );
  border_ent = manager.CreateEntity();
  manager.AddComponent( border_ent, border );
  //left
  pos.x = 1.0f;
  pos.y = 50.0f;
  border = new Border( pos, false, 2 );
  border_ent = manager.CreateEntity();
  manager.AddComponent( border_ent, border );
  //right
  pos.x = 99.0f;
  border = new Border( pos, false, 1 );
  border_ent = manager.CreateEntity();
  manager.AddComponent( border_ent, border );
  */

  {
    //get the document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file( string(LOCAL_DATA + "pong.xml").c_str() );

    if( !result) {
      cout << "XML loading error: " << result.description() << endl;
    }
    else {
      //get the <entities /> tag
      pugi::xml_node entities = doc.child("entities");

      //iterate through each child of the tag to find each <entity /> tag
      for( pugi::xml_node entity = entities.first_child(); entity; entity = entity.next_sibling() ) {
        //create a new entity for each child
        unsigned int entity_id = manager.CreateEntity();

        //iterate through each component of a given entity
        for( pugi::xml_node component = entity.first_child(); component; component = component.next_sibling() ) {
          
          //get the type
          string type = component.attribute("type").value();
          
          //throw it at our component factory
          IComponent* new_component = factory.Create( type );
          if( new_component ) {
            //deserialize any pertinent XML data
            new_component->Deserialize(component);
            //add it to our entity
            manager.AddComponent( entity_id, new_component );
          }
        }
      }
    }

    //document goes out of scope and is destroyed
  }

  //Get game systems
  AIPaddleDriver ai_paddle_driver;
  BallDriver ball_driver;
  Collision collision;
  PlayerPaddleDriver player_paddle_driver;

  while(g_app_running) {
    //start timing the frame
    clock.StartFrame();

    //take care of any events
    console.CheckEvents();

    //run all of our systems to update components, passing the delta_time value for timing
    ball_driver.Process(clock.delta_time());
    ai_paddle_driver.Process(clock.delta_time());
    player_paddle_driver.Process(clock.delta_time());
    collision.Process(clock.delta_time());

    //draw components
    Draw(&console);

    //swap buffers
    console.Present();

    //finish timing frame and update delta time
    clock.EndFrame();
  }

  return 0;
}

void ConsoleProc( INPUT_RECORD *record ) {
  if( record->EventType == KEY_EVENT ) { //escape means we quit
    if( record->Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE ) {
      g_app_running = false;
    }
    //change input map for various keys as needed
    if( record->Event.KeyEvent.wVirtualKeyCode == VK_UP && record->Event.KeyEvent.bKeyDown ) {
      g_input_map[VK_UP] = true;
    }
    else if( record->Event.KeyEvent.wVirtualKeyCode == VK_UP && !record->Event.KeyEvent.bKeyDown ) {
      g_input_map[VK_UP] = false;
    }
    if( record->Event.KeyEvent.wVirtualKeyCode == VK_DOWN && record->Event.KeyEvent.bKeyDown ) {
      g_input_map[VK_DOWN] = true;
    }
    else if( record->Event.KeyEvent.wVirtualKeyCode == VK_DOWN && !record->Event.KeyEvent.bKeyDown ) {
      g_input_map[VK_DOWN] = false;
    }
    if( record->Event.KeyEvent.wVirtualKeyCode == VK_SPACE && record->Event.KeyEvent.bKeyDown ) {
      g_input_map[VK_SPACE] = true;
    }
    else if( record->Event.KeyEvent.wVirtualKeyCode == VK_SPACE && !record->Event.KeyEvent.bKeyDown ) {
      g_input_map[VK_SPACE] = false;
    }
  }
}

void Draw(ConsoleHandler *console) {
  IEntityManager* manager = ServiceLocator::GetEntityManager();

  console->ClearScreen(); //clear to black

  //get our drawable components: ball, paddles, scores.
  vector<IComponent*> ball_components = manager->GetAllComponentsOfType(COMP_BALL);
  Ball* ball = NULL;
  if(ball_components.size() != 0) {
    ball = dynamic_cast<Ball*>(ball_components[0]);
  }
  vector<IComponent*> paddles = manager->GetAllComponentsOfType(COMP_PADDLE);
  vector<IComponent*> scores = manager->GetAllComponentsOfType( COMP_SCORE );

  if( ball ) {
    //ball
    //convert y to 0-50. our 'world' is 100 high, and we have 50 rows.
    Vector2 pos = ball->position_;
    pos.y /= 2;
    //convert x to 0-80. our 'world' is 100 long and we have 80 columns.
    pos.x = (pos.x / 100) * 80;

    //print
    console->PrintCharacter( 0xDB, (unsigned short)pos.x, (unsigned short)pos.y );
  }

  //paddles
  for( unsigned int i=0; i<paddles.size(); ++i ) {
    Paddle* paddle = dynamic_cast<Paddle*>(paddles[i]);

    //convert
    Vector2 pos = paddle->position_;
    pos.y = (pos.y / 2) - (paddle->height_/2);
    pos.x = (pos.x / 100.0f) * 80.0f;

    //print
    for( unsigned int l=0; l<paddle->height_; l++ ) {
      console->PrintCharacter( 0xDB, (unsigned short)pos.x, (unsigned short)pos.y+l );
    }

  }

  for( unsigned int i=0; i< scores.size(); ++i ) {
    int y = 2;
    int x = 10 + (i * 50);

    //print pretty numbers
    switch( dynamic_cast<Score*>(scores[i])->current_score_ ) {
    case 0:
      console->PrintCharacter( 0xDB, x, y );
      console->PrintCharacter( 0xDB, x+1, y );
      console->PrintCharacter( 0xDB, x+2, y );

      console->PrintCharacter( 0xDB, x, y+1 );
      console->PrintCharacter( 0xDB, x+2, y+1 );
      console->PrintCharacter( 0xDB, x, y+2 );
      console->PrintCharacter( 0xDB, x+2, y+2 );
      console->PrintCharacter( 0xDB, x, y+3 );
      console->PrintCharacter( 0xDB, x+2, y+3 );

      console->PrintCharacter( 0xDB, x, y+4 );
      console->PrintCharacter( 0xDB, x+1, y+4 );
      console->PrintCharacter( 0xDB, x+2, y+4 );
      break;
    case 1:
      console->PrintCharacter( 0xDB, x+1, y );
      console->PrintCharacter( 0xDB, x+1, y+1 );
      console->PrintCharacter( 0xDB, x+1, y+2 );
      console->PrintCharacter( 0xDB, x+1, y+3 );
      console->PrintCharacter( 0xDB, x+1, y+4 );
      break;
    case 2:
      console->PrintCharacter( 0xDB, x, y );
      console->PrintCharacter( 0xDB, x+1, y );
      console->PrintCharacter( 0xDB, x+2, y );

      console->PrintCharacter( 0xDB, x+2, y+1 );

      console->PrintCharacter( 0xDB, x+2, y+2 );

      console->PrintCharacter( 0xDB, x+1, y+3 );

      console->PrintCharacter( 0xDB, x, y+4 );
      console->PrintCharacter( 0xDB, x+1, y+4 );
      console->PrintCharacter( 0xDB, x+2, y+4 );
      break;
    case 3:
      console->PrintCharacter( 0xDB, x, y );
      console->PrintCharacter( 0xDB, x+1, y );
      console->PrintCharacter( 0xDB, x+2, y );

      console->PrintCharacter( 0xDB, x+3, y+1 );

      console->PrintCharacter( 0xDB, x+1, y+2 );
      console->PrintCharacter( 0xDB, x+2, y+2 );

      console->PrintCharacter( 0xDB, x+3, y+3 );

      console->PrintCharacter( 0xDB, x, y+4 );
      console->PrintCharacter( 0xDB, x+1, y+4 );
      console->PrintCharacter( 0xDB, x+2, y+4 );
      break;
    case 4:
      console->PrintCharacter( 0xDB, x, y );
      console->PrintCharacter( 0xDB, x, y+1 );
      console->PrintCharacter( 0xDB, x, y+2 );
      console->PrintCharacter( 0xDB, x+1, y+2 );
      console->PrintCharacter( 0xDB, x+2, y+2 );
      console->PrintCharacter( 0xDB, x+3, y+2 );

      console->PrintCharacter( 0xDB, x+2, y );
      console->PrintCharacter( 0xDB, x+2, y+1 );
      console->PrintCharacter( 0xDB, x+2, y+3 );
      console->PrintCharacter( 0xDB, x+2, y+4 );
      break;
    case 5:
      console->PrintCharacter( 0xDB, x+3, y );
      console->PrintCharacter( 0xDB, x+2, y );
      console->PrintCharacter( 0xDB, x+1, y );
      console->PrintCharacter( 0xDB, x, y );

      console->PrintCharacter( 0xDB, x, y+1 );
      console->PrintCharacter( 0xDB, x, y+2 );

      console->PrintCharacter( 0xDB, x, y );
      console->PrintCharacter( 0xDB, x+1, y+2 );
      console->PrintCharacter( 0xDB, x+2, y+2 );
      console->PrintCharacter( 0xDB, x+3, y+2 );

      console->PrintCharacter( 0xDB, x+3, y+3 );

      console->PrintCharacter( 0xDB, x+2, y+4 );
      console->PrintCharacter( 0xDB, x+1, y+4 );
      console->PrintCharacter( 0xDB, x, y+4 );
      break;
    case 6:
      console->PrintCharacter( 0xDB, x+3, y );
      console->PrintCharacter( 0xDB, x+2, y );

      console->PrintCharacter( 0xDB, x+1, y+1 );
      console->PrintCharacter( 0xDB, x, y+2 );
      console->PrintCharacter( 0xDB, x, y+3 );
      console->PrintCharacter( 0xDB, x+1, y+4 );

      console->PrintCharacter( 0xDB, x+1, y+4 );
      console->PrintCharacter( 0xDB, x+2, y+4 );

      console->PrintCharacter( 0xDB, x+3, y+3 );
      console->PrintCharacter( 0xDB, x+3, y+2 );

      console->PrintCharacter( 0xDB, x+2, y+2 );
      console->PrintCharacter( 0xDB, x+1, y+2 );
      break;
    case 7:
      console->PrintCharacter( 0xDB, x, y );
      console->PrintCharacter( 0xDB, x+1, y );
      console->PrintCharacter( 0xDB, x+2, y );
      console->PrintCharacter( 0xDB, x+3, y );

      console->PrintCharacter( 0xDB, x+3, y+1 );
      console->PrintCharacter( 0xDB, x+2, y+2 );
      console->PrintCharacter( 0xDB, x+1, y+3 );
      console->PrintCharacter( 0xDB, x, y+4 );

      console->PrintCharacter( 0xDB, x+1, y+2 );
      console->PrintCharacter( 0xDB, x, y+2 );
      break;
    case 8:
      console->PrintCharacter( 0xDB, x+1, y );
      console->PrintCharacter( 0xDB, x+2, y );

      console->PrintCharacter( 0xDB, x, y+1 );
      console->PrintCharacter( 0xDB, x, y+1 );
      console->PrintCharacter( 0xDB, x+3, y+1 );
      console->PrintCharacter( 0xDB, x+3, y+1 );

      console->PrintCharacter( 0xDB, x+1, y+2 );
      console->PrintCharacter( 0xDB, x+2, y+2 );

      console->PrintCharacter( 0xDB, x, y+3 );
      console->PrintCharacter( 0xDB, x, y+3 );
      console->PrintCharacter( 0xDB, x+3, y+3 );
      console->PrintCharacter( 0xDB, x+3, y+3 );

      console->PrintCharacter( 0xDB, x+1, y+4 );
      console->PrintCharacter( 0xDB, x+2, y+4 );
      break;
    case 9:
      console->PrintCharacter( 0xDB, x+1, y );
      console->PrintCharacter( 0xDB, x+2, y );

      console->PrintCharacter( 0xDB, x, y+1 );
      console->PrintCharacter( 0xDB, x, y+1 );
      console->PrintCharacter( 0xDB, x+3, y+1 );
      console->PrintCharacter( 0xDB, x+3, y+1 );

      console->PrintCharacter( 0xDB, x+1, y+2 );
      console->PrintCharacter( 0xDB, x+2, y+2 );
      console->PrintCharacter( 0xDB, x+3, y+2 );

      console->PrintCharacter( 0xDB, x+3, y+3 );
      console->PrintCharacter( 0xDB, x+2, y+4 );
      console->PrintCharacter( 0xDB, x+1, y+4 );
      break;
    default:
      break;
    }
  }
}