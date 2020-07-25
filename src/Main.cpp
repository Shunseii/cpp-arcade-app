#include <iostream>
#include <SDL2/SDL.h>

#include "Utils/Vec2D.h"
#include "Graphics/Color.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;

void SetPixel(SDL_Surface* noptrWindowSurfacei, uint32_t color, int x, int y);
size_t GetIndex(SDL_Surface* noptrSurface, int r, int c);

int main(int argc, char* argv[]) {

	// Initialize SDL Video
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Error SDL_Init Failed" << std::endl;
		return 1;
	}
	
	// Create SDL window
	SDL_Window* optrWindow = SDL_CreateWindow(
			"Arcade", 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			0
	);

	if (optrWindow == nullptr) {
		std::cout << "Could not create window. Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Canvas
	SDL_Surface* noptrWindowSurface = SDL_GetWindowSurface(optrWindow);

	// Set pixel format of Color class to format used in the window surface	
	SDL_PixelFormat* pixelFormat = noptrWindowSurface->format;
	Color::InitColorFormat(pixelFormat);
	
	SetPixel(noptrWindowSurface, Color::Orange().GetPixelColor(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SDL_UpdateWindowSurface(optrWindow);

	SDL_Event sdlEvent;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
				case SDL_QUIT:
					running = false;
					break;
			}
		}
	}

	SDL_DestroyWindow(optrWindow);
	SDL_Quit();

	return 0;
}


void SetPixel(SDL_Surface* noptrWindowSurface, uint32_t color, int x, int y) {
	SDL_LockSurface(noptrWindowSurface);
	
	// 1D array of all pixels on surface
	uint32_t* pixels = (uint32_t*)noptrWindowSurface->pixels;

	// y -> row, x -> column
	size_t index = GetIndex(noptrWindowSurface, y, x);
	pixels[index] = color;
	
	SDL_UnlockSurface(noptrWindowSurface);
}

size_t GetIndex(SDL_Surface* noptrSurface, int r, int c) {
	// Convert from 1D array to 2D
	return r * noptrSurface->w + c;
}
