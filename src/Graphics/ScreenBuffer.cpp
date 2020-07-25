#include "Graphics/ScreenBuffer.h"

#include <SDL2/SDL.h>
#include <cassert>

// Converts given 2D (r, c) coordinate of an array
//   to a 1D representation of a 2D array.
size_t ScreenBuffer::GetIndex(int r, int c) {	
	assert(mSurface);
	
	if (mSurface) {
		// Convert from 1D array to 2D
		return r * mSurface->w + c;
	}

	return 0;
}

ScreenBuffer::ScreenBuffer(): mSurface(nullptr) {}

ScreenBuffer::ScreenBuffer(const ScreenBuffer& sb) {
	SDL_Surface* sbSurface = sb.mSurface;
	
	// Allocates an RGB surface with same format as sbSurface
	mSurface = SDL_CreateRGBSurfaceWithFormat(
			0, 
			sbSurface->w, 
			sbSurface->h, 
			0, 
			sbSurface->format->format
	);
	
	// Copy all the pixels from sbSurface to mSurface
	SDL_BlitSurface(sbSurface, nullptr, mSurface, nullptr);
}

ScreenBuffer::~ScreenBuffer() {
	if (mSurface) {
		SDL_FreeSurface(mSurface);
	}
}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& sb) {
	if (this == &sb) {
		return *this;
	}

	if (mSurface != nullptr) {
		SDL_FreeSurface(mSurface);
		mSurface = nullptr;
	}
	
	if (sb.mSurface != nullptr) {		
		SDL_Surface* sbSurface = sb.mSurface;
		
		// Allocates an RGB surface with same format as sbSurface
		mSurface = SDL_CreateRGBSurfaceWithFormat(
				0, 
				sbSurface->w, 
				sbSurface->h, 
				0, 
				sbSurface->format->format
		);
		
		// Copy all the pixels from sbSurface to mSurface
		SDL_BlitSurface(sbSurface, nullptr, mSurface, nullptr);
	}

	return *this;
} 

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t height) {	
	mSurface = SDL_CreateRGBSurfaceWithFormat(
			0, width, height, 0, format);
	Clear();
}

void ScreenBuffer::Clear(const Color& c) {
	assert(mSurface);
	if (mSurface) {
		SDL_FillRect(mSurface, nullptr, c.GetPixelColor());
	}
}

// Sets pixel at (x, y) to given color.
void ScreenBuffer::SetPixel(const Color& color, int x, int y) {
	assert(mSurface);
	
	if (mSurface && 
			(y < mSurface->h && y > 0) && 
			(x < mSurface->w && x > 0)) {
		SDL_LockSurface(mSurface);
		
		// 1D array of all pixels on surface
		uint32_t* pixels = (uint32_t*)mSurface->pixels;

		// y -> row, x -> column
		size_t index = GetIndex(y, x);
		pixels[index] = color.GetPixelColor();
		
		SDL_UnlockSurface(mSurface);
	}
}
