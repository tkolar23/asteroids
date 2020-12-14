#include "screen.h"
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

// starts up SDL, creates windows, creates renderer
bool init(SDL_Window** window_ptr, SDL_Renderer** renderer_ptr)
{
	// initialize
	if (SDL_Init(SDL_INIT_VIDEO) != 0)	// successful init only if 0 is returned
	{
		fprintf(stderr, "SDL_Init Error: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	// create window
	SDL_Window* win = SDL_CreateWindow("Asteroids", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	*window_ptr = win;

	if (win == nullptr)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	// create renderer
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	*renderer_ptr = ren;

	if (ren == nullptr)
	{
		SDL_DestroyWindow(win);
		fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;

	}

	return EXIT_SUCCESS;
}

// render BMP image, and then load BMP image
bool load_image(SDL_Window* win, SDL_Renderer* ren, SDL_Texture** tex_ptr, std::string filename)
{
	SDL_Surface* bmp = SDL_LoadBMP(filename.c_str());

	if (bmp == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		fprintf(stderr, "SDL_LoadBMP Error: %s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
	*tex_ptr = tex;
	SDL_FreeSurface(bmp);	// done with original surface

	if (tex == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}

// frees media and shuts down SDL
void cleanup(SDL_Window* win, SDL_Renderer* ren, SDL_Texture* tex)
{
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
