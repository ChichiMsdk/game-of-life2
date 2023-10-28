#include "life.h"

SDL_Texture	*fonting(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect Fontrect, char *str, int counter)
{
	SDL_itoa(counter, str, 10);
	SDL_Color textColor = {255, 0, 0, 0};
	SDL_Surface *surface = TTF_RenderText_Solid(font, str, textColor);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	Fontrect.w = surface->w;
	Fontrect.h = surface->h;
	SDL_FreeSurface(surface);
	return(texture);
	//SDL_RenderPresent(renderer);
}

void voidRect(SDL_Renderer *renderer, int x, int y)
{
	SDL_Rect rect;
	rect.x = x+1;
	rect.y = y+1;
	rect.w = CELLWIDTH-1;
	rect.h = CELLHEIGHT-1;

//	SDL_SetRenderDrawColor(renderer, 0, 198, 0, 255);
	SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void	fillRect(SDL_Renderer *renderer, int x, int y)
{
	SDL_Rect rect;
	rect.x = x+2;
	rect.y = y+2;
	rect.w = CELLWIDTH-3;
	rect.h = CELLHEIGHT-3;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}
void	DrawCell(SDL_Renderer *renderer,s_cell **cell,int x,int y)
{
	if ((cell[x][y].score == 2 || cell[x][y].score == 3) && cell[x][y].alive == 1)
	{
		voidRect(renderer, cell[x][y].x*CELLWIDTH, cell[x][y].y*CELLHEIGHT);
		fillRect(renderer, cell[x][y].x*CELLWIDTH, cell[x][y].y*CELLHEIGHT);
		cell[x][y].colorNext = BLACK;
		cell[x][y].aliveNext = 1;
	}
	else if ( cell[x][y].score == 3 && cell[x][y].alive == 0)
	{
		voidRect(renderer, cell[x][y].x*CELLWIDTH, cell[x][y].y*CELLHEIGHT);
		fillRect(renderer, cell[x][y].x*CELLWIDTH, cell[x][y].y*CELLHEIGHT);
		cell[x][y].colorNext = BLACK;
		cell[x][y].aliveNext = 1;
	}
	else
	{
		voidRect(renderer, cell[x][y].x*CELLWIDTH, cell[x][y].y*CELLHEIGHT);
		cell[x][y].colorNext = WHITE;
		cell[x][y].aliveNext = 0;
	}
}

int neighbours(SDL_Renderer *renderer, s_cell **cell, Uint32 lastUpdatedTime, Uint32 currentTime)
{
	//SDL_SetRenderTarget(renderer, bufferTexture2);
	//SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
	int score = 0;

	if (!cell)
		exit (1);
	int x = 0;
	int y = 0;
	while (x < NUM_CELLS_HORIZONTAL)
	{
		y = 0;
		score = 0;
		while ( y < NUM_CELLS_VERTICAL)
		{
				if (x - 1 >= 0 && cell[x - 1][y].alive == 1) // WEST
					score++;
				if (x + 1 < NUM_CELLS_HORIZONTAL && cell[x + 1][y].alive == 1) // EAST
					score++;
				if (y - 1 >= 0 && cell[x][y - 1].alive == 1) // NORTH
					score++;
				if (y + 1 < NUM_CELLS_VERTICAL && cell[x][y + 1].alive == 1) // SOUTH
					score++;
				if (x - 1 >= 0 && y - 1 >= 0 && cell[x - 1][y - 1].alive == 1) // NORTH WEST
					score++;
				if (x + 1 < NUM_CELLS_HORIZONTAL && y - 1 >= 0 && cell[x + 1][y - 1].alive == 1) // NORTH EAST
					score++;
				if (x - 1 >= 0 && y + 1 < NUM_CELLS_VERTICAL && cell[x - 1][y + 1].alive == 1) // SOUTH WEST
					score++;
				if (x + 1 < NUM_CELLS_HORIZONTAL && y + 1 < NUM_CELLS_VERTICAL && cell[x + 1][y + 1].alive == 1) // SOUTH EAST
					score++;
				cell[x][y].scoreNext = score;
				score = 0;
				DrawCell(renderer, cell, x, y);
			y++;
		}
		x++;
	}
	x = 0;
	y = 0;
		while (x < NUM_CELLS_HORIZONTAL)
		{
			y = 0;
				while (y < NUM_CELLS_VERTICAL)
			{
				cell[x][y].alive = cell[x][y].aliveNext;
				cell[x][y].color = cell[x][y].colorNext;
				cell[x][y].score = cell[x][y].scoreNext;
				y++;
			}
			x++;
		}

	//SDL_SetRenderTarget(renderer, NULL);
	//SDL_RenderCopy(renderer, bufferTexture2, NULL, NULL);
   //	drawGrid(renderer, cell, bufferTexture2, bufferTexture2);
	return (score);
}

int living(SDL_Renderer *renderer, s_cell **cell, Uint32 lastUpdatedTime, Uint32 currentTime)
{
	if (!cell)
		exit (1);
	//SDL_SetRenderTarget(renderer, bufferTexture);
	neighbours(renderer, cell, lastUpdatedTime, currentTime);
	return (0);
}

void drawBG(SDL_Renderer *renderer, SDL_Texture *bufferTexture, SDL_Texture *bufferTexture2)
{
	//SDL_SetRenderDrawColor(renderer,160, 160, 160, 255);
	SDL_SetRenderDrawColor(renderer, 198, 198, 198, 255);
	SDL_RenderClear(renderer);
}

void drawGrid(SDL_Renderer *renderer, s_cell **cell, SDL_Texture *bufferTexture, SDL_Texture *bufferTexture2) 
{
	SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int i = 0;
    while ( i <= NUM_CELLS_HORIZONTAL) 
	{
        int x = i * CELLWIDTH;
        if (SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT)< 0)
			exit(1);
		i++;
    }

	int j = 0;
    while ( j <= NUM_CELLS_VERTICAL)
	{
        int y = j * CELLHEIGHT;
        if (SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y) < 0)
			exit(1);
		j++;
    }
}
