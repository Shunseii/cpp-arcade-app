#ifndef GRAPHICS_COLOR_H
#define GRAPHICS_COLOR_H

#include <stdint.h>

struct SDL_PixelFormat;

/*
 * Color Class which handles converting between
 * 	 SDL pixel format of the window and RGBA.
 */

class Color {
	private:
		uint32_t mColor;
	
	public:
		// Must initialize to use specific color format
		static const SDL_PixelFormat* mFormat;
		static void InitColorFormat(const SDL_PixelFormat* format);
	
		// Preset colors
		static Color Black() {return Color(0, 0, 0, 255);}
		static Color White() {return Color(255, 255, 255, 255);}
		static Color Red() {return Color(255, 0, 0, 255);}
		static Color Blue() {return Color(0, 0, 255, 255);}
		static Color Green() {return Color(0, 255, 0, 255);}
		static Color Yellow() {return Color(255, 255, 0, 255);}
		static Color Magenta() {return Color(255, 0, 255, 255);}
		static Color Cyan() {return Color(0, 255, 255, 255);}
		static Color Orange() {return Color(255, 150, 0, 255);}

		Color(): mColor(0) {}
		Color(uint32_t color): mColor(color) {}
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		
		inline bool operator==(const Color& c) const {return mColor == c.mColor;}
		inline bool operator!=(const Color& c) const {return !(*this == c);}
		inline uint32_t GetPixelColor() const {return mColor;}

		void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		void SetRed(uint8_t red);
		void SetGreen(uint8_t green);
		void SetBlue(uint8_t blue);
		void SetAlpha(uint8_t alpha);

		uint8_t GetRed(uint8_t red) const;
		uint8_t GetGreen(uint8_t green) const;
		uint8_t GetBlue(uint8_t blue) const;
		uint8_t GetAlpha(uint8_t alpha) const;
};

#endif
