#pragma once

#include "plotpp/IPlot.hpp"

namespace plotpp{


	template<class Tx, ForwardRange Ty>
	class Boxplot : public IPlot{
	public:
		/// Note: Boxplot needs at least 4 y-data points to work correctly
		/// If less than 4 datapoints are used the median will be added as padding. 
		Boxplot(const Tx& x_scalar, optional_ptr<Ty> y_range)
			: x_(x_scalar)
			, y_(y_range)
		{}
		
		// ---- setters getters ----
		
		Boxplot& label(const char* label) & {this->IPlot::label(label); return *this;}
		Boxplot&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		Boxplot& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		Boxplot&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		Boxplot& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		Boxplot&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		float opacity() const {return this->opacity_;}
		Boxplot& opacity(float opacity) & {this->opacity_ = opacity; return *this;}
		Boxplot&& opacity(float opacity) && {this->opacity_ = opacity; return std::move(*this);}
		
		float boxWidth() const {return this->box_width;}
		Boxplot& boxWidth(float bw) & {this->box_width = bw; return *this;}
		Boxplot&& boxWidth(float bw) && {this->box_width = bw; return std::move(*this);}
		
		bool relativeBoxWidth() const {return this->relative_boxwidth;}
		Boxplot& relativeBoxWidth(bool rbw) & {this->relative_boxwidth = rbw; return *this;}
		Boxplot&& relativeBoxWidth(bool rbw) && {this->relative_boxwidth = rbw; return std::move(*this);}
		
		
		// ---- IPlot overloads ----

		virtual void printSettings(FILE* fptr) const {
			fmt::print(fptr, 
				"set boxwidth {:02f} {:s}\n",
				this->boxWidth(), 
				this->relativeBoxWidth() ? " relative" : "");
		}
		
		virtual void printData(FILE* fptr) const {
			fmt::print(fptr, "$d{:d} << e\n", this->IPlot::uid());
			
			for(auto yitr = std::begin(*y_); yitr!=std::end(*y_); ++yitr)
				fmt::print(fptr, "{} {}\n", this->x_, *yitr);
			
			fmt::print(fptr, "e\n");
		}
		
		virtual void printPlot(FILE* fptr) const {
			fmt::print(fptr, "$d{:d} using 1:2 with boxplot fs transparent solid {:02f}", this->IPlot::uid(), this->opacity());
			
			if(this->IPlot::label().empty()){
				fmt::print(fptr, " notitle");
			}else{
				fmt::print(fptr, " title '{}'", this->IPlot::label());
			}
		}
		
		
	private:
		Tx x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_color = std::nullopt;
		float opacity_ = 0.5;
		float box_width = 0.8;
		bool relative_boxwidth = true;
	};

	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto boxplot(const U1& x_scalar, U2&& y_range) {
		using Tx = U1;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Boxplot<Tx, Ty>(x_scalar, optional_ptr<Ty>(std::forward<U2>(y_range)));
	}
	
	template<PtrOrMoved U2>
	auto boxplot(U2&& y_range) {
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Boxplot<int, Ty>(1, optional_ptr<Ty>(std::forward<U2>(y_range)));
	}

}