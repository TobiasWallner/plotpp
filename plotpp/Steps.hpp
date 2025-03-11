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

	/// @example steps.cpp

	template<ForwardRange Tx, ForwardRange Ty>
	class Steps : public IPlot{	
	public:
	
		Steps(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{
				fill_style.clear();
			}
		
		Steps(Steps const &) = default;
		Steps(Steps&&) = default;
		Steps& operator=(Steps const &) = default;
		Steps& operator=(Steps&&) = default;
		
		// ---- setters getters ----
		
		inline LineType lineType() const {return this->line_type;}
		inline Steps& lineType(LineType lt) & {this->line_type = lt; return *this;}
		inline Steps&& lineType(LineType lt) && {this->line_type = lt; return std::move(*this);}
		
		inline float lineWidth() const {return this->line_width;}
		inline Steps& lineWidth(float lw) & {this->line_width = lw; return *this;}
		inline Steps&& lineWidth(float lw) && {this->line_width = lw; return std::move(*this);}
		
		inline Color lineColor() const {return this->opt_line_color.value_or(Color(0,0,0));}
		inline Steps& lineColor(Color col) & {this->opt_line_color = col; return *this;}
		inline Steps&& lineColor(Color col) && {this->opt_line_color = col; return std::move(*this);}
		inline Steps& lineColor(float r, float g, float b) & {return this->lineColor(Color(r, g, b));}
		inline Steps&& lineColor(float r, float g, float b) && {return std::move(this->lineColor(Color(r, g, b)));}
		
		inline Color fillColor() const {return this->opt_fill_color.value_or(Color(0,0,0));}
		inline Steps& fillColor(Color col) & {this->opt_fill_color = col; return *this;}
		inline Steps&& fillColor(Color col) && {this->opt_fill_color = col; return std::move(*this);}
		inline Steps& fillColor(float r, float g, float b) & {return this->fillColor(Color(r, g, b));}
		inline Steps&& fillColor(float r, float g, float b) && {return std::move(this->fillColor(Color(r, g, b)));}
		
		inline Steps& color(Color col) & {return this->lineColor(col).fillColor(col); return *this;}
		inline Steps&& color(Color col) && {return std::move(this->lineColor(col).fillColor(col));}
		inline Steps& color(float r, float g, float b) & {return this->color(Color(r, g, b));}
		inline Steps&& color(float r, float g, float b) && {return std::move(this->color(Color(r, g, b)));}
		
		inline Steps& autoLineColor() & {this->opt_line_color = std::nullopt; return *this;}
		inline Steps&& autoLineColor() && {this->opt_line_color = std::nullopt; return std::move(*this);}
		
		inline Steps& autoFillColor() & {this->opt_fill_color = std::nullopt; return *this;}
		inline Steps&& autoFillColor() && {this->opt_fill_color = std::nullopt; return std::move(*this);}
		
		inline Steps& autoColor() & {return this->autoLineColor().autoFillColor();}
		inline Steps&& autoColor() && {return std::move(this->autoLineColor().autoFillColor);}
		
		inline Steps& fill(float opacity = 0.3) & {this->fill_style.solid(opacity); return *this;}
		inline Steps&& fill(float opacity = 0.3) && {this->fill_style.solid(opacity); return std::move(*this);}
		
		inline Steps& fillPattern(int n) & {this->fill_style.pattern(n); return *this;}
		inline Steps&& fillPattern(int n) && {this->fill_style.pattern(n); return std::move(*this);}
		
		inline Steps& noFill() & {this->fill_style.clear(); return *this;}
		inline Steps&& noFill() && {this->fill_style.clear(); return std::move(*this);}
		
		inline bool isFilled() const {return !(this->fill_style.isEmpty());}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(FILE* fptr) const override {
			// Print Steps
			// ==========
			
			if(this->line_type != LineType::none){
				fmt::print(fptr, 
					"$d{:d} using 1:2 with steps lw {:.2f} {} {} {}", 
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

				// data and steps type
				fmt::print(fptr, "$d{:d} using 1:2 with fillsteps {} {}", 
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
				auto xItr = std::ranges::cbegin(*(this->x_));
				const auto xEnd = std::ranges::cend(*(this->x_));
				auto yItr = std::ranges::cbegin(*(this->y_));
				const auto yEnd = std::ranges::cend(*(this->y_));
				for(; (xItr != xEnd) && (yItr != yEnd); ++xItr, (void)++yItr){
					const auto& x = *xItr;
					const auto& y = *yItr;
					fmt::print(fptr, "{} {}\n", x, y);
				}
			}else{
				size_t x = 0;
				auto yItr = std::ranges::cbegin(*(this->y_));
				const auto yEnd = std::ranges::cend(*(this->y_));
				for(;yItr != yEnd; ++x, (void)++yItr){
					const auto& y = *yItr;
					fmt::print(fptr, "{} {}\n", x, y);
				}
			}
			fmt::print(fptr, "e\n");
		}
		
		
		
		
		
		inline Steps& label(const char* label) & {this->IPlot::label(label); return *this;}
		inline Steps&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		inline Steps& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		inline Steps&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		inline Steps& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		inline Steps&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
	public:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_line_color = std::nullopt;
		std::optional<Color> opt_fill_color = std::nullopt;
		LineType line_type = LineType::solid;
		float line_width = 1.5;
		FillStyle fill_style;
		
	};

	/*constructor helper
		Deduces the template parameters for `Steps` and constructs it with perfect argument forwarding.
		This guarantees that no unnecessary copies are made for what could be huge datasets for `x` and `y`.
	*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto steps(U1&& x, U2&& y) 
	{
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Steps<Tx, Ty>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}

	/*constructor helper*/
	template<PtrOrMoved U2>
	auto steps(U2&& y) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Steps<Tx, Ty>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}

}