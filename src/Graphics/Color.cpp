#include "Graphics/Color.h"
#include <SDL2/SDL.h>

const SDL_PixelFormat* Color::mFormat = nullptr;

void Color::InitColorFormat(const SDL_PixelFormat* format) {
	Color::mFormat = format;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SetRGBA(r, g, b, a);
}

void Color::SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	mColor = SDL_MapRGBA(mFormat, r, g, b, a);
}

void Color::SetRed(uint8_t red) {
	uint8_t r, g, b, a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	SetRGBA(red, g, b, a);
}

void Color::SetGreen(uint8_t green) {
	uint8_t r, g, b, a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	SetRGBA(r, green, b, a);
}

void Color::SetBlue(uint8_t blue) {
	uint8_t r, g, b, a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	SetRGBA(r, g, blue, a);
}

void Color::SetAlpha(uint8_t alpha) {
	uint8_t r, g, b, a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	SetRGBA(r, g, b, alpha);
}

uint8_t Color::GetRed() const {
	uint8_t r, g, b, a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	return r;
}

uint8_t Color::GetGreen() const {
	uint8_t r, g, b, a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	return g;
}

uint8_t Color::GetBlue() const {
	uint8_t r, g, b, a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	return b;
}

uint8_t Color::GetAlpha() const {
	uint8_t r, g, b, a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	return a;
}

Color Color::Evaluate1MinusSourceAlpha(
		const Color& source, const Color& dest) {
	uint8_t alpha = source.GetAlpha();

	float sourceAlpha = float(alpha) / 255.0f;
	float destAlpha = 1.0f - sourceAlpha;

	Color outColor;

	outColor.SetAlpha(255);
	outColor.SetRed(float(source.GetRed()) * sourceAlpha + 
			dest.GetRed() * destAlpha);

	outColor.SetBlue(float(source.GetBlue()) * sourceAlpha + 
			dest.GetBlue() * destAlpha);
	
	outColor.SetGreen(float(source.GetGreen()) * sourceAlpha + 
			dest.GetGreen() * destAlpha);
	
	return outColor;
}
