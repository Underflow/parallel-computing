#include "metaballs.h"

void initMetaball(metaball *m, float startx, float starty, float radius)
{
m->_x = startx;
m->_y = starty;
m->_radius = radius;
}

float equation(metaball m, float x, float y)
{ return (m._radius / sqrt( (x-m._x)*(x-m._x) + (y-m._y)*(y-m._y) ) ); }

void draw_pixel(SDL_Surface *screen, int x, int y, Uint32 color)
{
if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            return;
        }
    }
    switch (screen->format->BytesPerPixel) {
        case 1: { /*On gère le mode 8bpp */
            Uint8 *bufp;

            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
            *bufp = color;
        }
        break;

        case 2: { /* Certainement 15 ou 16 bpp */
            Uint16 *bufp;

            bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
            *bufp = color;
        }
        break;

        case 3: { /* 24 bpp lent et généralement pas utilisé */
            Uint8 *bufp;

            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
            if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
                bufp[0] = color;
                bufp[1] = color >> 8;
                bufp[2] = color >> 16;
            } else {
                bufp[2] = color;
                bufp[1] = color >> 8;
                bufp[0] = color >> 16;
            }
        }
        break;

        case 4: { /* Probablement 32 bpp alors */
            Uint32 *bufp;

            bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
            *bufp = color;
        }
        break;
    }
    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }
}

void draw_metaballs(SDL_Surface *screen, metaball **ballList, Uint32 color) 
{
// Value to act as a summation of all Metaballs' fields applied to this particular pixel
float sum;
// Iterate over every pixel on the screen
 for(int y = 0; y < SCREEN_HEIGHT; y++)
 {
   for(int x = 0; x < SCREEN_WIDTH; x++)
   { // Reset the summation
   sum = 0;
   // Iterate through every Metaball in the world
      for(int i = 0; i < MAX_METABALLS && ballList[i] != NULL; i++)
      {
	 (ballList[i])->equation = equation(*(ballList[i]), x, y);
         sum += (ballList[i])->equation;
      }
      // Decide whether to draw a pixel
      if(sum >= MIN_THRESHOLD && sum <= MAX_THRESHOLD)
      {
         draw_pixel(screen, x, y, color);
      }
   }
 }
}

void move(SDL_Surface *screen, metaball *m, int *vx, int *vy)
{
m->_x += *vx;
m->_y += *vy;

if(m->_x + m->_radius >= SCREEN_WIDTH || m->_x - m->_radius <= 0)
*vx = - (*vx);

if(m->_y + m->_radius >= SCREEN_HEIGHT || m->_y - m->_radius <= 0)
*vy = - (*vy);

}

int main(int argc, char* args[])
{
SDL_Surface *screen = NULL;
SDL_Event event;
if (argc == 2 && atoi(args[1]) == -1)
printf("-1");
else
{
//SDL_Surface *screen = NULL;
//SDL_Event event;
int quit = 1;
int vx = atoi(args[1]);
int vy = atoi(args[2]);
int vx2 = 2;
int vy2 = -2;


//srand(time(NULL));

if (SDL_Init(SDL_INIT_VIDEO) == -1)
{
	printf("Can't init SDL : %s\n", SDL_GetError());
	return EXIT_FAILURE;
}

//atexit(SDL_Quit());

screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0, 0, 0 ,0);

/*if(screen == NULL)
{
	printf("Can't set the video mode : %s\n", SDL_GetError());
	return EXIT_FAILURE;
}*/


metaball *ballList[MAX_METABALLS];

metaball m1, m2, m3, m4;

initMetaball(&m1, 40, 40, 20);
initMetaball(&m2, 35, 270, 30);
initMetaball(&m3,230, 300, 10);
initMetaball(&m4, 300, 300, 45);

ballList[0] = &m1;
ballList[1] = &m2;
ballList[2] = &m3;
ballList[3] = &m4;


/*while (quit)
{
while (SDL_PollEvent(&event))
{
if (event.type == SDL_QUIT)
quit = 0; 
}
*/
SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

Uint32 color_white = SDL_MapRGB(screen->format, 255, 120, 255);
move(screen, ballList[0], &vx, &vy);
move(screen, ballList[1], &vx2, &vy2);
//move(screen, ballList[2], vx, vy);
//move(screen, ballList[3], vx, vy);

draw_metaballs(screen, ballList, color_white);
//SDL_UpdateRect(screen, 0, 0, 0, 0);
//SDL_Delay(10000);
//}
SDL_SaveBMP(screen, "/tmp/meta.bmp");
FILE* f;
f = fopen("/tmp/meta.bmp", "rb");
char *buf = calloc(1, 1024);
size_t s;
while(s = fread(buf, 1, 1024, f))
{
	fwrite(buf, 1, s, stdout);
}
SDL_FreeSurface(screen);
SDL_Quit();
}
return 0;

}
