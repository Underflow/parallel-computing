#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../static-lib/lib/mlc.h"
#include <SDL/SDL.h>
#include "metaballs.h"

static const int MAX_FRAMES = 200;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int MAX_METABALLS = 5;
const float MIN_THRESHOLD = 0.99f;
const float MAX_THRESHOLD = 1.05f;


SDL_Surface *surfaces[500];

char* gen_task(int id)
{
    char *str = malloc(1024);
    if(id > MAX_FRAMES)
    {
        strcpy(str, "echo termiated");
        return str;
    }
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
    if(id >= MAX_FRAMES)
    {
        quit();
    }
    printf("--- \n Received result. \n Task : %d \n Data : %s \n --- \n", id, data);
    printf("%d\n", size_of);
    FILE *f;
    f = fopen("/tmp/meta.bmp", "w+");
    fwrite(data, size_of, 1, f);
    fclose(f);
    surfaces[id] = SDL_LoadBMP("/tmp/meta.bmp");
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
        int i = 0;
        while(1)
        {
            SDL_BlitSurface(surfaces[i%MAX_FRAMES], NULL, screen, NULL);
            SDL_UpdateRect(screen, 0, 0, 0, 0);
            ++i;
        }
        SDL_FreeSurface(screen);
        SDL_Quit();
        return 0;
    }
}
