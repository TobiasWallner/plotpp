#pragma once
#include <format>
#include <algorithm>

namespace plotpp{
	class Color{
	public:
		constexpr Color() = default;
		
		constexpr Color(uint8_t red, uint8_t green, uint8_t blue)
			: red_(red/255.f)
			, green_(green/255.f)
			, blue_(blue/255.f){}
			
		constexpr Color(int red, int green, int blue)
			: red_(red/255.f)
			, green_(green/255.f)
			, blue_(blue/255.f){}
			
		constexpr Color(float red, float green, float blue)
			: red_(std::max(std::min(red, 1.f), 0.f))
			, green_(std::max(std::min(green, 1.f), 0.f))
			, blue_(std::max(std::min(blue, 1.f), 0.f)){}
			
		constexpr Color(double red, double green, double blue)
			: Color(static_cast<float>(red), static_cast<float>(green), static_cast<float>(blue)) {}
		
		constexpr Color(uint32_t rgb) 
			: Color(
				static_cast<uint8_t>((rgb >> 16) & 0xFF), 
				static_cast<uint8_t>((rgb >> 8) & 0xFF), 
				static_cast<uint8_t>(rgb & 0xFF)){}
		
		constexpr uint8_t red_ui8() const {return static_cast<uint8_t>(this->red_ * 255);}
		constexpr uint8_t green_ui8() const {return static_cast<uint8_t>(this->green_ * 255);}
		constexpr uint8_t blue_ui8() const {return static_cast<uint8_t>(this->blue_ * 255);}
		
		constexpr float redf() const {return this->red_;}
		constexpr float greenf() const {return this->green_;}
		constexpr float bluef() const {return this->blue_;}
		
		constexpr Color& red(uint8_t red) {this->red_ = red; return *this;}
		constexpr Color& green(uint8_t green) {this->green_ = green; return *this;}
		constexpr Color& blue(uint8_t blue) {this->blue_ = blue; return *this;}

		constexpr std::int32_t to_int32() const {
			const std::int32_t red = this->red_ui8();
			const std::int32_t green = this->green_ui8();
			const std::int32_t blue = this->blue_ui8();
			const std::int32_t result = red << 16 | green << 8 | blue;
			return result;
		}

		inline std::string to_hex() const {
			return std::format("{:02x}{:02x}{:02x}", this->red_ui8(), this->green_ui8(), this->blue_ui8());
		}
		
	private:
		float red_ = 0;
		float green_ = 0;
		float blue_ = 0;
	};
	
	constexpr Color operator + (const Color& l, const Color& r){
		return Color(l.redf() + r.redf(), l.greenf() + r.greenf(), l.bluef() + r.bluef());
	}
	
	constexpr Color operator - (const Color& l, const Color& r){
		return Color(l.redf() - r.redf(), l.greenf() - r.greenf(), l.bluef() - r.bluef());
	}
	
	constexpr Color operator * (const Color& l, const Color& r){
		return Color(l.redf() * r.redf(), l.greenf() * r.greenf(), l.bluef() * r.bluef());
	}
	
	constexpr Color operator * (const Color& l, const float& r){
		return Color(l.redf() * r, l.greenf() * r, l.bluef() * r);
	}
	
	constexpr Color operator * (const float& l, const Color& r){
		return Color(l * r.redf(), l * r.greenf(), l * r.bluef());
	}
	
	constexpr Color blend(const Color& a, const Color& b, const float& t){
		/* 
			linearly interpolates from color a to color b
				a   -------> b
			t:	0.0 -------> 1.0
		*/
		return b * t + a * (1 - t);
	}
	
	template<size_t N>
	constexpr Color map(const float& v, const std::array<Color, N>& color_map){
		/*
			linearly interpolates into the color_map
				color_map.front() -----> color_map.back()
			v:	0.0 -------------------> 1.0
		*/
		const float k = (color_map.size() - 1) * v;
		const int bucket = static_cast<int>(k);
		if(bucket == color_map.size()-1) return color_map.back();
		return blend(color_map[bucket], color_map[bucket+1], k - bucket);
	}
}