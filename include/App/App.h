#ifndef APP_APP_H
#define APP_APP_H

#include <stdint.h>
#include <vector>
#include <memory>
#include "Scenes/Scene.h"
#include "Graphics/Screen.h"

struct SDL_WINDOW;

class App {
	private:
		Screen mScreen;
		SDL_Window* mnoptrWindow;
	
		std::vector<std::unique_ptr<Scene>> mSceneStack;

	public:
		static App& Singleton();
		bool Init(uint32_t width, uint32_t height, uint32_t mag);
		void Run();

		inline uint32_t GetWidth() const { return mScreen.Width(); }
		inline uint32_t GetHeight() const { return mScreen.Height(); }

		void PushScene(std::unique_ptr<Scene> scene);
		void PopScene();
		Scene* TopScene();
};

#endif
