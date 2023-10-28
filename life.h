#ifndef LIFE_H
#define LIFE_H

#include <stdio.h>
//#include <SDL2/SDL.h>
#include <math.h>
#include "SDL/include/SDL2/SDL.h"
#include "SDL/include/SDL2/SDL_ttf.h"
#include "SDL/include/SDL2/SDL_image.h"

#define WINDOW_WIDTH 1900
#define WINDOW_HEIGHT 1000
#define NUM_CELLS_HORIZONTAL 190  // Number of cells horizontally
#define NUM_CELLS_VERTICAL 100    // Number of cells vertically
#endif

extern Uint32 DELAY;
extern Uint32 CELLWIDTH; 
extern Uint32 CELLHEIGHT;

enum colors
{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	YELLOW = 3,
	PURPLE = 4,
	CYAN = 5,
	WHITE = 6,
	BLACK = 7,
};

typedef struct s_cell
{
	int x;
	int y;
	int alive;
	int color;
	int score;
	int aliveNext;
	int scoreNext;
	int colorNext;
} s_cell;

void		bouge(SDL_Rect *rect,int x,int y, int X_offset, int Y_offset);
SDL_Texture	*fonting(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect Fontrect, char *str, int DELAY);
int 		living(SDL_Renderer *renderer, s_cell **cell, Uint32 lastUpdatedTime, Uint32 currentTime);
void 		voidRect(SDL_Renderer *renderer, int x, int y);
void		nocolorClick(SDL_Renderer *renderer, int x, int y, int w, int h, s_cell **cell);
void		fillRect(SDL_Renderer *renderer, int x, int y);
void 		drawGrid(SDL_Renderer *renderer, s_cell **cell, SDL_Texture *bufferTexture, SDL_Texture *bufferTexture2);
void		mousePos(int *x, int *y);
void		spawnRect(SDL_Renderer *renderer, int x, int y, int w,int h);
void		colorClick(SDL_Renderer *renderer, int x,int y,int w,int h, s_cell **cell);
int			isMoving(int x, int y, int oldx, int oldy);
void		DrawCell(SDL_Renderer *renderer,s_cell **cell,int x,int y);
Uint32 mapScaleToDelay(int scale_position) ;
int mapDelayToScale(Uint32 delay);
