#include "App/App.h"

#include <SDL2/SDL.h>

#include "Shapes/Line2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/AARectangle.h"
#include "Shapes/Circle.h"
#include "Graphics/Color.h"

App& App::Singleton() {
	static App theApp;
	return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag) {
	mnoptrWindow = mScreen.Init(width, height, mag);
	return mnoptrWindow != nullptr;
}

void App::Run() {
	if (mnoptrWindow) {
		Triangle triangle{Vec2D(mScreen.Width() / 2, 10), Vec2D(10, mScreen.Height() / 2), Vec2D(mScreen.Width() / 2, mScreen.Height() / 2)};
		mScreen.Draw(triangle, Color::Blue(), true, Color::Blue());

		Circle circle{Vec2D(mScreen.Width() / 2, mScreen.Height() / 2), 50};
		mScreen.Draw(circle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
		mScreen.SwapScreens();	

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
	}
}

