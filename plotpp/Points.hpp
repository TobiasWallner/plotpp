#pragma once

/**
	@file Line.hpp
	@brief Defines the Points class and useful helper functions for plotting points from x- and y- coordinates.	
*/

// std
#include <ostream>
#include <iterator>
#include <vector>
#include <optional>
#include <ranges>

// {fmt}
#include <fmt/core.h>

// project
#include "optional_ptr.hpp"
#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"
#include "plotpp/Color.hpp"

namespace plotpp{
	
	/// @example points.cpp
	
	/**
		@brief Represents a point plot from x- and y-coordiantes.
		
		The Point class holds information about how to draw a point plot in a figure.
		It supports various customizations such as point type, color, and fill styles.
		
		@tparam Tx Type for x-coordinate range, must satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range) (aka. have forward `begin()` and `end()` iterators)
		@tparam Ty Type for y-coordinate range, must satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range) ()
	*/
	template<class Tx, class Ty>
	class Points : public IPlot{
	public:
		// ---- Constructors ----
		
		
		/**
			@brief Constructs a Points plot with optional x and y coordinate ranges.
			
			Suggestion: Use these construction helpers instead: 
			- points(U1&& x, U2&& y)
			- points(U2&& y) 
			- scatter(U1&& x, U2&& y)
			- auto scatter(U2&& y)
			
			@param x Optional pointer to the x-coordinate range.
			@param y Pointer to the y-coordinate range.
		*/
		Points(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{}
		
		/// Default copy constructor
		Points(Points const &) = default;
		/// Default move constructor
		Points(Points&&) = default;
		/// Default copy assignment constructor
		Points& operator=(Points const &) = default;
		/// Default move assignment constructor
		Points& operator=(Points&&) = default;
		
		// ---- setters getters ----
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Points - Self, for method chaining
		*/
		inline Points& label(const PlotTitle& label) & {this->IPlot::label(label); return *this;}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Points - Self, for method chaining
		*/
		inline Points&& label(const PlotTitle& label) && {this->IPlot::label(label); return std::move(*this);}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Points - Self, for method chaining
		*/
		inline Points& label(PlotTitle&& label) & {this->IPlot::label(label); return *this;}
		
		/** 
			@brief Sets the label to be seen in the legend of the plot
			@param label : PlotTitle - A title of the plot containing the label to be displayed in the legend
			@return Points - Self, for method chaining
		*/
		inline Points&& label(PlotTitle&& label) && {this->IPlot::label(label); return std::move(*this);}
		
		/**
			@brief Gets the point type
			@return PointType - The current point type
		*/
		PointType pointType() const {return this->point_type;}
		
		/** 
			@brief Sets the point type
			@param pt : PointType - The new point type
			@return Points - Self, for method chaining
		*/
		Points& pointType(PointType pt) & {this->point_type = pt; return *this;}
		
		/** 
			@brief Sets the point type
			@param pt : PointType - The new point type
			@return Points - Self, for method chaining
		*/
		Points&& pointType(PointType pt) && {this->point_type = pt; return std::move(*this);}
		
		/**
			@brief Gets the point size
			@return float - The current point size
		*/
		float pointSize() const {return this->point_size;}
		
		/** 
			@brief Sets the point size
			@param ps : float - The new point size
			@return Points - Self, for method chaining
		*/
		Points& pointSize(float ps) & {this->point_size = ps; return *this;}
		
		/** 
			@brief Sets the point size
			@param ps : float - The new point size
			@return Points - Self, for method chaining
		*/
		Points&& pointSize(float ps) && {this->point_size = ps; return std::move(*this);}
		
		/**
			@brief Gets the plot color
			@return Color - The current point color
		*/
		Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		
		/** 
			@brief Sets the point color
			@param col : Color - The new point color
			@return Points - Self, for method chaining
		*/
		Points& color(Color col) & {this->opt_color = col; return *this;}
		
		/** 
			@brief Sets the point color
			@param col : Color - The new point color
			@return Points - Self, for method chaining
		*/
		Points&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		/** 
			@brief Tells whether automatic coloring is enabled
			@return bool - `true` if automatic coloring is enabled, `false` otherwise
		*/
		bool isAutoColor() const {return this->opt_color.has_value();}
		
		/** 
			@brief Enables automatic coloring with multiple plots
			@return Points - Self, for method chaining
		*/
		Points& setAutoColor() & {this->opt_color = std::nullopt; return *this;}
		
		/** 
			@brief Enables automatic coloring with multiple plots
			@return Points - Self, for method chaining
		*/
		Points&& setAutoColor() && {this->opt_color = std::nullopt; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		/**
			@brief prints the plot command for gnuplot
			
			This function does normally not need to be called by the user. 
			The class Figure will take care it and the communication with Gnuplot.
			
			@param file : [FILE](https://en.cppreference.com/w/c/io/FILE) - A pointer to the stream/file that the plot command shall be written to.
		*/
		virtual void printPlot(FILE* fptr) const override {
			fmt::print(fptr, 
				"$d{0:d} using 1:2 with points ps {1:.2f} {2} {3} {4}", 
				this->IPlot::uid(), 
				this->pointSize(), 
				this->pointType(),
				this->opt_color,
				this->IPlot::label());
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
				auto xitr = std::ranges::cbegin(*x_);
				auto yitr = std::ranges::cbegin(*y_);
				
				for (; xitr != std::ranges::cend(*x_) && yitr != std::ranges::cend(*y_); ++xitr, (void)++yitr)
					fmt::print(fptr, "{} {}\n", *xitr, *yitr);
			}else{
				size_t x = 0;
				auto yitr = std::ranges::cbegin(*y_);
				
				for (; yitr != std::ranges::cend(*y_); ++x, (void)++yitr)
					fmt::print(fptr, "{} {}\n", x, *yitr);
			}
			fmt::print(fptr, "e\n");
		}
		
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_color = std::nullopt;
		float point_size = 1.0;
		PointType point_type = PointType::CircleFilled;
		/*TODO: LineColor*/
		
	};
	
	/**
		@brief Construction helper function to create a Plot instance with x- and y-coordinate ranges.
		@param x : PtrOrMoved - The x-coordinate data. Can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@param y : PtrOrMoved - The y-coordinate data. can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@return A Points instance.
	*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto points(U1&& x, U2&& y) {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Points<Tx, Ty>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}
	
	/**
		@brief Construction helper function to create a Plot instance with x- and y-coordinate ranges.
		
		Wrapper to for the function points(U1&& x, U2&& y), to provide another common name used for this kind of plots.
		
		@param x : PtrOrMoved - The x-coordinate data. Can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@param y : PtrOrMoved - The y-coordinate data. can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@return A Points instance.
	*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto scatter(U1&& x, U2&& y) {return points(std::forward<U1>(x), std::forward<U2>(y));}
	
	/**
		@brief Construction helper function to create a Plot instance with x- and y-coordinate ranges.
		@param y : PtrOrMoved - The y-coordinate data. can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@return A Points instance.
	*/
	template<PtrOrMoved U2>
	auto points(U2&& y) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Points<Tx, Ty>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}

	/**
		@brief Construction helper function to create a Plot instance with x- and y-coordinate ranges.
		
		Wrapper to for the function points(U2&& y), to provide another common name used for this kind of plots.
		
		@param y : PtrOrMoved - The y-coordinate data. can be passed by pointer `&x` or moved `std::move(x)`. Also has to satisfy [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range)
		@return A Points instance.
	*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto scatter(U2&& y) {return points(std::forward<U2>(y));}

}
