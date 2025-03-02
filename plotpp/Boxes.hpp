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
	
	/// @example boxes.cpp
	
	/**
		@brief class for plotting boxes into a plotpp::Figure
		
		
		@tparam Tx, Ty Generic types that store the data for plotting and are [forward ranges](https://en.cppreference.com/w/cpp/ranges/forward_range) (aka. have `begin()` and `end()` iterators)
		
		to construct boxes **See**:
			- boxes(U1&& x, U2&& y)
			- boxes(U2&& y) 
	*/
	
	template<class Tx, class Ty>
	class Boxes : public IPlot{
	public:
		
		
		/**
			@brief Constructs boxes at x position with height y
			
			Suggestion: Use these construction helpers instead: 
			- boxes(U1&& x, U2&& y)
			- boxes(U2&& y)  
			
			@param x optional_ptr to the x-coordinate range.
			@param y optional_ptr to the y-coordinate range.
		*/
		Boxes(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
		{
			this->fill_style.solid();
		}
		
		// ---- setters getters ----
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Boxes - Self, for method chaining
		*/
		inline Boxes& label(const PlotTitle& label) & {this->IPlot::label(label); return *this;}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Boxes - Self, for method chaining
		*/
		inline Boxes&& label(const PlotTitle& label) && {this->IPlot::label(label); return std::move(*this);}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Boxes - Self, for method chaining
		*/
		inline Boxes& label(PlotTitle&& label) & {this->IPlot::label(label); return *this;}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Boxes - Self, for method chaining
		*/
		inline Boxes&& label(PlotTitle&& label) && {this->IPlot::label(label); return std::move(*this);}
		
		/**
			@brief returns the width of the boxes as a float number
			@returns float - the width of the boxes
		*/
		inline float boxWidth() const {return this->box_width;}
		
		/**
			@brief sets the absolute width of the boxes
			@param bw : float - the new box width
			@return Boxes - Self, for method chaining
		*/
		inline Boxes& boxWidth(float bw) & {this->box_width = bw; return *this;}
		
		/**
			@brief sets the absolute width of the boxes
			@param bw : float - the new box width
			@return Boxes - Self, for method chaining
		*/
		inline Boxes&& boxWidth(float bw) && {this->box_width = bw; return std::move(*this);}
		
		/**
			@returns bool - true if the plot uses a relative box width
		*/
		inline bool isRelativeBoxWidth() const {return this->relative_boxwidth;}
		
		/**
			@brief sets the box width to relative or absolute
			@param rbw : float - if true (default): uses relative box width, if false: uses absolute box widths
			@return Boxes - Self, for method chaining
		*/
		inline Boxes& relativeBoxWidth(bool rbw=true) & {this->relative_boxwidth = rbw; return *this;}
		
		/**
			@brief sets the box width to relative or absolute
			@param rbw : float - if true (default): uses relative box width, if false: uses absolute box widths
			@return Boxes - Self, for method chaining
		*/
		inline Boxes&& relativeBoxWidth(bool rbw=true) && {this->relative_boxwidth = rbw; return std::move(*this);}
		
		/**
			@return FillStyle - The fillstyle of the plot
		*/
		inline const FillStyle& fill() const {return this->fill_style;}
		
		/**
			@brief sets the box fill style to a solid fillClear
			@param opacity : float - sets the opacity of the fill (default is 0.6)
			@param transparent : bool - if true: makes the fill transparent, opacity acts like alpha value; if false (default): cannot see through filled areas
			@returns Boxes - Self, for method chaining
		*/
		inline Boxes& fillSolid(float opacity = 0.6, bool transparent = false) & {this->fill_style.solid(opacity, transparent); return *this;}
		/**
			@brief sets the box fill style to a solid fillClear
			@param opacity : float - sets the opacity of the fill (default is 0.6)
			@param transparent : bool - if true: makes the fill transparent, opacity acts like alpha value; if false (default): cannot see through filled areas
			@returns Boxes - Self, for method chaining
		*/
		
		inline Boxes&& fillSolid(float opacity = 0.6, bool transparent = false) && {this->fill_style.solid(opacity, transparent); return std::move(*this);}
		/**
			@brief removes any fill-styles
			@returns Boxes - Self, for method chaining
		*/
		inline Boxes& fillClear() & {this->fill_style.clear(); return *this;}
		
		/**
			@brief removes any fill-styles
			@returns Boxes - Self, for method chaining
		*/
		inline Boxes&& fillClear() && {this->fill_style.clear(); return std::move(*this);}
		
		/**
			@brief uses a [gnuplot fill pattern](https://gnuplot.sourceforge.net/demo/fillstyle.html). May be useful for black and white printing.
			@param n : int - the number of the pattern
			@returns Boxes - Self, for method chaining
		*/
		inline Boxes& fillPattern(int n) & {this->fill_style.pattern(n); return *this;}
		
		/**
			@brief uses a [gnuplot fill pattern](https://gnuplot.sourceforge.net/demo/fillstyle.html). May be useful for black and white printing.
			@param n : int - the number of the pattern
			@returns Boxes - Self, for method chaining
		*/
		inline Boxes&& fillPattern(int n) && {this->fill_style.pattern(n); return std::move(*this);}
		
		/**
			@brief sets the border of the box
			@param b : bool - if true (default): enables the border; if false: disables the border
			@returns Boxes - Self, for method chaining
		*/
		inline Boxes& border(bool b=true) & {this->fill_style.border(b); return *this;}
		
		/**
			@brief sets the border of the box
			@param b : bool - if true (default): enables the border; if false: disables the border
			@returns Boxes - Self, for method chaining
		*/
		inline Boxes&& border(bool b=true) && {this->fill_style.border(b); return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		/**
			@brief prints extra commands that are not within the gnuplot plot command
			
			This function does normally not need to be called by the user. 
			The class Figure will take care it and the communication with Gnuplot.
			
			@param file : [FILE](https://en.cppreference.com/w/c/io/FILE) - A pointer to the stream/file that the plot command shall be written to.
		*/
		virtual void printSettings(FILE* fptr) const override{
			fmt::print(fptr, 
				"set boxwidth {:.2f} {}\n", 
				this->boxWidth(),
				this->isRelativeBoxWidth() ? " relative" : "");
		}
		
		/**
			@brief prints the data for gnuplot
			
			This function does normally not need to be called by the user. 
			The class Figure will take care it and the communication with Gnuplot.
			
			@param file : [FILE](https://en.cppreference.com/w/c/io/FILE) - A pointer to the stream/file that the plot command shall be written to.
		*/
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
		
		/**
			@brief prints the plot command for gnuplot
			
			This function does normally not need to be called by the user. 
			The class Figure will take care it and the communication with Gnuplot.
			
			@param file : [FILE](https://en.cppreference.com/w/c/io/FILE) - A pointer to the stream/file that the plot command shall be written to.
		*/
		virtual void printPlot(FILE* fptr) const override{
			fmt::print(fptr, "$d{0} using 1:2 with boxes {1} {2} {3}", 
				this->IPlot::uid(), 
				this->fill_style,
				this->opt_color,
				this->IPlot::label());
		}
		
		
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_color = std::nullopt;
		FillStyle fill_style;
		float box_width = 0.8;
		bool relative_boxwidth = true;
	};
	
	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	inline auto boxes(U1&& x, U2&& y) {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Boxes<Tx, Ty>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}
	
	template<PtrOrMoved U2>
	inline auto boxes(U2&& y) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Boxes<Tx, Ty>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}
}