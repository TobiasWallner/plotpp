#pragma once

// std
#include <ostream>
#include <iterator>
#include <optional>
#include <ranges>

// {fmt}
#include <fmt/core.h>

// project
#include "optional_ptr.hpp"
#include "plotpp/IPlot.hpp"
#include "plotpp/DataRelation.hpp"
#include "plotpp/ArrowHeadStyle.hpp"

namespace plotpp{
	
	/**
		\brief class for plotting arrows in plotpp::Figure
		
		Arrows contains the start and end coordinates for vectors. 
		The relationship between the datasets ([x1, y1] and [x2, y2]) can be set using \ref plotpp::DataRelation. 
		In every case [x1, y1] will be the absolute start coordinate of the vector and [x2, y2] can the absolute end coordinate or relative to the start.
		
		\tparam Tx1, Ty1, Tx2, Ty2 Generic types that store the data for plotting and are [forward ranges](https://en.cppreference.com/w/cpp/ranges/forward_range) (aka. have `begin()` and `end()` iterators)
		
		\see  arrows<PtrOrMoved, PtrOrMoved, PtrOrMoved, PtrOrMoved> function to help construct an Arrow.
	*/
	template<std::ranges::forward_range Tx1, std::ranges::forward_range Ty1, std::ranges::forward_range Tx2, std::ranges::forward_range Ty2>
	class Arrows : public IPlot{
	public:
		/**
			\brief Constructs an Arrow from x and y data for plotting plotpp::Figure
			\param x1, y1 the start coordinates of the vector
			\param x2, y2 the end coordinates of the vector. Can be absolute or relative.
		*/
		Arrows(optional_ptr<const Tx1> x1, optional_ptr<const Ty1> y1, optional_ptr<const Tx2> x2, optional_ptr<const Ty2> y2)
			: x1_(std::move(x1))
			, y1_(std::move(y1)) 
			, x2_(std::move(x2))
			, y2_(std::move(y2)) 
			{}
		
		// ---- setters getters ----
		/** 
			\brief adds a label to the plot which can be seen in legends
			\param label a string to set the label name shown in the legend 
			\returns the class itself for method chaining 
		*/
		Arrows& label(const char* label) & {this->IPlot::label(label); return *this;}
		Arrows&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		Arrows& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		Arrows&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		Arrows& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		Arrows&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		/// \returns The line width
		float lineWidth() const {return this->line_width;}
		/** 
			\brief Changes the width of the line
			\param lw The new linewidth
			\returns The class itself for method chaining 
		*/
		Arrows& lineWidth(float lw) & {this->line_width = lw; return *this;}
		Arrows&& lineWidth(float lw) && {this->line_width = lw; return std::move(*this);}
		
		/** 
			\brief Returns the relation of [x2, y2]
			\returns DataRelation
			- `DataRelation::absolute` if the end coordinates [x2, y2] are absolute to the origin of the Figure
			- `DataRelation::relative` if the end coordinates [x2, y2] are relative to [x1, y1]
		*/
		DataRelation dataRelation() const {return this->data_relation;}
		/** 
			\brief Changes the relation of the start and end data points
			
			The relationship of the start [x1, y1] coordinates and end [x2, y2] coordinates can be set with the enum plotpp::DataRelation.
			If set to 
			- `DataRelation::absolute` [x2, y2] will be absolute to the origin of the plot
			- `DataRelation::relative` [x2, y2] will be relative to the start point [x1, y1]
			
			\param lw The new linewidth
			\returns The Class itself for method chaining 
		*/
		Arrows& dataRelation(DataRelation dr) & {this->data_relation = dr; return *this;}
		Arrows&& dataRelation(DataRelation dr) && {this->data_relation = dr; return std::move(*this);}
		
		/// \returns The style of the arrow head (plotpp::ArrowHeadStyle)
		ArrowHeadStyle arrowHeadStyle() const {return this->arrow_head_style;}
		Arrows& arrowHeadStyle(ArrowHeadStyle ahs) & {this->arrow_head_style = ahs; return *this;}
		Arrows&& arrowHeadStyle(ArrowHeadStyle ahs) && {this->arrow_head_style = ahs; return std::move(*this);}
		
