#include "life.h"

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
	rect.x = x+1;
	rect.y = y+1;
	rect.w = CELLWIDTH-1;
	rect.h = CELLHEIGHT-1;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}

int neighbours(SDL_Renderer *renderer, s_cell **cell, SDL_Texture *bufferTexture, SDL_Texture *bufferTexture2)
{
	SDL_SetRenderTarget(renderer, bufferTexture2);
	SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
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
			{
				score++;
				//printf("1\n");
			}
			if (x + 1 < NUM_CELLS_HORIZONTAL && cell[x + 1][y].alive == 1) // EAST
			{
				score++;
				//printf("2\n");
			}
			if (y - 1 >= 0 && cell[x][y - 1].alive == 1) // NORTH
			{
				score++;
				//printf("3\n");
			}
			if (y + 1 < NUM_CELLS_VERTICAL && cell[x][y + 1].alive == 1) // SOUTH
			{
				score++;
				//printf("4\n");
			}
			if (x - 1 >= 0 && y - 1 >= 0 && cell[x - 1][y - 1].alive == 1) // NORTH WEST
			{
				score++;
				//printf("5\n");
			}
			if (x + 1 < NUM_CELLS_HORIZONTAL && y - 1 >= 0 && cell[x + 1][y - 1].alive == 1) // NORTH EAST
			{
				score++;
				//printf("6\n");
			}
			if (x - 1 >= 0 && y + 1 < NUM_CELLS_VERTICAL && cell[x - 1][y + 1].alive == 1) // SOUTH WEST
			{
				score++;
				//printf("7\n");
			}
			if (x + 1 < NUM_CELLS_HORIZONTAL && y + 1 < NUM_CELLS_VERTICAL && cell[x + 1][y + 1].alive == 1) // SOUTH EAST
			{
				score++;
				//printf("8\n");
			}
			static int continuing;
			cell[x][y].scoreNext = score;
			score = 0;
	
			if ((cell[x][y].score == 2 || cell[x][y].score == 3) && cell[x][y].alive == 1)
			{
				fillRect(renderer, cell[x][y].x*CELLWIDTH, cell[x][y].y*CELLHEIGHT);
				cell[x][y].colorNext = BLACK;
				cell[x][y].aliveNext = 1;
			}
			else if ( cell[x][y].score == 3 && cell[x][y].alive == 0)
			{
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
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, bufferTexture2, NULL, NULL);
    drawGrid(renderer, cell, bufferTexture2, bufferTexture2);
	return (score);
}

int living(SDL_Renderer *renderer, s_cell **cell, SDL_Texture *bufferTexture, SDL_Texture *bufferTexture2)
{
	if (!cell)
		exit (1);
	SDL_SetRenderTarget(renderer, bufferTexture);
	neighbours(renderer, cell, bufferTexture, bufferTexture2);
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

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    (void)argc;
    (void)argv;
	s_cell **cell = malloc(sizeof(s_cell*) * NUM_CELLS_HORIZONTAL);
	if (!cell)
		exit(1);
	int i = 0;
	while (i < NUM_CELLS_HORIZONTAL)
	{
		cell[i] = malloc(sizeof(s_cell) * NUM_CELLS_VERTICAL);
		if (!cell[i])
			exit(1);
		i++;
	}
	i = 0;
	int j = 0;
	while(i < NUM_CELLS_HORIZONTAL)
	{
		j = 0;
		while (j < NUM_CELLS_VERTICAL)
		{
			cell[i][j].x = i;
			cell[i][j].y = j;
			cell[i][j].alive = 0;
			cell[i][j].aliveNext = 0;
			cell[i][j].color = WHITE;
			cell[i][j].colorNext = WHITE;
			cell[i][j].score = 0;
			cell[i][j].scoreNext = 0;
			j++;
		}
		i++;
	}

    SDL_Window* window = SDL_CreateWindow("Grid Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Texture* bufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Texture* bufferTexture2 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    int quit = 0;
    SDL_Event e;
	int x = 0;
	int y = 0;
	int tmp = 300;
	int DELAY = 300;
	int w = CELLWIDTH;
	int h = CELLHEIGHT;
	static int x_rect;
	static int y_rect;
	int buttons = 0;
	int button = 0;
	int isPaused = 0;
	Uint32 lastTime = 0, currentTime;
	mousePos(&x, &y);
 	x =0;
	while(x < NUM_CELLS_HORIZONTAL)
	{
		y = 0;
		while (y < NUM_CELLS_VERTICAL)
		{
			if (cell[x][y].alive == 1)
				fillRect(renderer, cell[x][y].x*CELLWIDTH, cell[x][y].y*CELLHEIGHT);
			else
				voidRect(renderer, cell[x][y].x*CELLWIDTH, cell[x][y].y*CELLHEIGHT);
			y++;
		}
		x++;
	}
	drawGrid(renderer, cell, bufferTexture, bufferTexture2);
    while (!quit)
	{
        while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_KEYDOWN) 
			{
				if (e.key.keysym.sym == SDLK_ESCAPE) 
					quit = 1;
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					if (isPaused == 0)
						isPaused = 1;
					else
						isPaused = 0;
				}
			}
            if (e.type == SDL_QUIT) 
                quit = 1;
			if (e.type == SDL_MOUSEWHEEL)
			{
				if (e.wheel.y < 0)
				{
					if (DELAY >= 1500)
						break;
					else
						DELAY += 10;
					tmp = DELAY;
				}
				else if (e.wheel.y > 0)
				{
					if (DELAY <= 0)
						break;
					else
						DELAY -= 10;
					tmp = DELAY;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					//spawnRect(renderer, x, y, w, h);
					//colorClick(renderer, x, y, w, h, cell);
					buttons = 1;
					tmp = DELAY;
				}
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
				//	nocolorClick(renderer, x, y, w, h, cell);
					button = 1;
					tmp = DELAY;
				}
			}
			if ( e.type == SDL_MOUSEBUTTONUP)
			{
				if ( e.button.button == SDL_BUTTON_LEFT)
				{
					buttons = 0;
					DELAY = tmp;
				}
				if ( e.button.button == SDL_BUTTON_RIGHT)
				{
					button = 0;
					DELAY = tmp;
				}
			}
        }
		//if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT) && currentTime - lastTime >= 100)
		if ( buttons == 1 )
		{
			tmp = DELAY;
			DELAY = 10;
			mousePos(&x, &y);
			colorClick(renderer, x, y, w, h, cell);
		//	printf("x = %d, y = %d\n", cell[x/w][y/h].x, cell[x/w][y/h].y);
		}
		//if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT) && currentTime - lastTime >= 100)
		if ( button == 1 )
		{
			tmp = DELAY;
			DELAY = 10;
			mousePos(&x, &y);
			nocolorClick(renderer, x, y, w, h, cell);
		//	printf("x = %d, y = %d\n", cell[x/w][y/h].x, cell[x/w][y/h].y);
		}
		if (!buttons && button == 0 && isPaused == 0)
		{
			living(renderer, cell, bufferTexture, bufferTexture2);
		}
		DELAY = tmp;
		SDL_RenderPresent(renderer);
		SDL_Delay(DELAY);
	}

	i = 0;
	while (i < NUM_CELLS_VERTICAL)
	{
		free(cell[i]);
		cell[i] = NULL;
		i++;
	}
	free(cell);
    SDL_DestroyRenderer(renderer);
	//SDL_DestroyTexture(bufferTexture);
	//SDL_DestroyTexture(bufferTexture2);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
