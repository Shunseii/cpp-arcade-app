#include "Graphics/Screen.h"

#include <SDL2/SDL.h>
#include <cassert>
#include <cmath>
#include "Utils/Vec2D.h"
#include "Shapes/Line2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/AARectangle.h"

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

void Screen::Draw(const Line2D& line, const Color& color) {
	assert(moptrWindow);
	if (moptrWindow) {
		int dx, dy;

		int x0 = roundf(line.GetP0().GetX());
		int y0 = roundf(line.GetP0().GetY());	
		int x1 = roundf(line.GetP1().GetX());
		int y1 = roundf(line.GetP1().GetY());

		dx = x1 - x0;
		dy = y1 - y0;

		signed const char incrX((dx > 0) - (dx < 0)); // gives 1 or -1
		signed const char incrY((dy > 0) - (dy < 0));

		// Removes floating point
		dx = abs(dx) * 2;
		dy = abs(dy) * 2;
		
		// Draw first point of the line
		Draw(x0, y0, color);

		if (dx >= dy) { // Move in the x direction
			// Decision parameter
			int d = dy - dx / 2;

			while (x0 != x1) {
				if (d >= 0) {
					d -= dx;
					y0 += incrY;
				}

				d += dy;
				x0 += incrX;

				Draw(x0, y0, color);
			}
		} else { // Move in the y direction
			int d = dx - dy / 2;

			while (y0 != y1) {
				if (d >= 0) {
					d -= dy;
					x0 += incrX;
				}

				d += dx;
				y0 += incrY;

				Draw(x0, y0, color);
			}
		}
	}
}


void Screen::Draw(const Triangle& triangle, const Color& color) {
	Line2D lineP0ToP1 = Line2D(triangle.GetP0(), triangle.GetP1());
	Line2D lineP1ToP2 = Line2D(triangle.GetP1(), triangle.GetP2());
	Line2D lineP0ToP2 = Line2D(triangle.GetP0(), triangle.GetP2());

	Draw(lineP0ToP1, color);	
	Draw(lineP1ToP2, color);
	Draw(lineP0ToP2, color);
}

void Screen::Draw(const AARectangle& rect, const Color& color) {
	std::vector<Vec2D> points = rect.GetPoints();
	
	Line2D top = Line2D(points[0], points[1]);
	Line2D right = Line2D(points[1], points[2]);
	Line2D bottom = Line2D(points[2], points[3]);
	Line2D left = Line2D(points[0], points[3]);

	Draw(top, color);
	Draw(right, color);
	Draw(bottom, color);
	Draw(left, color);
}
