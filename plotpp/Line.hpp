#pragma once

// std
#include <ostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <optional>
#include <ranges>

// fmt
#include <fmt/core.h>

// plotpp
#include "plotpp/IPlot.hpp"
#include "plotpp/LineType.hpp"
#include "plotpp/Color.hpp"
#include "optional_ptr.hpp"
#include "plotpp/concepts.hpp"
#include "plotpp/FillStyle.hpp"

namespace plotpp{

	template<std::ranges::forward_range Tx, std::ranges::forward_range Ty>
	class Line : public IPlot{	
	public:
		

		Line(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{
				fill_style.clear();
			}
		
		Line(Line const &) = default;
		Line(Line&&) = default;
		Line& operator=(Line const &) = default;
		Line& operator=(Line&&) = default;
		
		// ---- setters getters ----
		
		inline LineType lineType() const {return this->line_type;}
		inline Line& lineType(LineType lt) & {this->line_type = lt; return *this;}
		inline Line&& lineType(LineType lt) && {this->line_type = lt; return std::move(*this);}
		
		inline float lineWidth() const {return this->line_width;}
		inline Line& lineWidth(float lw) & {this->line_width = lw; return *this;}
		inline Line&& lineWidth(float lw) && {this->line_width = lw; return std::move(*this);}
		
		
		inline Color lineColor() const {return this->opt_line_color.value_or(Color(0,0,0));}
		inline Line& lineColor(Color col) & {this->opt_line_color = col; return *this;}
		inline Line&& lineColor(Color col) && {this->opt_line_color = col; return std::move(*this);}
		inline Line& lineColor(float r, float g, float b) & {return this->lineColor(Color(r, g, b));}
		inline Line&& lineColor(float r, float g, float b) && {return std::move(this->lineColor(Color(r, g, b)));}
		
		inline Color fillColor() const {return this->opt_fill_color.value_or(Color(0,0,0));}
		inline Line& fillColor(Color col) & {this->opt_fill_color = col; return *this;}
		inline Line&& fillColor(Color col) && {this->opt_fill_color = col; return std::move(*this);}
		inline Line& fillColor(float r, float g, float b) & {return this->fillColor(Color(r, g, b));}
		inline Line&& fillColor(float r, float g, float b) && {return std::move(this->fillColor(Color(r, g, b)));}
		
		inline Line& color(Color col) & {return this->lineColor(col).fillColor(col); return *this;}
		inline Line&& color(Color col) && {return std::move(this->lineColor(col).fillColor(col));}
		inline Line& color(float r, float g, float b) & {return this->color(Color(r, g, b));}
		inline Line&& color(float r, float g, float b) && {return std::move(this->color(Color(r, g, b)));}
		
		inline Line& autoLineColor() & {this->opt_line_color = std::nullopt; return *this;}
		inline Line&& autoLineColor() && {this->opt_line_color = std::nullopt; return std::move(*this);}
		
		inline Line& autoFillColor() & {this->opt_fill_color = std::nullopt; return *this;}
		inline Line&& autoFillColor() && {this->opt_fill_color = std::nullopt; return std::move(*this);}
		
		inline Line& autoColor() & {return this->autoLineColor().autoFillColor();}
		inline Line&& autoColor() && {return std::move(this->autoLineColor().autoFillColor);}
		
		inline Line& fill(float opacity = 0.3) & {this->fill_style.solid(opacity); return *this;}
		inline Line&& fill(float opacity = 0.3) && {this->fill_style.solid(opacity); return std::move(*this);}
		
		inline Line& fillPattern(int n) & {this->fill_style.pattern(n); return *this;}
		inline Line&& fillPattern(int n) && {this->fill_style.pattern(n); return std::move(*this);}
		
		inline Line& noFill() & {this->fill_style.clear(); return *this;}
		inline Line&& noFill() && {this->fill_style.clear(); return std::move(*this);}
		
		inline bool isFilled() const {return !(this->fill_style.isEmpty());}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(FILE* fptr) const override {
			// Print Line
			// ==========
			
			if(this->line_type != LineType::none){
				fmt::print(fptr, 
					"$d{:d} using 1:2 with lines lw {:.2f} {} {} {}", 
					this->IPlot::uid(), 
					this->lineWidth(), 
					this->lineType(),
					this->opt_line_color,
					this->IPlot::label());
			}
			
			// Print Fill
			// ==========
			
			if(this->isFilled()){
				if(this->line_type != LineType::none) fmt::print(fptr, ", \\\n");

				// data and line type
				fmt::print(fptr, "$d{:d} using 1:2:(0) with filledcurves {} {}", 
					this->IPlot::uid(),
					this->fill_style,
					this->opt_fill_color);
				
				// Title
				if(this->line_type == LineType::none) {
					fmt::print(fptr, " {}", this->IPlot::label());
				}else{
					fmt::print(fptr, " notitle");
				}
			}
			
		}
		
		virtual void printData(FILE* fptr) const override {
			fmt::print(fptr, "$d{:d} << e\n", this->IPlot::uid());

			if(this->x_){
				auto xItr = std::cbegin(*(this->x_));
				const auto xEnd = std::cend(*(this->x_));
				auto yItr = std::cbegin(*(this->y_));
				const auto yEnd = std::cend(*(this->y_));
				for(; (xItr != xEnd) && (yItr != yEnd); ++xItr, (void)++yItr){
					const auto& x = *xItr;
					const auto& y = *yItr;
					fmt::print(fptr, "{} {}\n", x, y);
				}
			}else{
				size_t x = 0;
				auto yItr = std::cbegin(*(this->y_));
				const auto yEnd = std::cend(*(this->y_));
				for(;yItr != yEnd; ++x, (void)++yItr){
					const auto& y = *yItr;
					fmt::print(fptr, "{} {}\n", x, y);
				}
			}
			fmt::print(fptr, "e\n");
		}
		
		
		inline Line& label(const char* label) & {this->IPlot::label(label); return *this;}
		inline Line&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		inline Line& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		inline Line&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		inline Line& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		inline Line&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		inline Tx* x() {return this->x_.get();}
		inline const Tx* x() const {return this->x_.get();}
		
		inline Ty* y() {return this->y_.get();}
		inline const Ty* y() const {return this->y_.get();}		
		
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_line_color = std::nullopt;
		std::optional<Color> opt_fill_color = std::nullopt;
		LineType line_type = LineType::solid;
		float line_width = 1.5;
		FillStyle fill_style;
		
	};

	/*constructor helper
		Deduces the template parameters for `Line` and constructs it with perfect argument forwarding.
		This guarantees that no unnecessary copies are made for what could be huge datasets for `x` and `y`.
	*/
	template<PtrOrMoved Ux, PtrOrMoved Uy>
	auto line(Ux&& x, Uy&& y) 
	{
		using Tx = remove_ptr_t<std::remove_reference_t<Ux>>;
		using Ty = remove_ptr_t<std::remove_reference_t<Uy>>;
		return Line<Tx, Ty>(
					optional_ptr<Tx>(std::forward<Ux>(x)), 
					optional_ptr<Ty>(std::forward<Uy>(y)));
	}

	/*constructor helper*/
	template<PtrOrMoved Uy>
	auto line(Uy&& y) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<Uy>>;
		return Line<Tx, Ty>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<Uy>(y)));
	}

}