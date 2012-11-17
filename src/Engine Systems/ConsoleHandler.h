//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Handles the win32 STD handles to read and write to the console, giving handy functions to make things easier.

#ifndef ENTITYSYSTEMPONG_CONSOLEHANDLER_H_
#define ENTITYSYSTEMPONG_CONSOLEHANDLER_H_

#include <windows.h>
#include <string>

using std::string;

//Sample usage:
//  void ConsoleProc(INPUT_RECORD* event) { if( record->Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE ) { g_app_is_running = false; } }
//  ConsoleHandler console(80, 50, "Pong", ConsoleProc);
//  while(g_app_is_running) {
//    console.CheckEvents();
//    console.ClearScreen();
//    console.PrintCharacter( 'H', 20, 20 );
//    console.Present();
//  }
class ConsoleHandler {
public:
  //Constructor initializes width, height, title and an optional event processor. Note that the console must be destroyed prior to re-initializing it.
  ConsoleHandler( const unsigned short &console_width, const unsigned short &console_height, const string &console_title, void (*event_proc)(INPUT_RECORD*) );
  ~ConsoleHandler(); //destructor

  //Check for events and iterates through each one, calling the proc appropriately
  void CheckEvents();

  //Prints the backbuffer to the console 
  void Present();

  //Gets the width of the console
  unsigned short console_width();
  //Gets the height of the console
  unsigned short console_height();

  //Sets the console title
  void set_console_title( const string &title );
  //Gets the console title
  string console_title();

  //Prints a single character at a given X and Y
  void PrintCharacter( const unsigned char &character, unsigned short x, unsigned short y );

  //Makes all characters in the console spaces
  void ClearScreen();

private:
  //Returns true if there are events to handle
  bool HasEvents();

  unsigned short console_width_;
  unsigned short console_height_;

  string console_title_;

  HANDLE write_handle_; //STD_HANDLE for output
  HANDLE read_handle_; //STD_HANDLE for input
  DWORD event_count_; //Number of events
  INPUT_RECORD event_; //A singular event, repopulated to save memory
  COORD char_buffer_size_; //The size of the buffer
  COORD character_pos_; //A position buffer to say where the console buffer should be written 
  CHAR_INFO *console_buffer_; //The buffer to write to the console
  SMALL_RECT write_area_; //The size of the write area

  //Function pointer for event procs
  void (*event_proc_)(INPUT_RECORD*);
};

#endif//ENTITYSYSTEMPONG_CONSOLEHANDLER_H_
