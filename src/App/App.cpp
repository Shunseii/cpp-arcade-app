#include "App/App.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>

#include "Scenes/ArcadeScene.h"
#include "Scenes/GameScene.h"
#include "Games/Breakout/Breakout.h"

App& App::Singleton() {
	static App theApp;
	return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag) {
	mnoptrWindow = mScreen.Init(width, height, mag);
	
	// std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();
	// PushScene(std::move(arcadeScene));
	
	// Temp
	std::unique_ptr<Breakout> breakoutGame = std::make_unique<Breakout>();
	std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));

	PushScene(std::move(breakoutScene));

	return mnoptrWindow != nullptr;
}

void App::Run() {
	if (mnoptrWindow) {
		bool running = true;

		uint32_t lastTick = SDL_GetTicks(); // Number of ms since SDL initialization
		uint32_t currentTick = lastTick;

		uint32_t dt = 10; // Update in 10 ms intervals
		uint32_t accumulator = 0;

		mInputController.Init([&running](uint32_t dt, InputState state){
			running = false;
		});

		while (running) {
			currentTick = SDL_GetTicks();
			uint32_t frameTime = currentTick - lastTick; // Number of frames since last tick

			if (frameTime > 300) {
				frameTime = 300;
			}

			lastTick = currentTick;
			accumulator += frameTime; // Number of ticks in total

			// Input
			mInputController.Update(dt);

			Scene* topScene = App::TopScene();

			assert(topScene && "Should have a scene");
			if (topScene) {
				// Update
				while (accumulator >= dt) {
					// Update current scene by dt (10 ms intervals)
					topScene->Update(dt);
					accumulator -= dt;
				}

				// Render 
				topScene->Draw(mScreen);
			}

			mScreen.SwapScreens();
		}
	}
}

void App::PushScene(std::unique_ptr<Scene> scene) {
	assert(scene && "Don't push nullptr");
	if (scene) {
		scene->Init();

		mInputController.SetGameController(scene->GetGameController());
		mSceneStack.emplace_back(std::move(scene)); // Moves scene instead of copy	
		SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
	}
}

void App::PopScene() {
	if (mSceneStack.size() > 1) {
		mSceneStack.pop_back();
	}

	if (TopScene()) {
		mInputController.SetGameController(TopScene()->GetGameController());
		SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
	}
}

Scene* App::TopScene() {
	if (mSceneStack.empty()) {
		return nullptr;
	}

	return mSceneStack.back().get();
}

const std::string& App::GetBasePath() {
	static std::string basePath = SDL_GetBasePath();
	return basePath;
}
