#define SAVE_SCREEN         // this directive forces saving/restoring the screen
#define USE_TI89
#define OPTIMIZE_ROM_CALLS

#define HEIGHT 40
#define BITMAP_SIZE (BITMAP_HDR_SIZE + HEIGHT*HEIGHT/8)

#define ENTER_KEY 13
#define LEFT_KEY  338
#define RIGHT_KEY 344
#define UP_KEY    337
#define DOWN_KEY  340

#define DRAW // 1. *** YOUR CODE HERE ***

#include <tigcclib.h>

_main() {
  SCR_RECT SCREEN = {{0, 0, LCD_WIDTH-1, LCD_HEIGHT-1}};
  SCR_RECT rect = {{0, 0, HEIGHT-1, HEIGHT-1}};

  short attr = A_XOR; // Default replace value: A_XOR

  // Parses arguments
  ESI argptr;
  InitArgPtr(argptr);
  int argtype = GetArgType(argptr);
  if (argtype == POSINT_TAG) {
    int num = GetIntArg(argptr);
    // 2. *** YOUR CODE HERE ***
  }

  // Initializes a rectangle bitmap of HEIGHT x HEIGHT
  char mask [BITMAP_SIZE];
  int i = 0;
  while (i < BITMAP_SIZE) {
    mask[i] = 0xFF; // Change this value to get different masks!
    i++;
  }
  BitmapInit(&rect, mask);

  // Puts the rectangle onto the screen
  DRAW;

  int c;
  // Main loop for getting keyboard input
  while ((c = ngetchx()) != ENTER_KEY) {
    // Erases old bitmap
    DRAW;
    switch (c) { // Moves bitmap around
    case LEFT_KEY:
      if (rect.xy.x0 - 5 >= 0) {
        rect.xy.x0 -=5;
        rect.xy.x1 -=5;
      }
      break;
    case RIGHT_KEY:
      if (rect.xy.x1 + 5 < LCD_WIDTH) {
        rect.xy.x0 +=5;
        rect.xy.x1 +=5;
      }
      break;
    case UP_KEY:
      if (rect.xy.y0 - 5 >= 0) {
        rect.xy.y0 -=5;
        rect.xy.y1 -=5;
      }
      break;
    case DOWN_KEY:
      if (rect.xy.y1 + 5 < LCD_HEIGHT) {
        rect.xy.y0 +=5;
        rect.xy.y1 +=5;
      }
      break;
    }
    // Draws new bitmap
    DRAW;
  }
}