		///	\returns The color of the line (plotpp::Color)
		Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		
		/**
			\brief Sets the color of the line
			\returns The class itself for method chaining 
		*/
		Arrows& color(Color col) & {this->opt_color = col; return *this;}
		Arrows&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		// ---- IPlot overloads ----
		/**
			\brief Prints the plot command for gnuplot
			\param fptr The file or stream that the plot command should be written to
		*/
		virtual void printPlot(FILE* fptr) const {	
			fmt::print(fptr, "$d{0} {1} {2} {3} lw {4:.2f} {5} {6}",
				this->IPlot::uid(),
				(this->dataRelation() == DataRelation::absolute) ? " using 1:2:(($3)-($1)):($4-$2)" : " using 1:2:3:4",
				(this->dataRelation() == DataRelation::polar) ? " with arrows" : " with vectors",
				this->arrowHeadStyle(), 
				this->lineWidth(), 
				this->opt_color,
				this->IPlot::label());
		}
		
		/**
			\brief Prints the data for gnuplot
			\param fptr The file or stream that the data should be written to
		*/
		virtual void printData(FILE* fptr) const {
			fmt::print(fptr, "$d{:d} << e\n", this->IPlot::uid());
			auto x1itr = std::begin(*x1_);
			auto y1itr = std::begin(*y1_);
			auto x2itr = std::begin(*x2_);
			auto y2itr = std::begin(*y2_);
			for(; x1itr != std::end(*x1_) && y1itr != std::end(*y1_) && x2itr != std::end(*x2_) && y2itr != std::end(*y2_)
				; (void)++x1itr, (void)++y1itr, (void)++x2itr, (void)++y2itr){
				fmt::print(fptr, "{} {} {} {}\n", *x1itr, *y1itr, *x2itr, *y2itr);
			}
			fmt::print(fptr, "e\n");
		}
		
	private:
		optional_ptr<const Tx1> x1_;
		optional_ptr<const Ty1> y1_;
		optional_ptr<const Tx2> x2_;
		optional_ptr<const Ty2> y2_;
		std::optional<Color> opt_color = std::nullopt;
		DataRelation data_relation = DataRelation::relative; // relation from [x1, y1] to [x2, y2]
		float line_width = 1.5;
		ArrowHeadStyle arrow_head_style = ArrowHeadStyle::filled_head;
	};
	
	/**
		\brief helper constructor function
		
		Function that constructs an Arrow. 
		This will automatically derive correct types from the data-ranges and converts them into an optional_ptr that may or may not be the owner of the data.
		
		\tparam U1, U2, U3, U4 Can either be: 
		- a pointer to data (The Arrow will **not** own the data, aka. not deconstruct it) or 
		- data that is moved (The Arrow will own the data, aka. destruct it)
		Further the datatype has to be a [forward range](https://en.cppreference.com/w/cpp/ranges/forward_range) because of the constructor Arrows::Arrows
		
		\param x1, y1 The start coordinates of the Arrow
		\param x2, y2 The end coordinates of the Arrow
		
		\returns 
	*/
	template<PtrOrMoved U1, PtrOrMoved U2, PtrOrMoved U3, PtrOrMoved U4>
	auto arrows(U1&& x1, U2&& y1, U3&& x2, U4&& y2) {
		using Tx1 = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty1 = remove_ptr_t<std::remove_reference_t<U2>>;
		using Tx2 = remove_ptr_t<std::remove_reference_t<U3>>;
		using Ty2 = remove_ptr_t<std::remove_reference_t<U4>>;
		return Arrows<Tx1, Ty1, Tx2, Ty2>(
					optional_ptr<const Tx1>(std::forward<U1>(x1)),
					optional_ptr<const Ty1>(std::forward<U2>(y1)),
					optional_ptr<const Tx2>(std::forward<U3>(x2)),
					optional_ptr<const Ty2>(std::forward<U4>(y2)));
	}
	
	/**
		
	*/
	
}