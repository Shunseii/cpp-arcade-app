#include <iostream>
#include <SDL2/SDL.h>

#include "Graphics/Color.h"
#include "Graphics/Screen.h"
#include "Shapes/Line2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/AARectangle.h"
#include "Shapes/Circle.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 1;

int main(int argc, char* argv[]) {
	Screen theScreen;
	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
		
	Triangle triangle{Vec2D(SCREEN_WIDTH / 2, 10), Vec2D(10, SCREEN_HEIGHT / 2), Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)};
	theScreen.Draw(triangle, Color::Blue(), true, Color::Blue());

	Circle circle{Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 50};
	theScreen.Draw(circle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
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
