#pragma once

/**
	@file Line.hpp
	@brief Defines the line class and useful helper functions for plotting a line from x- and y- coordinates.
*/

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

	/**
		@example line.cpp
	*/ 

	/**
		@brief Represents a line plot from x- and y-coordiantes.
		
		The Line class holds information about how to draw a line plot in a figure.
		It supports various customizations such as line type, color, and fill styles.
		
		@tparam Tx Type for x-coordinate range, must satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range) (aka. have forward `begin()` and `end()` iterators)
		@tparam Ty Type for y-coordinate range, must satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range) ()
		
		
	*/
	template<std::ranges::forward_range Tx, std::ranges::forward_range Ty>
	class Line : public IPlot{	
	public:
		
		/**
			@brief Constructs a Line with optional x and y coordinate ranges.
			
			Suggestion: Use these construction helpers instead: 
			- line(Ux&& x, Uy&& y) 
			- line(Uy&& y) 
			
			@param x optional_ptr to the x-coordinate range.
			@param y optional_ptr to the y-coordinate range.
		*/
		Line(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{
				fill_style.clear();
			}
		
		Line(Line const &) = default; 				///< Default copy constructor	
		Line(Line&&) = default;						///< Default move constructor
		Line& operator=(Line const &) = default;	///< Default copy assignment
		Line& operator=(Line&&) = default;			///< Default move assignment
		
		
		// ---- setters getters ----
		
		/**
			@brief Gets the line type
			@return LineType - The current LineType
		*/
		inline LineType lineType() const {return this->line_type;}
		
		/** 
			@brief Sets the line type
			@param lt : LineType - The new line type
			@return Line - Self, for method chaining
		*/
		inline Line& lineType(LineType lt) & {this->line_type = lt; return *this;}
		
		/** 
			@brief Sets the line type
			@param lt : float - The new line type
			@return Line - Self, for method chaining
		*/
		inline Line&& lineType(LineType lt) && {this->line_type = lt; return std::move(*this);}
		
		/**
			@brief Gets the line width
			@return float: The current line width
		*/
		inline float lineWidth() const {return this->line_width;}
		
		/** 
			@brief Sets the line width
			@param lw : float - The new line width
			@return Line - Self, for method chaining
		*/
		inline Line& lineWidth(float lw) & {this->line_width = lw; return *this;}
		
		/** 
			@brief Sets the line width
			@param lw : float - The new line width
			@return Line - Self, for method chaining
		*/
		inline Line&& lineWidth(float lw) && {this->line_width = lw; return std::move(*this);}
		
		
		/** 
			@brief Gets the line color
			@return Color - the current line color
		*/
		inline Color lineColor() const {return this->opt_line_color.value_or(Color(0,0,0));}
		
		/** 
			@brief Sets the line color
			@param col : Color - The new line color
			@return Line - Self, for method chaining
		*/
		inline Line& lineColor(Color col) & {this->opt_line_color = col; return *this;}
		
		/** 
			@brief Sets the line color
			@param col : Color - The new line color
			@return Line - Self, for method chaining
		*/
		inline Line&& lineColor(Color col) && {this->opt_line_color = col; return std::move(*this);}
		
		/** 
			@brief Sets the line color
			@param r,g,b : float - The new line color in rgb-values in the range [0, 1]
			@return Line - Self, for method chaining
		*/
		inline Line& lineColor(float r, float g, float b) & {return this->lineColor(Color(r, g, b));}
		
		/** 
			@brief Sets the line color
			@param r,g,b : float - The new line color in rgb-values in the range [0, 1]
			@return Line - Self, for method chaining
		*/
		inline Line&& lineColor(float r, float g, float b) && {return std::move(this->lineColor(Color(r, g, b)));}
		
		/** 
			@brief Gets the line color
			@return Color - the current fill color
		*/
		inline Color fillColor() const {return this->opt_fill_color.value_or(Color(0,0,0));}
		
		/** 
			@brief Sets the fill color
			@param col : Color - The new fill color
			@return fill - Self, for method chaining
		*/
		inline Line& fillColor(Color col) & {this->opt_fill_color = col; return *this;}
		
		/** 
			@brief Sets the fill color
			@param col : Color - The new fill color
			@return fill - Self, for method chaining
		*/
		inline Line&& fillColor(Color col) && {this->opt_fill_color = col; return std::move(*this);}
		
		/** 
			@brief Sets the line and fill color
			@param col : Color - The new line and fill color
			@return fill - Self, for method chaining
		*/
		inline Line& color(Color col) & {return this->lineColor(col).fillColor(col); return *this;}
		
		/** 
			@brief Sets the line and fill color
			@param col : Color - The new line and fill color
			@return fill - Self, for method chaining
		*/
		inline Line&& color(Color col) && {return std::move(this->lineColor(col).fillColor(col));}
		
		/** 
			@brief Enables automatic line coloring
			@return Line - Self, for method chaining
		*/
		inline Line& autoLineColor() & {this->opt_line_color = std::nullopt; return *this;}
		
		/** 
			@brief Enables automatic line coloring
			@return Line - Self, for method chaining
		*/
		inline Line&& autoLineColor() && {this->opt_line_color = std::nullopt; return std::move(*this);}
		
		/** 
			@brief Enables automatic fill coloring
			@return Line - Self, for method chaining
		*/
		inline Line& autoFillColor() & {this->opt_fill_color = std::nullopt; return *this;}
		
		/** 
			@brief Enables automatic fill coloring
			@return Line - Self, for method chaining
		*/
		inline Line&& autoFillColor() && {this->opt_fill_color = std::nullopt; return std::move(*this);}
		
		/** 
			@brief Enables automatic line and fill coloring
			@return Line - Self, for method chaining
		*/
		inline Line& autoColor() & {return this->autoLineColor().autoFillColor();}
		
		/** 
			@brief Enables automatic line and fill coloring
			@return Line - Self, for method chaining
		*/
		inline Line&& autoColor() && {return std::move(this->autoLineColor().autoFillColor);}
		
		/** 
			@brief Sets the opacity of the fill color
			@param r,g,b : float - the new opacity in a range of [0, 1]
			@return Line - Self, for method chaining
		*/
		inline Line& fill(float opacity = 0.3) & {this->fill_style.solid(opacity); return *this;}
		
		/** 
			@brief Sets the opacity of the fill color
			@param r,g,b : float - the new opacity in a range of [0, 1]
			@return Line - Self, for method chaining
		*/
		inline Line&& fill(float opacity = 0.3) && {this->fill_style.solid(opacity); return std::move(*this);}
		
		/** 
			@brief Sets the fill pattern 
			@param n : int - Select one of Gnuplots fill patterns. May be benefitial for printing figures on paper.
			@return Line - Self, for method chaining
		*/
		inline Line& fillPattern(int n) & {this->fill_style.pattern(n); return *this;}
		
		/** 
			@brief Sets the fill pattern 
			@param n : int - Select one of Gnuplots fill patterns. May be benefitial for printing figures on paper.
			@return Line - Self, for method chaining
		*/
		inline Line&& fillPattern(int n) && {this->fill_style.pattern(n); return std::move(*this);}
		
		/** 
			@brief Disables the curve fill
			@return Line - Self, for method chaining
		*/
		inline Line& noFill() & {this->fill_style.clear(); return *this;}
		
		/** 
			@brief Disables the curve fill
			@return Line - Self, for method chaining
		*/
		inline Line&& noFill() && {this->fill_style.clear(); return std::move(*this);}
		
		/** 
			@brief Tells whether or not the fill is enabled
			@return bool - Returns `true` if the fill is enabled and `false` otherwise
		*/
		inline bool isFilled() const {return !(this->fill_style.isEmpty());}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Line - Self, for method chaining
		*/
		inline Line& label(const PlotTitle& label) & {this->IPlot::label(label); return *this;}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Line - Self, for method chaining
		*/
		inline Line&& label(const PlotTitle& label) && {this->IPlot::label(label); return std::move(*this);}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Line - Self, for method chaining
		*/
		inline Line& label(PlotTitle&& label) & {this->IPlot::label(label); return *this;}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Line - Self, for method chaining
		*/
		inline Line&& label(PlotTitle&& label) && {this->IPlot::label(label); return std::move(*this);}
		
		/**
			@brief Gets the x-values
			@return Tx - A pointer to the provided x-values of the plot. May be a `nullptr` if non were provided.
		*/
		inline Tx* x() {return this->x_.get();}
		
		/**
			@brief Gets the x-values
			@return Tx - A pointer to the provided x-values of the plot. May be a `nullptr` if non were provided.
		*/
		inline const Tx* x() const {return this->x_.get();}
		
		/**
			@brief Gets the y-values
			@return Ty - A pointer to the provided y-values of the plot
		*/
		inline Ty* y() {return this->y_.get();}
		
		/**
			@brief Gets the y-values
			@return Ty - A pointer to the provided y-values of the plot
		*/
		inline const Ty* y() const {return this->y_.get();}		
		
		// ---- IPlot overloads ----
		
		/**
			@brief prints the plot command for gnuplot
			
			This function does normally not need to be called by the user. 
			The class Figure will take care it and the communication with Gnuplot.
			
			@param file : [FILE](https://en.cppreference.com/w/c/io/FILE) - A pointer to the stream/file that the plot command shall be written to.
		*/
		virtual void printPlot(FILE* fptr) const override {
			// Print Fill
			// ==========
			
			if(this->isFilled()){
				// data and line type
				fmt::print(fptr, "$d{:d} using 1:2:(0) with filledcurves {} {}", 
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
			
			// Print Line
			// ==========
			
			if(this->line_type != LineType::none){
				if(this->isFilled()) fmt::print(fptr, ", \\\n\t");
				fmt::print(fptr, 
					"$d{:d} using 1:2 with lines lw {:.2f} {} {} {}", 
					this->IPlot::uid(), 
					this->lineWidth(), 
					this->lineType(),
					this->opt_line_color,
					this->IPlot::label());
			}
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
				auto xItr = std::cbegin(*(this->x_));
				const auto xEnd = std::cend(*(this->x_));
				auto yItr = std::cbegin(*(this->y_));
				const auto yEnd = std::cend(*(this->y_));
				for(; (xItr != xEnd) && (yItr != yEnd); ++xItr, (void)++yItr){
					const auto& x = *xItr;
					const auto& y = *yItr;
					fmt::print(fptr, "{} {}\n", x, y);
				}
			}else{
				size_t x = 0;
				auto yItr = std::cbegin(*(this->y_));
				const auto yEnd = std::cend(*(this->y_));
				for(;yItr != yEnd; ++x, (void)++yItr){
					const auto& y = *yItr;
					fmt::print(fptr, "{} {}\n", x, y);
				}
			}
			fmt::print(fptr, "e\n");
		}
		
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_line_color = std::nullopt;
		std::optional<Color> opt_fill_color = std::nullopt;
		LineType line_type = LineType::solid;
		float line_width = 1.5;
		FillStyle fill_style;
		
	};

	/**
		@brief Construction helper function to create a Line instance with x- and y-coordinate ranges.
		@param x : PtrOrMoved - The x-coordinate data. Can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@param y : PtrOrMoved - The y-coordinate data. can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@return A Line instance.
	*/
	template<PtrOrMoved Ux, PtrOrMoved Uy>
	auto line(Ux&& x, Uy&& y) 
	{
		using Tx = remove_ptr_t<std::remove_reference_t<Ux>>;
		using Ty = remove_ptr_t<std::remove_reference_t<Uy>>;
		return Line<Tx, Ty>(
					optional_ptr<Tx>(std::forward<Ux>(x)), 
					optional_ptr<Ty>(std::forward<Uy>(y)));
	}

	/**
		@brief Construction helper function to create a Line instance with x and y coordinate ranges.
		@param y : PtrOrMoved - The y-coordinate data. can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@return A Line instance.
	*/
	template<PtrOrMoved Uy>
	auto line(Uy&& y) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<Uy>>;
		return Line<Tx, Ty>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<Uy>(y)));
	}

}