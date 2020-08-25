#include "App/App.h"

#include <SDL2/SDL.h>
#include <iostream>

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
		SDL_Event sdlEvent;
		bool running = true;

		uint32_t lastTick = SDL_GetTicks(); // Number of ms since SDL initialization
		uint32_t currentTick = lastTick;

		uint32_t dt = 10; // Update in 10 ms intervals
		uint32_t accumulator = 0;

		while (running) {
			currentTick = SDL_GetTicks();
			uint32_t frameTime = currentTick - lastTick; // Number of frames since last tick

			if (frameTime > 300) {
				frameTime = 300;
			}

			lastTick = currentTick;
			accumulator += frameTime; // Number of ticks in total

			// Input
			while (SDL_PollEvent(&sdlEvent)) {
				switch (sdlEvent.type) {
					case SDL_QUIT:
						running = false;
						break;
				}
			}
			
			// Update
			while (accumulator >= dt) {
				// Update current scene by dt (10 ms intervals)
				accumulator -= dt;
			}

			// Render 
			Triangle triangle{Vec2D(mScreen.Width() / 2, 10), Vec2D(10, mScreen.Height() / 2), Vec2D(mScreen.Width() / 2, mScreen.Height() / 2)};
			mScreen.Draw(triangle, Color::Blue(), true, Color::Blue());
			Circle circle{Vec2D(mScreen.Width() / 2, mScreen.Height() / 2), 50};
			mScreen.Draw(circle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));

			mScreen.SwapScreens();
		}
	}
}

