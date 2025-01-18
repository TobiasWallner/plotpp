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

	template<ForwardRange Tx, ForwardRange Ty1, ForwardRange Ty2>
	class Filledcurves : public IPlot{	
	public:
		

		Filledcurves(optional_ptr<Tx> x, optional_ptr<Ty1> y1, optional_ptr<Ty2> y2)
			: x_(std::move(x))
			, y1_(std::move(y1)) 
			, y2_(std::move(y2)) 
			{}
		
		Filledcurves(Filledcurves const &) = default;
		Filledcurves(Filledcurves&&) = default;
		Filledcurves& operator=(Filledcurves const &) = default;
		Filledcurves& operator=(Filledcurves&&) = default;
		
		// ---- setters getters ----
		
		inline Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		inline Filledcurves& color(Color col) & {this->opt_color = col; return *this;}
		inline Filledcurves&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		inline bool isAutoColor() const {return this->opt_color.has_value();}
		inline Filledcurves& setAutoColor() & {this->opt_color = std::nullopt; return *this;}
		inline Filledcurves&& setAutoColor() && {this->opt_color = std::nullopt; return std::move(*this);}
		
		inline Filledcurves& label(const char* label) & {this->IPlot::label(label); return *this;}
		inline Filledcurves&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		inline Filledcurves& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		inline Filledcurves&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		inline Filledcurves& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		inline Filledcurves&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		
		inline const FillStyle& fill() const {return this->fill_style;}
		inline Filledcurves& fillSolid(float opacity = 1.0, bool transparent = false) & {this->fill_style.solid(opacity, transparent); return *this;}
		inline Filledcurves&& fillSolid(float opacity = 1.0, bool transparent = false) && {this->fill_style.solid(opacity, transparent); return std::move(*this);}
		inline Filledcurves& fillClear() & {this->fill_style.clear(); return *this;}
		inline Filledcurves&& fillClear() && {this->fill_style.clear(); return std::move(*this);}
		inline Filledcurves& fillPattern(int n) & {this->fill_style.pattern(n); return *this;}
		inline Filledcurves&& fillPattern(int n) && {this->fill_style.pattern(n); return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(FILE* fptr) const override {
			// data and line type and fill style
			fmt::print(fptr, "$d{:d} using 1:2:3 with filledcurves {}", this->IPlot::uid(), this->fill_style);
			
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
				auto xItr = std::cbegin(*(this->x_));
				const auto xEnd = std::cend(*(this->x_));
				auto y1Itr = std::cbegin(*(this->y1_));
				const auto y1End = std::cend(*(this->y1_));
				auto y2Itr = std::cbegin(*(this->y2_));
				const auto y2End = std::cend(*(this->y2_));
				for(; (xItr != xEnd) && (y1Itr != y1End) && (y2Itr != y2End); ++xItr, (void)++y1Itr, (void)++y2Itr){
					const auto& x = *xItr;
					const auto& y1 = *y1Itr;
					const auto& y2 = *y2Itr;
					fmt::print(fptr, "{} {} {}\n", x, y1, y2);
				}
			}else{
				size_t x = 0;
				auto y1Itr = std::cbegin(*(this->y1_));
				const auto y1End = std::cend(*(this->y1_));
				auto y2Itr = std::cbegin(*(this->y2_));
				const auto y2End = std::cend(*(this->y2_));
				for(; (y1Itr != y1End) && (y2Itr != y2End); ++x, (void)++y1Itr, (void)++y2Itr){
					const auto& y1 = *y1Itr;
					const auto& y2 = *y2Itr;
					fmt::print(fptr, "{} {} {}\n", x, y1, y2);
				}
			}
			fmt::print(fptr, "e\n");
		}
		
	public:
		optional_ptr<Tx> x_;
		optional_ptr<Ty1> y1_;
		optional_ptr<Ty2> y2_;
		std::optional<Color> opt_color = std::nullopt;
		FillStyle fill_style;
		
	};

	/*constructor helper
		Deduces the template parameters for `Filledcurves` and constructs it with perfect argument forwarding.
		This guarantees that no unnecessary copies are made for what could be huge datasets for `x` and `y`.
	*/
	template<PtrOrMoved U1, PtrOrMoved U2, PtrOrMoved U3>
	auto filledcurves(U1&& x, U2&& y1, U3&& y2) 
	{
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty1 = remove_ptr_t<std::remove_reference_t<U2>>;
		using Ty2 = remove_ptr_t<std::remove_reference_t<U3>>;
		return Filledcurves<Tx, Ty1, Ty2>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty1>(std::forward<U2>(y1)),
					optional_ptr<Ty2>(std::forward<U3>(y2)));
	}

	/*constructor helper*/
	template<PtrOrMoved U2, PtrOrMoved U3>
	auto filledcurves(U2&& y1, U3&& y2) {
		using Tx = std::vector<int>; // placeholder type
		using Ty1 = remove_ptr_t<std::remove_reference_t<U2>>;
		using Ty2 = remove_ptr_t<std::remove_reference_t<U3>>;
		return Filledcurves<Tx, Ty1, Ty2>( 
					optional_ptr<Ty1>(std::forward<U2>(y1)),
					optional_ptr<Ty2>(std::forward<U3>(y2)));
	}

}