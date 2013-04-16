#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../static-lib/lib/mlc.h"
#include <SDL/SDL.h>
#include "metaballs.h"

const int MAX_FRAMES = 200;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int MAX_METABALLS = 5;
const float MIN_THRESHOLD = 0.99f;
const float MAX_THRESHOLD = 1.05f;


//static SDL_Surface surfaces[MAX_FRAMES];

char* gen_task(int id)
{
    char *str = malloc(1024);
    strcpy(str, "./application/Metaballs/metaballs ");
    static int vx=1;
    static int vy=1;
    char *v_x = malloc(1024);
    char *v_y = malloc(1024);
    sprintf(v_x, "%d", vx++);
    sprintf(v_y, "%d", vy++);
    strcat(str, v_x);
    strcat(str, " ");
    strcat(str, v_y);
    return str;
}

void get_result(int id, double mac, int size_of, char* data)
{
    printf("--- \n Received result. \n Task : %d \n Data : %s \n --- \n", id, data);
    printf("%d\n", size_of);
    FILE *f;
    f = fopen("test.bmp", "w+");
    fwrite(data, size_of, 1, f);
 //  surfaces[id] = frame;
}

int main(int argc, char* argv[])
{
    init(&gen_task, &get_result);
    SDL_Surface* screen;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE);
    int quit = 1;
    while(quit)
	{
	while(SDL_PollEvent(&event))
	{
	 if (event.type == SDL_QUIT)
	  quit = 0;
	}
	 SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
/*	 for (int i = 0 ; i < MAX_FRAMES ; i++)
	 {
		SDL_BlitSurface(&(surfaces[i]), NULL, screen, NULL);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	 }*/
	}
    SDL_FreeSurface(screen);
    SDL_Quit();
    return 0;
}
