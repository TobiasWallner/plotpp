#pragma once

#include <ostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <optional>

#include "plotpp/IPlot.hpp"
#include "plotpp/Color.hpp"
#include "optional_ptr.hpp"
#include "plotpp/concepts.hpp"
#include "plotpp/LineType.hpp"
#include "plotpp/FillStyle.hpp"


namespace plotpp{

	class Circle : public IPlot{
	public:
	
		Circle(float x, float y, float radius, float startAngle, float endAngle);
	
		// ---- setters getters ----
		
		inline Circle& label(const char* label) & {this->IPlot::label(label); return *this;}
		inline Circle&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		inline Circle& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		inline Circle&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		inline Circle& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		inline Circle&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		inline LineType lineType() const {return this->line_type;}
		inline Circle& lineType(LineType lt) & {this->line_type = lt; return *this;}
		inline Circle&& lineType(LineType lt) && {this->line_type = lt; return std::move(*this);}
		
		inline float lineWidth() const {return this->line_width;}
		inline Circle& lineWidth(float lw) & {this->line_width = lw; return *this;}
		inline Circle&& lineWidth(float lw) && {this->line_width = lw; return std::move(*this);}
		
		inline Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		inline Circle& color(Color col) & {this->opt_color = col; return *this;}
		inline Circle&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		inline bool isAutoColor() const {return this->opt_color.has_value();}
		inline Circle& setAutoColor() & {this->opt_color = std::nullopt; return *this;}
		inline Circle&& setAutoColor() && {this->opt_color = std::nullopt; return std::move(*this);}
		
		inline const FillStyle& fill() const {return this->fill_style;}
		inline Circle& fillSolid(float opacity = 1.0, bool transparent = false) & {this->fill_style.solid(opacity, transparent); return *this;}
		inline Circle&& fillSolid(float opacity = 1.0, bool transparent = false) && {this->fill_style.solid(opacity, transparent); return std::move(*this);}
		inline Circle& fillClear() & {this->fill_style.clear(); return *this;}
		inline Circle&& fillClear() && {this->fill_style.clear(); return std::move(*this);}
		inline Circle& fillPattern(int n) & {this->fill_style.pattern(n); return *this;}
		inline Circle&& fillPattern(int n) && {this->fill_style.pattern(n); return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printData(FILE* fptr) const override;
		
		virtual void printPlot(FILE* fptr) const override;
	
	private:
		
		float x_;
		float y_;
		float radius_;
		float start_angle;
		float end_angle;
		
		float line_width = 1.5;
		LineType line_type = LineType::solid;
		
		FillStyle fill_style;
		
		std::optional<Color> opt_color = std::nullopt;
		
	};

	// construction helper
	// this one mostly exists for a uniform API
	inline Circle circle(float x, float y, float radius=1.0f, float startAngle=0.0f, float endAngle=360.0f){
		return Circle(x, y, radius, startAngle, endAngle);
	}

}