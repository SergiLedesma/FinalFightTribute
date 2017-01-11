#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "MemLeaks.h"
#include "SDL/include/SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs ---------
typedef unsigned int uint;

// Deletes a buffer
#define RELEASE( x ) \
    {									  \
       if( x != nullptr )   \
       {						      \
         delete x;                  \
	     x = nullptr;             \
       }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{                              \
       if( x != nullptr )              \
       {                            \
           delete[] x;                \
	       x = nullptr;                    \
		 }                            \
                              \
	 }

// Configuration -----------
#define SCREEN_SIZE 3
#define SCREEN_WIDTH 256//384
#define SCREEN_HEIGHT 195//240
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Super Awesome Game"

// Controls -----------
#define GORIGHT SDL_SCANCODE_RIGHT
#define GOLEFT SDL_SCANCODE_LEFT
#define GOUP SDL_SCANCODE_UP
#define GODOWN SDL_SCANCODE_DOWN
#define JUMP SDL_SCANCODE_Z
#define ATTACK SDL_SCANCODE_X
#define PAUSE SDL_SCANCODE_P
#define CAMERARIGHT SDL_SCANCODE_D
#define CAMERALEFT SDL_SCANCODE_A
#define CAMERAUP SDL_SCANCODE_W
#define CAMERADOWN SDL_SCANCODE_S
#define DEBUG SDL_SCANCODE_F1

#endif //__GLOBALS_H__