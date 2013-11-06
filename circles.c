#define SAVE_SCREEN         // this directive forces saving/restoring the screen
#define USE_TI89
#define OPTIMIZE_ROM_CALLS

#define NUM_CIRCLES 5
#define CYCLES 1
#define MAX_RADIUS 100

#include <tigcclib.h>

_main() {
  short x1, x2, x3, y1, y2, y3, x4, y4, x5, y5;

  short r = 0;

  int n = 4;
  int i;
  while (--n > 0) {
    x1 = random(150);
    x2 = random(150);
    x3 = random(150);
    x4 = random(150);
    x5 = random(150);
    y1 = random(100);
    y2 = random(100);
    y3 = random(100);
    y4 = random(100);
    y5 = random(100);
    for (i = 0; i < 200; ++i){
      r = (r + 1) % 100;
      DrawClipEllipse(x1, y1, r, r, &(SCR_RECT){{0, 0, 159, 99}}, A_XOR);
      DrawClipEllipse(x2, y2, r, r, &(SCR_RECT){{0, 0, 159, 99}}, A_XOR);
      DrawClipEllipse(x3, y3, r, r, &(SCR_RECT){{0, 0, 159, 99}}, A_XOR);
      DrawClipEllipse(x4, y4, r, r, &(SCR_RECT){{0, 0, 159, 99}}, A_XOR);
      DrawClipEllipse(x5, y5, r, r, &(SCR_RECT){{0, 0, 159, 99}}, A_XOR);
    }
  }
}
