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

namespace plotpp{

	/// @example impulses.cpp

	template<ForwardRange Tx, ForwardRange Ty>
	class Impulses : public IPlot{	
	public:
		

		Impulses(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{}
		
		Impulses(Impulses const &) = default;
		Impulses(Impulses&&) = default;
		Impulses& operator=(Impulses const &) = default;
		Impulses& operator=(Impulses&&) = default;
		
		// ---- setters getters ----
		
		inline LineType lineType() const {return this->line_type;}
		inline Impulses& lineType(LineType lt) & {this->line_type = lt; return *this;}
		inline Impulses&& lineType(LineType lt) && {this->line_type = lt; return std::move(*this);}
		
		inline float lineWidth() const {return this->line_width;}
		inline Impulses& lineWidth(float lw) & {this->line_width = lw; return *this;}
		inline Impulses&& lineWidth(float lw) && {this->line_width = lw; return std::move(*this);}
		
		inline Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		inline Impulses& color(Color col) & {this->opt_color = col; return *this;}
		inline Impulses&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		inline bool isAutoColor() const {return this->opt_color.has_value();}
		inline Impulses& setAutoColor() & {this->opt_color = std::nullopt; return *this;}
		inline Impulses&& setAutoColor() && {this->opt_color = std::nullopt; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(FILE* fptr) const override {
			// data and line type
			fmt::print(fptr, "$d{:d} using 1:2 with impulses", this->IPlot::uid());
			
			// Impulses Width and Dash Type
			fmt::print(fptr, 
				" lw {:.2f} dt {:d}", 
				this->lineWidth(), static_cast<int>(this->lineType()));
			
			// Color
			if(this->opt_color){
				fmt::print(fptr, " lc rgb '#{:06x}'", this->opt_color.value().to_int32());
			}
			
			// Title
			if(this->IPlot::label().empty()){
				fmt::print(fptr, " notitle");
			}else{
				fmt::print(fptr, " title '{}'", this->IPlot::label());
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
		
		
		inline Impulses& label(const char* label) & {this->IPlot::label(label); return *this;}
		inline Impulses&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		inline Impulses& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		inline Impulses&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		inline Impulses& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		inline Impulses&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
	public:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_color = std::nullopt;
		LineType line_type = LineType::solid;
		float line_width = 1.5;
		
	};

	/*constructor helper
		Deduces the template parameters for `Impulses` and constructs it with perfect argument forwarding.
		This guarantees that no unnecessary copies are made for what could be huge datasets for `x` and `y`.
	*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto impulses(U1&& x, U2&& y) 
	{
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Impulses<Tx, Ty>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}

	/*constructor helper*/
	template<PtrOrMoved U2>
	auto impulses(U2&& y) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Impulses<Tx, Ty>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}

}