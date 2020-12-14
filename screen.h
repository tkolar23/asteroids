#pragma once
#include <SDL.h>
#include <string>

// starts up SDL and creates window
bool init(SDL_Window** window_ptr, SDL_Renderer** renderer_ptr);

// loads media
bool load_image(SDL_Window* win, SDL_Renderer* ren, SDL_Texture** tex_ptr, std::string filename);

// frees media and shurts down SDL
void cleanup(SDL_Window* win, SDL_Renderer* ren, SDL_Texture* tex);
