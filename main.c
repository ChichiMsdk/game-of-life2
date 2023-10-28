#include "SDL/include/SDL2/SDL_stdinc.h"
#include "life.h"


int	isMoving(int x, int y, int oldx, int oldy)
{
	if (x == oldx && y == oldy)
		return (0);
	printf("moved\n");
	return (1);
}

void	bouge(SDL_Rect *rect,int x,int y, int X_offset, int Y_offset)
{
	rect->x = x - X_offset;
	rect->y = y - Y_offset;
	if ( rect->x > 1900 || rect->x + rect->w > 1900)
		{
			rect->x = 1900 - rect->w;
		}
		if (rect->x <=0 )
		{
			rect->x = 0;
		}
		if (rect->y <= 0 )
		{
			rect->y = 0;
		}
		if ( rect->y > 1000 || rect->y + rect->h > 1000)
		{
			rect->y = 1000 - rect->h;
		}

}

Uint32 DELAY = 512;
Uint32 CELLWIDTH = (WINDOW_WIDTH / NUM_CELLS_HORIZONTAL);
Uint32 CELLHEIGHT = (WINDOW_HEIGHT / NUM_CELLS_VERTICAL);
Uint32 L_MOVE = 0;
Uint32 R_MOVE = 0;
Uint32 U_MOVE = 0;
Uint32 D_MOVE = 0;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
	if (TTF_Init() < 0)
		exit(1);
    (void)argc;
    (void)argv;

	
	int RECT1_X = 100;
	int RECT1_Y = 800;
	int RECT2_X = 400;
	int RECT2_Y = 10;
	char str[4];
	SDL_Color textColor = {255, 0, 0, 0};
	SDL_Rect Fontrect;
	Fontrect.x = 1800;
	Fontrect.y = 30;
	Fontrect.w = 100;
	Fontrect.h = 100;
	int troll = 1;

	SDL_itoa(DELAY, str, 10);
    SDL_Window* window = SDL_CreateWindow("Grid Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Font *font = TTF_OpenFont("JetBrainsMono-Bold.ttf", 24);
	if (!font)
		exit(1);
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

	SDL_Texture* bufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Texture* bufferTexture2 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_SetRenderTarget(renderer, bufferTexture2);
	SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);

    int quit = 0;
    SDL_Event e;
	int x = 0;
	int y = 0;
	int w = CELLWIDTH;
	int h = CELLHEIGHT;
	static int x_rect;
	static int y_rect;
	int buttons = 0;
	int button = 0;
	int isPaused = 0;
	Uint32 currentTime, lastUpdatedTime;
	Uint32 	startTime = 0;
	Uint32	displayTime = 3000000;
	mousePos(&x, &y);

 	x = 0;
	int hit1 = 0;
	int hit2 = 0;
    SDL_Texture *image1 = IMG_LoadTexture(renderer, "image6.png");
    SDL_Texture *image2 = IMG_LoadTexture(renderer, "image7.png");
    SDL_Rect rect1 = { RECT1_X, RECT1_Y, 50, 50 };  // x, y, width, height
    SDL_Rect rect2 = { RECT2_X, RECT2_Y, 657, 50 };  // x, y, width, height
													 //
	Uint32	tmp = DELAY;
	Uint32	counter = DELAY;
	int X_offset = y;
	int Y_offset = x;
	int resetting = 0;
	drawGrid(renderer, cell, bufferTexture, bufferTexture2);
	lastUpdatedTime = SDL_GetTicks64() + 100;

    while (!quit)
	{
		currentTime = SDL_GetTicks64() + 100;
		mousePos(&x, &y);
        while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_KEYDOWN) 
			{
				if (e.key.keysym.sym == SDLK_UP) 
				{
					CELLWIDTH += 1;
					CELLHEIGHT += 1;
					if (CELLWIDTH > 890 || CELLHEIGHT >890)
					{
						CELLWIDTH = 10;
						CELLHEIGHT = 10;
					}
					printf("CELLWIDTH = %d, CELLHEIGHT = %d\n", CELLWIDTH, CELLHEIGHT);
					goto zoom;
				}
				if (e.key.keysym.sym == SDLK_DOWN) 
				{
					CELLWIDTH -= 1;
					CELLHEIGHT -= 1;
					if (CELLWIDTH < 10 || CELLHEIGHT < 10)
					{
						CELLWIDTH = 890;
						CELLHEIGHT = 890;
					}
					printf("CELLWIDTH = %d, CELLHEIGHT = %d\n", CELLWIDTH, CELLHEIGHT);
					goto zoom;
				}
				if (e.key.keysym.sym == SDLK_f) 
				{
					CELLWIDTH = 10;
					CELLHEIGHT = 10;
					goto zoom;
				}
				if ( e.key.keysym.sym == SDLK_r)
				{
					reset(renderer, cell, bufferTexture, bufferTexture2);
					resetting = 1;
					isPaused = 0;
					printf("reset\n");
				}

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
					DELAY *= 2;
					if (DELAY >= 1000)
					{
						DELAY = 1000;
					}
					tmp = DELAY;
				}
				else if (e.wheel.y > 0)
				{
					DELAY /=2;
					if (DELAY <= 0)
					{
						DELAY = 1;
					}
					tmp = DELAY;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					//spawnRect(renderer, x, y, w, h);
					mousePos(&x, &y);
					tmp = DELAY;
					colorClick(renderer, x, y, CELLWIDTH, CELLHEIGHT, cell);
					printf("down\n");
				//	if ( x >= rect2.x && x<= rect2.x + rect2.w  && y >= rect2.y && y <= rect2.y + rect2.h)
				//	{
				//		mousePos(&x, &y);
				//		X_offset = x - rect2.x;
				//		Y_offset = y - rect2.y;
				//		hit2 = 1;
				//		rect2.x += 5;
				//		rect2.y += 5;
				//		rect2.w += 10;
				//		rect2.h += 10;
				//	}
				//	if ( x >= rect1.x && x<= rect1.x + rect1.w  && y >= rect1.y && y <= rect1.y + rect1.h)
				//	{
				//		mousePos(&x, &y);
				//		X_offset = x - rect1.x;
				//		Y_offset = y - rect1.y;
				//		hit1 = 1;
				//		rect1.x += 5;
				//		rect1.y += 5;
				//		rect1.w += 10;
				//		rect1.h += 10;
				//	}
					buttons = 1;
				}
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					colorClick(renderer, x, y, CELLWIDTH, CELLHEIGHT, cell);
					button = 1;
				}
			}
			if ( e.type == SDL_MOUSEBUTTONUP)
			{
				if ( e.button.button == SDL_BUTTON_LEFT)
				{
					mousePos(&x, &y);
					printf("up\n");
					buttons = 0;
					DELAY = tmp;
//					hit1 = 0;
//					hit2 = 0;
//					rect1.w = 50;
//					rect1.h = 50;
//					rect2.w = 657;
//					rect2.h = 50;
				}
				if ( e.button.button == SDL_BUTTON_RIGHT)
				{
					button = 0;
				}
			}
        }
		mousePos(&x, &y);
		if (resetting == 0)
		{
			SDL_SetRenderTarget(renderer, NULL);
			SDL_RenderCopy(renderer, bufferTexture2, NULL, NULL);
		}
		if ( buttons == 1)
		{
			DELAY = 1;
			mousePos(&x, &y);
			SDL_SetRenderTarget(renderer, bufferTexture);
			colorClick(renderer, x, y, CELLWIDTH, CELLHEIGHT, cell);
			SDL_SetRenderTarget(renderer, bufferTexture2);
			SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
			SDL_SetRenderTarget(renderer, NULL);
			SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
			
//			if ( hit1 == 1)
//			{
//				bouge(&rect1, x, y, X_offset, Y_offset);
//			}
//			mousePos(&x, &y);
//			if ( hit2 == 1)
//			{
//				bouge(&rect2, x, y, X_offset, Y_offset);
//			}
		}
		if ( button == 1 )
		{
			DELAY = 1;
			mousePos(&x, &y);
			SDL_SetRenderTarget(renderer, bufferTexture);
			nocolorClick(renderer, x, y, CELLWIDTH, CELLHEIGHT, cell);
			SDL_SetRenderTarget(renderer, bufferTexture2);
			SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
			SDL_SetRenderTarget(renderer, NULL);
			SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
		}
	if (!buttons && button == 0 && isPaused == 0)
	{
		if (currentTime - lastUpdatedTime > DELAY)
		{
		lastUpdatedTime = currentTime;
		DELAY = tmp;
zoom:
		SDL_SetRenderTarget(renderer, bufferTexture);
		living(renderer, cell, lastUpdatedTime, currentTime);
		SDL_SetRenderTarget(renderer, bufferTexture2);
		SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
		//living(renderer, cell, bufferTexture, bufferTexture2);
		}
	}
    	drawGrid(renderer, cell, bufferTexture2, bufferTexture2);
		counter = mapDelayToScale(DELAY);
		SDL_Texture *texture = fonting(renderer, font, Fontrect, str, counter); 
		SDL_RenderCopy(renderer, texture, NULL, &Fontrect);
		SDL_RenderCopy(renderer, texture, NULL, &Fontrect);
		SDL_DestroyTexture(texture);
