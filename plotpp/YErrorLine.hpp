#pragma once

/**
	@file YErrorLine.hpp
	@brief Defines the YErrorLine class and useful helper functions for plotting a YErrorLine from x- and y- coordinates.
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
		@example yerrorline.cpp
	*/ 

	/**
		@brief Represents a YErrorLine plot from x- and y-coordiantes.
		
		The YErrorLine class holds information about how to draw a YErrorLine plot in a figure.
		It supports various customizations such as YErrorLine type, color, and fill styles.
		
		@tparam Tx Type for x-coordinate range, must satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range) (aka. have forward `begin()` and `end()` iterators)
		@tparam Ty Type for y-coordinate range, must satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range) ()
		
		
	*/
	template<std::ranges::forward_range Tx, std::ranges::forward_range Ty, std::ranges::forward_range Terr>
	class YErrorLine : public IPlot{	
	public:
		
		/**
			@brief Constructs a YErrorLine with optional x and y coordinate ranges.
			
			Suggestion: Use these construction helpers instead: 
			- YErrorLine(Ux&& x, Uy&& y) 
			- YErrorLine(Uy&& y) 
			
			@param x optional_ptr to the x-coordinate range.
			@param y optional_ptr to the y-coordinate range.
		*/
		YErrorLine(optional_ptr<Tx> x, optional_ptr<Ty> y, optional_ptr<Terr> err)
			: x_(std::move(x))
			, y_(std::move(y)) 
			, err_(std::move(err))
			{
				fill_style.solid(0.3);
			}
		
		YErrorLine(YErrorLine const &) = default; 				///< Default copy constructor	
		YErrorLine(YErrorLine&&) = default;						///< Default move constructor
		YErrorLine& operator=(YErrorLine const &) = default;	///< Default copy assignment
		YErrorLine& operator=(YErrorLine&&) = default;			///< Default move assignment
		
		
		// ---- setters getters ----
		
		/**
			@brief Gets the YErrorLine type
			@return LineType - The current LineType
		*/
		inline LineType lineType() const {return this->line_type;}
		
		/** 
			@brief Sets the YErrorLine type
			@param lt : LineType - The new YErrorLine type
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& lineType(LineType lt) & {this->line_type = lt; return *this;}
		
		/** 
			@brief Sets the YErrorLine type
			@param lt : float - The new YErrorLine type
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& lineType(LineType lt) && {this->line_type = lt; return std::move(*this);}
		
		/**
			@brief Gets the YErrorLine width
			@return float: The current YErrorLine width
		*/
		inline float YErrorLineWidth() const {return this->YErrorLine_width;}
		
		/** 
			@brief Sets the YErrorLine width
			@param lw : float - The new YErrorLine width
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& YErrorLineWidth(float lw) & {this->YErrorLine_width = lw; return *this;}
		
		/** 
			@brief Sets the YErrorLine width
			@param lw : float - The new YErrorLine width
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& YErrorLineWidth(float lw) && {this->YErrorLine_width = lw; return std::move(*this);}
		
		
		/** 
			@brief Gets the YErrorLine color
			@return Color - the current YErrorLine color
		*/
		inline Color YErrorLineColor() const {return this->opt_YErrorLine_color.value_or(Color(0,0,0));}
		
		/** 
			@brief Sets the YErrorLine color
			@param col : Color - The new YErrorLine color
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& YErrorLineColor(Color col) & {this->opt_YErrorLine_color = col; return *this;}
		
		/** 
			@brief Sets the YErrorLine color
			@param col : Color - The new YErrorLine color
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& YErrorLineColor(Color col) && {this->opt_YErrorLine_color = col; return std::move(*this);}
		
		/** 
			@brief Sets the YErrorLine color
			@param r,g,b : float - The new YErrorLine color in rgb-values in the range [0, 1]
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& YErrorLineColor(float r, float g, float b) & {return this->YErrorLineColor(Color(r, g, b));}
		
		/** 
			@brief Sets the YErrorLine color
			@param r,g,b : float - The new YErrorLine color in rgb-values in the range [0, 1]
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& YErrorLineColor(float r, float g, float b) && {return std::move(this->YErrorLineColor(Color(r, g, b)));}
		
		/** 
			@brief Gets the YErrorLine color
			@return Color - the current fill color
		*/
		inline Color fillColor() const {return this->opt_fill_color.value_or(Color(0,0,0));}
		
		/** 
			@brief Sets the fill color
			@param col : Color - The new fill color
			@return fill - Self, for method chaining
		*/
		inline YErrorLine& fillColor(Color col) & {this->opt_fill_color = col; return *this;}
		
		/** 
			@brief Sets the fill color
			@param col : Color - The new fill color
			@return fill - Self, for method chaining
		*/
		inline YErrorLine&& fillColor(Color col) && {this->opt_fill_color = col; return std::move(*this);}
		
		/** 
			@brief Sets the YErrorLine and fill color
			@param col : Color - The new YErrorLine and fill color
			@return fill - Self, for method chaining
		*/
		inline YErrorLine& color(Color col) & {return this->YErrorLineColor(col).fillColor(col); return *this;}
		
		/** 
			@brief Sets the YErrorLine and fill color
			@param col : Color - The new YErrorLine and fill color
			@return fill - Self, for method chaining
		*/
		inline YErrorLine&& color(Color col) && {return std::move(this->YErrorLineColor(col).fillColor(col));}
		
		/** 
			@brief Enables automatic YErrorLine coloring
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& autoYErrorLineColor() & {this->opt_YErrorLine_color = std::nullopt; return *this;}
		
		/** 
			@brief Enables automatic YErrorLine coloring
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& autoYErrorLineColor() && {this->opt_YErrorLine_color = std::nullopt; return std::move(*this);}
		
		/** 
			@brief Enables automatic fill coloring
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& autoFillColor() & {this->opt_fill_color = std::nullopt; return *this;}
		
		/** 
			@brief Enables automatic fill coloring
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& autoFillColor() && {this->opt_fill_color = std::nullopt; return std::move(*this);}
		
		/** 
			@brief Enables automatic YErrorLine and fill coloring
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& autoColor() & {return this->autoYErrorLineColor().autoFillColor();}
		
		/** 
			@brief Enables automatic YErrorLine and fill coloring
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& autoColor() && {return std::move(this->autoYErrorLineColor().autoFillColor);}
		
		/** 
			@brief Sets the opacity of the fill color
			@param r,g,b : float - the new opacity in a range of [0, 1]
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& fill(float opacity = 0.3) & {this->fill_style.solid(opacity); return *this;}
		
		/** 
			@brief Sets the opacity of the fill color
			@param r,g,b : float - the new opacity in a range of [0, 1]
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& fill(float opacity = 0.3) && {this->fill_style.solid(opacity); return std::move(*this);}
		
		/** 
			@brief Sets the fill pattern 
			@param n : int - Select one of Gnuplots fill patterns. May be benefitial for printing figures on paper.
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& fillPattern(int n) & {this->fill_style.pattern(n); return *this;}
		
		/** 
			@brief Sets the fill pattern 
			@param n : int - Select one of Gnuplots fill patterns. May be benefitial for printing figures on paper.
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& fillPattern(int n) && {this->fill_style.pattern(n); return std::move(*this);}
		
		/** 
			@brief Disables the curve fill
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& noFill() & {this->fill_style.clear(); return *this;}
		
		/** 
			@brief Disables the curve fill
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& noFill() && {this->fill_style.clear(); return std::move(*this);}
		
		/** 
			@brief Tells whether or not the fill is enabled
			@return bool - Returns `true` if the fill is enabled and `false` otherwise
		*/
		inline bool isFilled() const {return !(this->fill_style.isEmpty());}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& label(const PlotTitle& label) & {this->IPlot::label(label); return *this;}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& label(const PlotTitle& label) && {this->IPlot::label(label); return std::move(*this);}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine& label(PlotTitle&& label) & {this->IPlot::label(label); return *this;}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return YErrorLine - Self, for method chaining
		*/
		inline YErrorLine&& label(PlotTitle&& label) && {this->IPlot::label(label); return std::move(*this);}
		
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
			// Print filled error curve
			// ========================
			
			if(this->isFilled()){
				// data and error type
				fmt::print(fptr, "$d{:d} using 1:($2+$3):($2-$3) with filledcurves {} {} ", 
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
			
			// Print YErrorLine
			// ==========
			
			if(this->line_type != LineType::none){
				if(this->isFilled()) fmt::print(fptr, ", \\\n\t");
				fmt::print(fptr, 
					"$d{:d} using 1:2 with line lw {:.2f} {} {} {}", 
					this->IPlot::uid(), 
					this->YErrorLineWidth(), 
					this->lineType(),
					this->opt_YErrorLine_color,
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
			fmt::print(fptr, "$d{:d} << e\n#x, y, error\n", this->IPlot::uid());

			if(this->x_){
				auto xItr = std::ranges::cbegin(*(this->x_));
				const auto xEnd = std::ranges::cend(*(this->x_));
				
				auto yItr = std::ranges::cbegin(*(this->y_));
				const auto yEnd = std::ranges::cend(*(this->y_));
				
				auto errItr = std::ranges::cbegin(*(this->err_));
				const auto errEnd = std::ranges::cend(*(this->err_));
				
				for(; (xItr != xEnd) && (yItr != yEnd) && (errItr != errEnd); ++xItr, (void)++yItr, (void)++errItr){
					const auto& x = *xItr;
					const auto& y = *yItr;
					const auto& err = *errItr;
					fmt::print(fptr, "{} {} {}\n", x, y, err);
				}
			}else{
				size_t x = 0;
				
				auto yItr = std::ranges::cbegin(*(this->y_));
				const auto yEnd = std::ranges::cend(*(this->y_));
				
				auto errItr = std::ranges::cbegin(*(this->err_));
				const auto errEnd = std::ranges::cend(*(this->err_));
				
				for(;(yItr != yEnd) && (errItr != errEnd); ++x, (void)++yItr, (void)++errItr){
					const auto& y = *yItr;
					const auto& err = *errItr;
					fmt::print(fptr, "{} {} {}\n", x, y, err);
				}
			}
			fmt::print(fptr, "e\n\n");
		}
		
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		optional_ptr<Terr> err_;
		std::optional<Color> opt_YErrorLine_color = std::nullopt;
		std::optional<Color> opt_fill_color = Color(0.5, 0.5, 0.5);
		LineType line_type = LineType::solid;
		float YErrorLine_width = 1.5;
		FillStyle fill_style;
		
	};

	/**
		@brief Construction helper function to create a YErrorLine instance with x- and y-coordinate ranges.
		@param x : PtrOrMoved - The x-coordinate data. Can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@param y : PtrOrMoved - The y-coordinate data. can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@return A YErrorLine instance.
	*/
	template<PtrOrMoved Ux, PtrOrMoved Uy, PtrOrMoved Uerr>
	auto yerrorline(Ux&& x, Uy&& y, Uerr&& err) 
	{
		using Tx = remove_ptr_t<std::remove_reference_t<Ux>>;
		using Ty = remove_ptr_t<std::remove_reference_t<Uy>>;
		using Terr = remove_ptr_t<std::remove_reference_t<Uerr>>;
		return YErrorLine<Tx, Ty, Terr>(
					optional_ptr<Tx>(std::forward<Ux>(x)), 
					optional_ptr<Ty>(std::forward<Uy>(y)),
					optional_ptr<Terr>(std::forward<Uerr>(err)));
	}

	/**
		@brief Construction helper function to create a YErrorLine instance with x and y coordinate ranges.
		@param y : PtrOrMoved - The y-coordinate data. can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@return A YErrorLine instance.
	*/
	template<PtrOrMoved Uy, PtrOrMoved Uerr>
	auto yerrorline(Uy&& y, Uerr&& err) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<Uy>>;
		using Terr = remove_ptr_t<std::remove_reference_t<Uerr>>;
		return YErrorLine<Tx, Ty, Terr>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<Uy>(y)),
					optional_ptr<Terr>(std::forward<Uerr>(err)));
	}

}