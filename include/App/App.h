#ifndef APP_APP_H
#define APP_APP_H

#include <stdint.h>

#include "Graphics/Screen.h"

struct SDL_WINDOW;

class App {
	private:
		Screen mScreen;
		SDL_Window* mnoptrWindow;

	public:
		static App& Singleton();
		bool Init(uint32_t width, uint32_t height, uint32_t mag);
		void Run();

		inline uint32_t GetWidth() const { return mScreen.Width(); }
		inline uint32_t GetHeight() const { return mScreen.Height(); }
};

#endif
