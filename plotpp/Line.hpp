#pragma once

// std
#include <ostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <optional>

// fmt
#include <fmt/core.h>

// plotpp
#include "plotpp/IPlot.hpp"
#include "plotpp/LineType.hpp"
#include "plotpp/Color.hpp"
#include "optional_ptr.hpp"
#include "plotpp/concepts.hpp"

namespace plotpp{

	template<ForwardRange Tx, ForwardRange Ty>
	class Line : public IPlot{	
	public:
		

		Line(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{}
		
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
		
		inline Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		inline Line& color(Color col) & {this->opt_color = col; return *this;}
		inline Line&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		inline bool isAutoColor() const {return this->opt_color.has_value();}
		inline Line& setAutoColor() & {this->opt_color = std::nullopt; return *this;}
		inline Line&& setAutoColor() && {this->opt_color = std::nullopt; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(FILE* fptr) const override {
			// Line Data, Width and Dash Type
			fmt::print(fptr, 
				"$d{:d} using 1:2 with lines lw {:02f} dt {:d}", 
				this->IPlot::uid(), this->lineWidth(), static_cast<int>(this->lineType()));
			
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
				auto xitr = std::begin(*x_);
				auto yitr = std::begin(*y_);
				
				for (; xitr != std::end(*x_) && yitr != std::end(*y_); ++xitr, (void)++yitr)
					fmt::print(fptr, "{} {}\n", *xitr, *yitr);
			}else{
				size_t x = 0;
				auto yitr = std::begin(*y_);
				
				for (; yitr != std::end(*y_); ++x, (void)++yitr)
					fmt::print(fptr, "{} {}\n", x, *yitr);
			}
			fmt::print(fptr, "e\n");
		}
		
		
		
		
		
		inline Line& label(const char* label) & {this->IPlot::label(label); return *this;}
		inline Line&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		inline Line& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		inline Line&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		inline Line& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		inline Line&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
	public:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_color = std::nullopt;
		LineType line_type = LineType::solid;
		float line_width = 1.5;
		
	};

	/*constructor helper
		Deduces the template parameters for `Line` and constructs it with perfect argument forwarding.
		This guarantees that no unnecessary copies are made for what could be huge datasets for `x` and `y`.
	*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto line(U1&& x, U2&& y) 
	{
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Line<Tx, Ty>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}

	/*constructor helper*/
	template<PtrOrMoved U2>
	auto line(U2&& y) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Line<Tx, Ty>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}

}