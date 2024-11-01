#pragma once

#include <ostream>
#include <functional>
#include "plotpp/IPlot.hpp"

namespace plotpp{

	/*
		   Heatmap for built in array types
	*//*
	template<class T, size_t ROWS=0, size_t COLS=0, bool custom=true>
	class Heatmap : public IPlot{
		   const T (&_matrix)[ROWS][COLS];
	public:

		   Heatmap(const T (&array)[ROWS][COLS], Text title="")
				   : IPlot(std::move(title))
				   , _matrix(array)
		   {}

		   virtual void print_plot(std::ostream& stream) const {
				   stream << "matrix using 2:1:3 with image title '" << this->IPlot::title.str << "'";
		   }

		   virtual void print_data(std::ostream& stream) const {
				   for(size_t col=0; col < COLS; ++col){
						   for(size_t row=0; row < ROWS; ++row){
								   stream << _matrix[row][col] << ' ';
						   }
						   stream << '\n';
				   }
		   }
	};*/
	   
	

	/*
		Heat Map for custom matrix like objects
	*/
	template<class T>
	class Heatmap : public IPlot{
		smartest_pointer<T> _matrix;
		size_t _rows = 0;
		size_t _columns = 0;
		std::function<double(const T&, size_t/*row*/, size_t/*col*/)> _at;
		
	public:

		template<typename U1>
		Heatmap(U1&& matrix, size_t rows, size_t columns, std::function<double(const T&, size_t/*row*/, size_t/*col*/)> at, Text title="")
			: IPlot(std::move(title))
			, _matrix(std::forward<U1>(matrix))
			, _rows(rows)
			, _columns(columns)
			, _at(std::move(at))
			{}
		
		virtual void print_plot(std::ostream& stream) const {
			stream << "matrix with image title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
			for(size_t row=0; row < this->_rows; ++row){
				for(size_t col=0; col < this->_columns; ++col){
					stream << this->_at(*(this->_matrix), row, col) << ' ';
				}
				stream << '\n';
			}
		}
		
	};
	
	// Primary helper constructor function
	template<typename U1>
	auto heatmap(U1&& matrix, size_t rows, size_t columns,
				 std::function<double(const std::remove_reference_t<U1>&, size_t, size_t)> at,
				 Text title = "") {
		using T = std::remove_reference_t<U1>;
		return Heatmap<T>(std::forward<U1>(matrix), rows, columns, at, std::move(title));
	}

	// Helper constructor function for creating a Heatmap from a 2D array
	template<class T, size_t ROWS, size_t COLS>
	auto heatmap(const T(&array)[ROWS][COLS], Text title = "") {
		// Lambda to access elements by row and column in the 2D array
		auto at = [](const T (&matrix)[ROWS][COLS], size_t row, size_t col) -> double {
			return static_cast<double>(matrix[row][col]);
		};

		// Use the primary heatmap helper with array, dimensions, and the lambda
		return heatmap(array, ROWS, COLS, at, std::move(title));
	}

}