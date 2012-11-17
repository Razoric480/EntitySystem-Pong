//© Francois Belair 2012+
//Author: Francois Belair, http://www.iced-fire.com/
//Handles the win32 STD handles to read and write to the console, giving handy functions to make things easier.

#ifndef ENTITYSYSTEMPONG_CONSOLEHANDLER_H_
#define ENTITYSYSTEMPONG_CONSOLEHANDLER_H_

#include <windows.h>
#include <string>

using std::string;

class ConsoleHandler {
public:
  ConsoleHandler( const unsigned short &console_width, const unsigned short &console_height, const string &console_title, void (*event_proc)(INPUT_RECORD*) );
  ~ConsoleHandler();

  void CheckEvents();

  void Present();

  unsigned short console_width();
  unsigned short console_height();

  void set_console_title( const string &title );
  string console_title();

  void PrintCharacter( const unsigned char &character, unsigned short x, unsigned short y );

  void ClearScreen();

private:
  bool HasEvents();

  unsigned short console_width_;
  unsigned short console_height_;

  string console_title_;

  HANDLE write_handle_;
  HANDLE read_handle_;
  DWORD event_count_;
  INPUT_RECORD event_;
  COORD char_buffer_size_;
  COORD character_pos_;
  CHAR_INFO *console_buffer_;
  SMALL_RECT write_area_;

  void (*event_proc_)(INPUT_RECORD*);
};

#endif//ENTITYSYSTEMPONG_CONSOLEHANDLER_H_
