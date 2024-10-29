#pragma once

#include <ostream>

#include "plotpp/IPlot.hpp"

namespace plotpp{


	/*
		Heatmap for built in array types
	*/
	template<class T, size_t ROWS=0, size_t COLS=0>
	class Heatmap : public IPlot{
		const T (&_matrix)[ROWS][COLS];
	public:
		
		Heatmap(const T (&array)[ROWS][COLS], Text title)
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
		
	};

	/*
		Heat Map for custom matrix like objects
	*/
	template<class T>
	class Heatmap<T, 0, 0> : public IPlot{
		T const & _matrix = nullptr;
		size_t _rows = 0;
		size_t _columns = 0;
		double (*_at)(T const * matrix, size_t row, size_t col);
		
	public:

		Heatmap(T const & matrix, size_t rows, size_t columns, double (*at)(T const & matrix, size_t row, size_t col), Text title="")
			: IPlot(std::move(title))
			, _matrix(matrix)
			, _rows(rows)
			, _columns(columns)
			, _at(at)
		{}
		
		virtual void print_plot(std::ostream& stream) const {
			stream << "'-' matrix using 2:1:3 with image title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
			stream << "# Data for " << this->IPlot::title.str << "\n";
			for(size_t col=0; col < this->_columns; ++col){
				for(size_t row=0; row < this->_rows; ++row){
					stream << (this->_at)(this->_matrix, row, col) << ' ';
				}
				stream << '\n';
			}
			stream << "e\n";
		}
		
	};

}