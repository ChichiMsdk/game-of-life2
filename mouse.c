#include "life.h"

// convert coordinates to cell coordinates
void	nocolorClick(SDL_Renderer *renderer, int x, int y, int w, int h, s_cell **cell)
{
	if ( x >= 1900 || y <= 0 || x <= 0 || y >= 1000)
	{
		printf("x = %d and y = %d are out of bound\n", x, y);
		return;
	}
	int i_x;
	int i_y;
	i_x = x / w;
	i_y = y / h;
	cell[i_x][i_y].alive = 0;
	cell[i_x][i_y].score = 0;
	cell[i_x][i_y].color = WHITE;
	//printf("alive = %d\n", cell[i_x][i_y].alive);
	//voidRect(renderer, cell[i_x][i_y].x*CELLWIDTH, cell[i_x][i_y].y*CELLHEIGHT);
	voidRect(renderer, i_x*CELLWIDTH, i_y*CELLHEIGHT);
}
// convert coordinates to cell coordinates
void	colorClick(SDL_Renderer *renderer, int x, int y, int w, int h, s_cell **cell)
{
	if ( x >= 1900 || y <= 0 || x <= 0 || y >= 1000)
	{
		printf("x = %d and y = %d are out of bound\n", x, y);
		return;
	}
	int i_x;
	int i_y;
	i_x = x / w;
	i_y = y / h;
//	i_x = (int)((float)x / (w*1.2));
//	i_y =(int)((float)y / (h*1.2));
	cell[i_x][i_y].alive = 1;
	cell[i_x][i_y].score = 2;
	cell[i_x][i_y].color = BLACK;
	//printf("alive = %d\n", cell[i_x][i_y].alive);
	//printf("x = %d, y = %d, .x = %d, .y = %d\n", x, y, cell[x][y].x, cell[x][y].y);
	//fillRect(renderer, cell[i_x][i_y].x*CELLWIDTH, cell[i_x][i_y].y*CELLHEIGHT);
	fillRect(renderer, i_x*CELLWIDTH, i_y*CELLHEIGHT);
}

void	spawnRect(SDL_Renderer *renderer, int x, int y, int w,int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void	mousePos(int *x, int *y)
{
	*x = 0;
	*y = 0;
	SDL_GetMouseState(x, y);
}
