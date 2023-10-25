#ifndef LIFE_H
#define LIFE_H

#include <stdio.h>
//#include <SDL2/SDL.h>
#include "SDL/include/SDL2/SDL.h"
#include "SDL/include/SDL2/SDL_ttf.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define NUM_CELLS_HORIZONTAL 160  // Number of cells horizontally
#define NUM_CELLS_VERTICAL 120    // Number of cells vertically
#define CELLWIDTH (WINDOW_WIDTH / NUM_CELLS_HORIZONTAL)
#define CELLHEIGHT (WINDOW_HEIGHT / NUM_CELLS_VERTICAL)
#endif


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

void voidRect(SDL_Renderer *renderer, int x, int y);
void	nocolorClick(SDL_Renderer *renderer, int x, int y, int w, int h, s_cell **cell);
void	fillRect(SDL_Renderer *renderer, int x, int y);
void 	drawGrid(SDL_Renderer *renderer, s_cell **cell, SDL_Texture *bufferTexture, SDL_Texture *bufferTexture2);
void	mousePos(int *x, int *y);
void	spawnRect(SDL_Renderer *renderer, int x, int y, int w,int h);
void	colorClick(SDL_Renderer *renderer, int x,int y,int w,int h, s_cell **cell);
