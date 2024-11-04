#pragma once
#include <format>

namespace plotpp{
	class Color{
	public:
		constexpr Color() = default;
		
		constexpr Color(uint8_t red, uint8_t green, uint8_t blue)
			: red_(red)
			, green_(green)
			, blue_(blue)
		{}
		
		constexpr Color(uint32_t rgb) 
			: Color((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF)
		{}
		
		constexpr uint8_t red() const {return this->red_;}
		constexpr uint8_t green() const {return this->green_;}
		constexpr uint8_t blue() const {return this->blue_;}
		
		constexpr Color& red(uint8_t red) {this->red_ = red; return *this;}
		constexpr Color& green(uint8_t green) {this->green_ = green; return *this;}
		constexpr Color& blue(uint8_t blue) {this->blue_ = blue; return *this;}

		inline std::string to_hex() const {
			return std::format("{:02x}{:02x}{:02x}", this->red(), this->green(), this->blue());
		}
		
	private:
		uint8_t red_ = 0;
		uint8_t green_ = 0;
		uint8_t blue_ = 0;
	};
	
	
	// Many thanks to : https://github.com/Gnuplotting/gnuplot-palettes
	// For the Color Palettes
	
	constexpr std::array<Color, 9> magma{0x000004, 0x1c1044, 0x4f127b, 0x812581, 0xb5367a, 0xe55964, 0xfb8761, 0xfec287, 0xfbfdbf};
	constexpr std::array<Color, 9> inferno{0x000004, 0x1f0c48, 0x550f6d, 0x88226a, 0xa83655, 0xe35933, 0xf9950a, 0xf8c932, 0xfcffa4};
	constexpr std::array<Color, 9> viridis{0x440154, 0x472c7a, 0x3b518b, 0x2c718e, 0x21908d, 0x27ad81, 0x5cc863, 0xaadc32, 0xfde725};
}