//    	SDL_RenderClear(renderer);
//     	SDL_RenderCopy(renderer, image1, NULL, &rect1);
//      SDL_RenderCopy(renderer, image2, NULL, &rect2);
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
		SDL_RenderClear(renderer);
		resetting = 0;
	}

	i = 0;
	while (i < NUM_CELLS_VERTICAL)
	{
		free(cell[i]);
		cell[i] = NULL;
		i++;
	}
	free(cell);
	TTF_CloseFont(font);
    SDL_DestroyTexture(image1);
    SDL_DestroyTexture(image2);
	SDL_DestroyTexture(bufferTexture);
	SDL_DestroyTexture(bufferTexture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
	TTF_Quit();
    SDL_Quit();

    return 0;
}

int mapDelayToScale(Uint32 delay)
{
    int scale_position = 0;

    if (delay == 1000) {
        scale_position = 1;
    } else if (delay == 512) {
        scale_position = 2;
    } else {
        scale_position = 3 + (int) (log2(512) - log2(delay));
    }
    
    return scale_position;
}

Uint32 mapScaleToDelay(int scale_position) 
{
    Uint32 delay;

    if (scale_position == 12) {
        delay = 1000;
    } else if (scale_position == 11) {
        delay = 512;
    } else {
        delay = (Uint32) pow(2, log2(512) - (10 - scale_position));
    }

    return delay;
}

void	reset(SDL_Renderer *renderer, s_cell **cell, SDL_Texture *bufferTexture, SDL_Texture *bufferTexture2)
{
	SDL_Rect Fontrect;

	int i = 0;
	int j = 0;
	SDL_SetRenderTarget(renderer, bufferTexture2);
	while (i < NUM_CELLS_HORIZONTAL)
	{
		j = 0;
		while (j < NUM_CELLS_VERTICAL)
		{
			cell[i][j].alive = 0;
			cell[i][j].aliveNext = 0;
			cell[i][j].color = WHITE;
			cell[i][j].colorNext = WHITE;
			cell[i][j].score = 0;
			cell[i][j].scoreNext = 0;
			j++;
			voidRect(renderer, cell[i][j].x*CELLWIDTH, cell[i][j].y*CELLHEIGHT);
		}
		i++;
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
}
