#define SAVE_SCREEN         // this directive forces saving/restoring the screen
#define USE_TI89
#define OPTIMIZE_ROM_CALLS
#include <tigcclib.h>

#define BITMAP_SIZE (BITMAP_HDR_SIZE + HEIGHT*HEIGHT/8)

#define RADIUS 5
#define TIMESTEP 0.2
#define SIM_TIME 500
#define GRAVITY 1
#define GRAVATIONAL_CONSTANT 5000

#define TOP    RADIUS
#define BOTTOM (LCD_HEIGHT - RADIUS)
#define LEFT   RADIUS
#define RIGHT  (LCD_WIDTH - RADIUS)
#define SCREEN (&(SCR_RECT) {{0, 0, LCD_WIDTH-1, LCD_HEIGHT-1}})

typedef struct {
  float x;
  float y;
} Vector;

void updateCircle(const Vector *v, short Attr) {
  int x = (int) (v->x + 0.5);
  int y = (int) (v->y + 0.5);
  DrawClipEllipse(x, y, RADIUS, RADIUS, SCREEN, Attr);
}

void addVector(Vector *v, const Vector *a) {
  v->x += a->x;
  v->y += a->y;
}

void subVector(Vector *v, const Vector *a) {
  v->x -= a->x;
  v->y -= a->y;
}

void mulConstVector(Vector *dest, Vector *src, float c) {
  dest->x = src->x * c;
  dest->y = src->y * c;
}

float lengthVector(Vector *v) {
  return sqrt((v->x)*(v->x) + (v->y)*(v->y));
}

void printVector(Vector *v) {
  printf("(%f, %f)\n", v->x, v->y);
}

void updateLinearGravity(Vector *r, Vector *v) {
  Vector dr = {0, 0};
  // Collision detection
  if (r->x < LEFT || r->x > RIGHT)
    v->x = -v->x;
  if (r->y < TOP || r->y > BOTTOM)
    v->y = -v->y;
  // Updating delta t
  v->y += GRAVITY * TIMESTEP;
  mulConstVector(&dr, v, TIMESTEP);
  addVector(r, &dr);
}

void updateRadialGravity(Vector *r, Vector *v) {
  Vector vg = {LCD_WIDTH / 2, LCD_HEIGHT / 2};
  Vector dr = {0, 0}, dv = {0, 0}, force = {0, 0};
  float len, tmp;

  // Compute force
  subVector(&vg, r);
  len = lengthVector(&vg);
  tmp = GRAVATIONAL_CONSTANT * GRAVITY / (len * len * len);
  if (tmp > 1) {
    tmp = 0;
  }
  force.x = tmp * vg.x;
  force.y = tmp * vg.y;

  // Increment velocity
  mulConstVector(&dv, &force, TIMESTEP);
  addVector(v, &dv);

  // Increment position
  mulConstVector(&dr, v, TIMESTEP);
  addVector(r, &dr);
}
