#pragma once

// std
#include <ostream>
#include <optional>

// {fmt}
#include <fmt/core.h>

// project
#include "optional_ptr.hpp"
#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{

	template<class Tx, class Ty, class Tyerr>
	class YError : public IPlot{
	public:
		
		YError(optional_ptr<Tx> x, optional_ptr<Ty> y, optional_ptr<Tyerr> yerr)
			: x_(std::move(x))
			, y_(std::move(y)) 
			, yerror_(std::move(yerr)) 
			{}
		
		YError(YError const &) = default;
		YError(YError&&) = default;
		YError& operator=(YError const &) = default;
		YError& operator=(YError&&) = default;
		
		// ---- setters getters ----
		
		YError& label(const char* label) & {this->IPlot::label(label); return *this;}
		YError&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		YError& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		YError&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		YError& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		YError&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		PointType pointType() const {return this->point_type;}
		YError& pointType(PointType pt) & {this->point_type = pt; return *this;}
		YError&& pointType(PointType pt) && {this->point_type = pt; return std::move(*this);}
		
		float pointSize() const {return this->point_size;}
		YError& pointSize(float ps) & {this->point_size = ps; return *this;}
		YError&& pointSize(float ps) && {this->point_size = ps; return std::move(*this);}
		
		Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		YError& color(Color col) & {this->opt_color = col; return *this;}
		YError&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		bool isAutoColor() const {return this->opt_color.has_value();}
		YError& setAutoColor() & {this->opt_color = std::nullopt; return *this;}
		YError&& setAutoColor() && {this->opt_color = std::nullopt; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(FILE* fptr) const {
			fmt::print(fptr, "$d{0:d} using 1:2:3 with yerrorbars ps {1:.2f} {2} {3} {4}", 
				this->IPlot::uid(), 
				this->pointSize(), 
				this->pointType(),
				this->opt_color,
				this->IPlot::label());
		}
		
		virtual void printData(FILE* fptr) const {
			fmt::print(fptr, "$d{:d} << e\n", this->IPlot::uid());

			auto xitr = std::begin(*x_);
			auto yitr = std::begin(*y_);
			auto yerrItr = std::begin(*yerror_);
			
			const auto xEnd = std::end(*x_);
			const auto yEnd = std::end(*y_);
			const auto yerrEnd = std::end(*yerror_);

			for (; xitr != xEnd && yitr != yEnd && yerrItr != yerrEnd; ++xitr, (void)++yitr, (void)++yerrItr)
				fmt::print(fptr, "{} {} {}\n", *xitr, *yitr, *yerrItr);
			
			fmt::print(fptr, "e\n");
		}
		
		
	public:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		optional_ptr<Tyerr> yerror_;
		std::optional<Color> opt_color = std::nullopt;
		PointType point_type = PointType::CircleFilled;
		float point_size = 1.0;
	};
	
	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2, PtrOrMoved U3>
	auto yerror(U1&& x, U2&& y, U3&& yerr) {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		using Tyerr = remove_ptr_t<std::remove_reference_t<U3>>;
		return YError<Tx, Ty, Tyerr>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)), 
					optional_ptr<Tyerr>(std::forward<U3>(yerr)));
	}
	
}