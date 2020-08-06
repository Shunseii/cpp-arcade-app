#include "Graphics/Screen.h"

#include <SDL2/SDL.h>
#include <cassert>
#include <cmath>
#include <algorithm>
#include "Utils/Vec2D.h"
#include "Utils/Utils.h"
#include "Shapes/Line2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/AARectangle.h"
#include "Shapes/Circle.h"

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
		// SDL_PixelFormat* pixelFormat = mnoptrSurface->format; // returns RGB8888 format which ignores alpha channel
		SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
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

void Screen::FillPoly(const std::vector<Vec2D>& points, const Color& color) {
	if (points.size() > 0) {
		float top = points[0].GetY();
		float bottom = points[0].GetY();
		float right = points[0].GetX();
		float left = points[0].GetX();

		for (size_t i = 1; i < points.size(); ++i) {
			if (points[i].GetY() < top) {
				top = points[i].GetY();
			}
			
			if (points[i].GetY() > bottom) {
				bottom = points[i].GetY();
			}
			
			if (points[i].GetX() > right) {
				right = points[i].GetX();
			}
			
			if (points[i].GetX() < left) {
				left = points[i].GetX();
			}
		}

		for (int pixelY = top; pixelY < bottom; ++pixelY) {
			std::vector<float> nodeXVec;
			size_t j = points.size() - 1;

			for (size_t i = 0; i < points.size(); ++i) {
				float pointiY = points[i].GetY();
				float pointjY = points[j].GetY();

				if ((pointiY <= (float)pixelY && pointjY > (float)pixelY) || 
						(pointjY <= (float)pixelY && pointiY > (float)pixelY)) {
					float denom = pointjY - pointiY;

					if (IsEqual(denom, 0)) {
						continue;
					}

					float x = points[i].GetX() + (pixelY - pointiY) / (denom) * 
						(points[j].GetX() - points[i].GetX());
					nodeXVec.push_back(x);
				}

				j = i;
			}	
			std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());
		
			for (size_t k = 0; k < nodeXVec.size(); k += 2) {
				if (nodeXVec[k] > right) {
					break;
				}

				if (nodeXVec[k + 1] > left) {
					if (nodeXVec[k] < left) {
						nodeXVec[k] = left;
					}

					if (nodeXVec[k + 1] > right) {
						nodeXVec[k + 1] = right;
					}

					for (int pixelX = nodeXVec[k]; pixelX < nodeXVec[k + 1]; ++pixelX) {
						Draw(pixelX, pixelY, color);
					}
				} 
			}
		}
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


void Screen::Draw(const Triangle& triangle, const Color& color, 
				bool fill, const Color& fillColor) {
	if (fill) {
		FillPoly(triangle.GetPoints(), fillColor);
	}
	
	Line2D lineP0ToP1 = Line2D(triangle.GetP0(), triangle.GetP1());
	Line2D lineP1ToP2 = Line2D(triangle.GetP1(), triangle.GetP2());
	Line2D lineP0ToP2 = Line2D(triangle.GetP0(), triangle.GetP2());

	Draw(lineP0ToP1, color);	
	Draw(lineP1ToP2, color);
	Draw(lineP0ToP2, color);
}

void Screen::Draw(const AARectangle& rect, const Color& color, 
				bool fill, const Color& fillColor) {
	if (fill) {
		FillPoly(rect.GetPoints(), fillColor);
	}
	
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

void Screen::Draw(const Circle& circle, const Color& color, 
				bool fill, const Color& fillColor) {
	static unsigned int NUM_CIRCLE_SEGMENTS = 300;

	std::vector<Vec2D> circlePoints;
	std::vector<Line2D> lines;

	float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);

	Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), 
			circle.GetCenterPoint().GetY());
	Vec2D p1 = p0;
	Line2D nextLineToDraw;

	for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; ++i) {
		p1.Rotate(angle, circle.GetCenterPoint());
		nextLineToDraw.SetP1(p1);
		nextLineToDraw.SetP0(p0);

		lines.push_back(nextLineToDraw);
		circlePoints.push_back(p0);
		p0 = p1;
	}

	if (fill) {
		FillPoly(circlePoints, fillColor);
	}

	for (const Line2D& line : lines) {
		Draw(line, color);
	}
}


