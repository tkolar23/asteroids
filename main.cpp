#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include <string>

// Screen dimension constants
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

// key press constants
enum key_press_surfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

int main(int argc, char* argv[]) {

	// initialize the window and the renderer
	SDL_Window* win = nullptr;
	SDL_Renderer* ren = nullptr;
	if (init(&win, &ren) == EXIT_FAILURE) return EXIT_FAILURE;

	// load up the texture
	SDL_Texture* tex = nullptr;
	if (load_image(win, ren, &tex, "C:\\Users\\Tomas\\source\\projects\\asteroids\\x64\\Debug\\hello.bmp") == EXIT_FAILURE) return EXIT_FAILURE;

	// Main loop flag, and the event handler
	bool quit = false;
	SDL_Event e;

	// handling events
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			// user requests quit
			if (e.type == SDL_QUIT) quit = true;
		}

		// clear renderer
		SDL_RenderClear(ren);

		// Draw texture
		SDL_RenderCopy(ren, tex, NULL, NULL);

		// Update screen
		SDL_RenderPresent(ren);

		// small break
		SDL_Delay(10);
	}

	cleanup(win, ren, tex);

	return EXIT_SUCCESS;
}