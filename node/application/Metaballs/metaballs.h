#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int MAX_METABALLS = 5;
const float MIN_THRESHOLD = 0.99f;
const float MAX_THRESHOLD = 1.05f;

typedef struct metaball_t metaball;
struct metaball_t {
float _x;
float _y;
float _radius;
float equation;
};

void initMetaball(metaball *m, float startx, float starty, float radius);

float equation(metaball m, float x, float y);

void draw_pixel(SDL_Surface *screen, int x, int y, Uint32 color);

void draw_metaballs(SDL_Surface *screen, metaball **ballList, Uint32 color);

void move(SDL_Surface *screen, metaball *m, int *vx, int *vy);
