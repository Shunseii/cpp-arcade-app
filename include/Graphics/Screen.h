#ifndef GRAPHICS_SCREEN_H
#define GRAPHICS_SCREEN_H

#include <stdint.h>
#include "Graphics/ScreenBuffer.h"
#include "Graphics/Color.h"

class Vec2D;
class Line2D;
class Triangle;

struct SDL_Window;
struct SDL_Surface;

/*
 * Class that wraps a window and window surface to
 *   astract drawing functionality on the screen.
 */
class Screen {
	private:
		// Prevent copying
		Screen(const Screen&);
		Screen& operator=(const Screen&);

		void ClearScreen();

		uint32_t mWidth, mHeight;
		
		Color mClearColor;
		ScreenBuffer mBackBuffer;

		SDL_Window* moptrWindow;
		SDL_Surface* mnoptrSurface;

	public:
		Screen();
		~Screen();

		SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
		void SwapScreens();

		inline void SetClearColor(const Color& clearColor) {mClearColor = clearColor;}
		inline uint32_t Width() const {return mWidth;}
		inline uint32_t Height() const {return mHeight;}

		// Draw Methods
		void Draw(int x, int y, const Color&);
		void Draw(const Vec2D& point, const Color&);
		void Draw(const Line2D&, const Color&);
		void Draw(const Triangle&, const Color&);
};

#endif
