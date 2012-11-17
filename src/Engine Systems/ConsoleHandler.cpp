#include "ConsoleHandler.h"

ConsoleHandler::ConsoleHandler( const unsigned short &console_width, const unsigned short &console_height, const string &console_title,
                               void (*event_proc)(INPUT_RECORD*) )
  : console_width_(console_width), console_height_(console_height), console_title_(console_title), event_count_(0), event_proc_(event_proc) {
  write_handle_ = GetStdHandle( STD_OUTPUT_HANDLE ); //Get the handles to the console
  read_handle_ = GetStdHandle( STD_INPUT_HANDLE );

  SetConsoleTitleA( console_title_.c_str() ); //set our initial title

  //set our write area and buffer values
  char_buffer_size_.X = console_width_;
  char_buffer_size_.Y = console_height_;

  write_area_.Left = 0;
  write_area_.Top = 0;
  write_area_.Right = console_width_-1;
  write_area_.Bottom = console_height_-1;

  //make our backbuffer and set it to all black with normal white text
  console_buffer_ = new CHAR_INFO[console_width_ * console_height_];
  for(int i=0; i<console_width_*console_height_; ++i) {
    console_buffer_[i].Char.AsciiChar = ' ';
    console_buffer_[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
  }

  character_pos_.X = 0;
  character_pos_.Y = 0;
  
  //finally, set our console and console buffer to the correct sizes
  SetConsoleWindowInfo( write_handle_, true, &write_area_ );
  SetConsoleScreenBufferSize( write_handle_, char_buffer_size_ );
}

ConsoleHandler::~ConsoleHandler() {
  if( console_buffer_ ) { //destroy the buffer, the only heap part of our handler
    delete[] console_buffer_;
    console_buffer_ = 0;
  }
}

void ConsoleHandler::CheckEvents() {
  if( !HasEvents() ) { //check if we have events. if we do not, let's just clear out
    return;
  }

  //if we do, we loop through each onea nd call the proc for it, win32 style
  DWORD events_read;
  while( event_count_ > 0 ) {
    ReadConsoleInput( read_handle_, &event_, 1, &events_read );

    if(event_proc_) {
      event_proc_(&event_);
    }

    --event_count_;
  }
}

void ConsoleHandler::Present() {
  //write our backbuffer to the console
  WriteConsoleOutputA( write_handle_, console_buffer_, char_buffer_size_, character_pos_, &write_area_ );
}

bool ConsoleHandler::HasEvents() {
  //get the number of events and then report
  GetNumberOfConsoleInputEvents( read_handle_, &event_count_ );

  return event_count_ != 0;
}

unsigned short ConsoleHandler::console_width() {
  return console_width_;
}

unsigned short ConsoleHandler::console_height() {
  return console_height_;
}

void ConsoleHandler::set_console_title( const string &title ) {
  console_title_ = title;
  SetConsoleTitleA( console_title_.c_str() );
}

string ConsoleHandler::console_title() {
  return console_title_;
}

void ConsoleHandler::PrintCharacter( const unsigned char &character, unsigned short x, unsigned short y ) {
  //clamp, to make sure we cannot print outside the buffer
  if( x > console_width_-1 ) {
    x = console_width_-1; //our console width is actual width size, so we minus one since the buffer is an array (0-(N-1))
  }
  else if( x < 0 ) {
    x = 0;
  }
  if( y > console_height_-1 ) {
    y = console_height_-1;
  }
  else if( y < 0 ) {
    y = 0;
  }
  console_buffer_[x+console_width_ * y].Char.AsciiChar = character;
}


void ConsoleHandler::ClearScreen() {
  //replace with spaces
  for(int i=0; i<console_width_ * console_height_; ++i) {
    console_buffer_[i].Char.AsciiChar = ' ';
  }
}