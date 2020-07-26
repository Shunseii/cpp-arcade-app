#include "Graphics/Screen.h"

#include <SDL2/SDL.h>
#include <cassert>
#include "Utils/Vec2D.h"

Screen::Screen(): 
	mWidth(0), 
	mHeight(0), 
	moptrWindow(nullptr), 
	mnoptrSurface(nullptr) {}

Screen::~Screen() {	
	if (moptrWindow) {
		SDL_DestroyWindow(moptrWindow);
		moptrWindow = nullptr;
	}

	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag) {	
	// Initialize SDL Video
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Error SDL_Init Failed" << std::endl;
		return nullptr;
	}
	
	mWidth = w;
	mHeight = h;

	// Create SDL window
	moptrWindow = SDL_CreateWindow(
			"Arcade", 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED,
			mWidth * mag,
			mHeight * mag,
			0
	);

	if (moptrWindow) {
		// Canvas
		mnoptrSurface = SDL_GetWindowSurface(moptrWindow);
	
		// Set pixel format of Color class to format used in the window surface	
		SDL_PixelFormat* pixelFormat = mnoptrSurface->format;
		Color::InitColorFormat(pixelFormat);

		mClearColor = Color::Black();

		mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
		mBackBuffer.Clear(mClearColor);
	}

	return moptrWindow;
}

void Screen::SwapScreens() {
	assert(moptrWindow);
	if (moptrWindow) {
		ClearScreen();
		
		// Scales up to match the magnification of the window surface
		SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrSurface, nullptr);
		SDL_UpdateWindowSurface(moptrWindow);

		mBackBuffer.Clear(mClearColor);
	}
}

void Screen::ClearScreen() {	
	assert(moptrWindow);
	if (moptrWindow) {
		SDL_FillRect(mnoptrSurface, nullptr, mClearColor.GetPixelColor());
	}
}

void Screen::Draw(int x, int y, const Color& color) {	
	assert(moptrWindow);
	if (moptrWindow) {
		mBackBuffer.SetPixel(color, x, y);
	}
}

void Screen::Draw(const Vec2D& point, const Color& color) {	
	assert(moptrWindow);
	if (moptrWindow) {
		mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
	}
}
