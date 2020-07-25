#ifndef GRAPHICS_SCREEN_BUFFER_H
#define GRAPHICS_SCREEN_BUFFER_H

#include <cstddef>
#include <stdint.h>
#include "Graphics/Color.h"

/*
 * ScreenBuffer class wraps SDL_Surface object
 *   and provides functionality for pixel
 *   manipulation on an SDL_Surface.
 */

struct SDL_Surface;

class ScreenBuffer {
	private:
		SDL_Surface* mSurface;
		size_t GetIndex(int r, int c);
	
	public:
		ScreenBuffer();
		ScreenBuffer(const ScreenBuffer&);
		~ScreenBuffer();

		ScreenBuffer& operator=(const ScreenBuffer&); 

		void Init(uint32_t format, uint32_t width, uint32_t height);

		inline SDL_Surface* GetSurface() {return mSurface;}

		void Clear(const Color& c = Color::Black());
		void SetPixel(const Color&, int x, int y);
};

#endif
