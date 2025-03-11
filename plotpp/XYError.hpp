#pragma once

// std
#include <ostream>
#include <optional>
#include <ranges>

// {fmt}
#include <fmt/core.h>

// project
#include "optional_ptr.hpp"
#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{
	
	/// @example xyerror.cpp
	
	template<class Tx, class Ty, class Txerr, class Tyerr>
	class XYError : public IPlot{
	public:
		XYError(optional_ptr<Tx> x, optional_ptr<Ty> y, optional_ptr<Txerr> xerror, optional_ptr<Tyerr> yerror)
			: x_(std::move(x))
			, y_(std::move(y))
			, xerror_(std::move(xerror))
			, yerror_(std::move(yerror))
		{}
		
		XYError(XYError const &) = default;
		XYError(XYError&&) = default;
		XYError& operator=(XYError const &) = default;
		XYError& operator=(XYError&&) = default;
		
		// ---- setters getters ----
		
		XYError& label(const char* label) & {this->IPlot::label(label); return *this;}
		XYError&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		XYError& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		XYError&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		XYError& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		XYError&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		PointType pointType() const {return this->point_type;}
		XYError& pointType(PointType pt) & {this->point_type = pt; return *this;}
		XYError&& pointType(PointType pt) && {this->point_type = pt; return std::move(*this);}
		
		float pointSize() const {return this->point_size;}
		XYError& pointSize(float ps) & {this->point_size = ps; return *this;}
		XYError&& pointSize(float ps) && {this->point_size = ps; return std::move(*this);}
		
		Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		XYError& color(Color col) & {this->opt_color = col; return *this;}
		XYError&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		bool isAutoColor() const {return this->opt_color.has_value();}
		XYError& setAutoColor() & {this->opt_color = std::nullopt; return *this;}
		XYError&& setAutoColor() && {this->opt_color = std::nullopt; return std::move(*this);}
		
		// ---- IPlot overloads ----

		virtual void printPlot(FILE* fptr) const {
			fmt::print(fptr, "$d{0:d} using 1:2:3:4 with xyerrorbars ps {1:.2f} {2} {3} {4}", 
				this->IPlot::uid(), 
				this->pointSize(), 
				this->pointType(),
				this->opt_color,
				this->IPlot::label());
		}
		
		virtual void printData(FILE* fptr) const {
			fmt::print(fptr, "$d{:d} << e\n", this->IPlot::uid());
			auto xitr = std::ranges::cbegin(*x_);
			auto yitr = std::ranges::cbegin(*y_);
			auto xerrItr = std::ranges::cbegin(*xerror_);
			auto yerrItr = std::ranges::cbegin(*yerror_);
			
			const auto xEnd = std::ranges::cend(*x_);
			const auto yEnd = std::ranges::cend(*y_);
			const auto xerrEnd = std::ranges::cend(*xerror_);
			const auto yerrEnd = std::ranges::cend(*yerror_);

			for (; xitr != xEnd && yitr != yEnd && xerrItr != xerrEnd && yerrItr != yerrEnd; ++xitr, (void)++yitr, (void)++yerrItr, (void)++xerrItr)
				fmt::print(fptr, "{} {} {} {}\n", *xitr, *yitr, *xerrItr, *yerrItr);
			
			fmt::print(fptr, "e\n");
		}
		
	
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		optional_ptr<Txerr> xerror_;
		optional_ptr<Tyerr> yerror_;
		std::optional<Color> opt_color = std::nullopt;
		PointType point_type = PointType::CircleFilled;
		float point_size = 1.0;
	};

	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2, PtrOrMoved U3, PtrOrMoved U4>
	auto xyerror(U1&& x, U2&& y, U3&& xerr, U4&& yerr) {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		using Txerr = remove_ptr_t<std::remove_reference_t<U3>>;
		using Tyerr = remove_ptr_t<std::remove_reference_t<U4>>;
		return XYError<Tx, Ty, Txerr, Tyerr>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)), 
					optional_ptr<Txerr>(std::forward<U3>(yerr)), 
					optional_ptr<Tyerr>(std::forward<U4>(yerr)));
	}

}