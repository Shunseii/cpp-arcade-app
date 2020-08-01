#include <iostream>
#include <SDL2/SDL.h>

#include "Graphics/Color.h"
#include "Graphics/Screen.h"
#include "Shapes/Line2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/AARectangle.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 1;

int main(int argc, char* argv[]) {
	Screen theScreen;
	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
	
	/*
	Line2D line{Vec2D(0,0), Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT)};
	theScreen.Draw(line, Color::Yellow());
	theScreen.SwapScreens();	
	*/
	
	/*
	Triangle triangle{Vec2D(SCREEN_WIDTH / 2, 10), Vec2D(10, SCREEN_HEIGHT / 2), Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)};
	theScreen.Draw(triangle, Color::Blue());
	theScreen.SwapScreens();	
	*/

	AARectangle rect{Vec2D(20, 50), 50, 100};
	theScreen.Draw(rect, Color::Red());
	theScreen.SwapScreens();	
	
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

	return 0;
}
