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
			
	template<class Tx, class Ty, class Txerr>
	class XError : public IPlot{
	public:
		

		XError(optional_ptr<Tx> x, optional_ptr<Ty> y, optional_ptr<Txerr> xerror)
			: x_(std::move(x))
			, y_(std::move(y))
			, xerror_(std::move(xerror))
		{}
		
		XError(XError const &) = default;
		XError(XError&&) = default;
		XError& operator=(XError const &) = default;
		XError& operator=(XError&&) = default;
		
		// ---- setters getters ----
		
		XError& label(const char* label) & {this->IPlot::label(label); return *this;}
		XError&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		XError& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		XError&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		XError& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		XError&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		PointType pointType() const {return this->point_type;}
		XError& pointType(PointType pt) & {this->point_type = pt; return *this;}
		XError&& pointType(PointType pt) && {this->point_type = pt; return std::move(*this);}
		
		float pointSize() const {return this->point_size;}
		XError& pointSize(float ps) & {this->point_size = ps; return *this;}
		XError&& pointSize(float ps) && {this->point_size = ps; return std::move(*this);}
		
		Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		XError& color(Color col) & {this->opt_color = col; return *this;}
		XError&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		bool isAutoColor() const {return this->opt_color.has_value();}
		XError& setAutoColor() & {this->opt_color = std::nullopt; return *this;}
		XError&& setAutoColor() && {this->opt_color = std::nullopt; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(FILE* fptr) const {
			fmt::print(fptr, "$d{0:d} using 1:2:3 with xerrorbars ps {1:.2f} {2} {3} {4}", 
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
			
			const auto xEnd = std::ranges::cend(*x_);
			const auto yEnd = std::ranges::cend(*y_);
			const auto xerrEnd = std::ranges::cend(*xerror_);

			for (; xitr != xEnd && yitr != yEnd && xerrItr != xerrEnd; ++xitr, (void)++yitr, (void)++xerrItr)
				fmt::print(fptr, "{} {} {}\n", *xitr, *yitr, *xerrItr);
			
			fmt::print(fptr, "e\n");
		}
		
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		optional_ptr<Txerr> xerror_;
		std::optional<Color> opt_color = std::nullopt;
		PointType point_type = PointType::CircleFilled;
		float point_size = 1.0;
	};

	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2, PtrOrMoved U3>
	auto xerror(U1&& x, U2&& y, U3&& xerr) {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		using Txerr = remove_ptr_t<std::remove_reference_t<U3>>;
		return XError<Tx, Ty, Txerr>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)), 
					optional_ptr<Txerr>(std::forward<U3>(xerr)));
	}

}