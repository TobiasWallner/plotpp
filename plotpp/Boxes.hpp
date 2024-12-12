#pragma once

#include <ostream>
#include <iterator>
#include <optional>

#include "plotpp/IPlot.hpp"


/* TODO: parameterise boxwidth 
				float width
				BoxWithType:: Absolute | Relative
*/

/* TODO: Add Color

*/


namespace plotpp{
	
	template<class Tx, class Ty>
	class Boxes : public IPlot{
	public:
		
		Boxes(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{}
		
		// ---- setters getters ----
		
		inline Boxes& label(const char* label) & {this->IPlot::label(label); return *this;}
		inline Boxes&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		inline Boxes& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		inline Boxes&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		inline Boxes& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		inline Boxes&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		inline float opacity() const {return this->opacity_;}
		inline Boxes& opacity(float opacity) & {this->opacity_ = opacity; return *this;}
		inline Boxes&& opacity(float opacity) && {this->opacity_ = opacity; return std::move(*this);}
		
		inline float boxWidth() const {return this->box_width;}
		inline Boxes& boxWidth(float bw) & {this->box_width = bw; return *this;}
		inline Boxes&& boxWidth(float bw) && {this->box_width = bw; return std::move(*this);}
		
		inline bool relativeBoxWidth() const {return this->relative_boxwidth;}
		inline Boxes& relativeBoxWidth(bool rbw) & {this->relative_boxwidth = rbw; return *this;}
		inline Boxes&& relativeBoxWidth(bool rbw) && {this->relative_boxwidth = rbw; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printSettings(FILE* fptr) const override{
			fmt::print(fptr, 
				"set boxwidth {:02f} {}\n", 
				this->boxWidth(),
				this->relativeBoxWidth() ? " relative" : "");
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
		
		virtual void printPlot(FILE* fptr) const override{
			fmt::print(fptr, "$d{:d} using 1:2 with boxes fs transparent solid {:02f}", this->IPlot::uid(), this->opacity());
			
			if(this->IPlot::label().empty()){
				fmt::print(fptr, " notitle");
			}else{
				fmt::print(fptr, " title '{}'", this->IPlot::label());
			}
		}
		
		
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_color = std::nullopt;
		float opacity_ = 0.5;
		float box_width = 0.8;
		bool relative_boxwidth = true;
	};
	
	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto boxes(U1&& x, U2&& y) {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Boxes<Tx, Ty>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}
	
	template<PtrOrMoved U2>
	auto boxes(U2&& y) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Boxes<Tx, Ty>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}
}