#pragma once

#include <ostream>
#include <functional>
#include "plotpp/IPlot.hpp"
#include "plotpp/concepts.hpp"

namespace plotpp{
	/*
		Heat Map for custom matrix like objects
	*/
	template<class T>
	class Heatmap : public IPlot{
		optional_ptr<T> _matrix;
		size_t _rows = 0;
		size_t _columns = 0;
		std::function<double(const T&, size_t/*row*/, size_t/*col*/)> _at;
		
	public:

		Heatmap(optional_ptr<T> matrix, size_t rows, size_t columns, std::function<double(const T&, size_t/*row*/, size_t/*col*/)> at)
			: _matrix(std::move(matrix))
			, _rows(rows)
			, _columns(columns)
			, _at(std::move(at))
			{}
		
		// ---- setters getters ----
		
		Heatmap& label(const char* label) & {this->IPlot::label(label); return *this;}
		Heatmap&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		Heatmap& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		Heatmap&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		Heatmap& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		Heatmap&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		// ---- IPlot overloads ----

		virtual void printPlot(FILE* fptr) const {
			fmt::print(fptr, "$d{:d} matrix with image title '{}'", this->IPlot::uid(), this->IPlot::label());
		}
		
		virtual void printData(FILE* fptr) const {
			fmt::print(fptr, "$d{:d} << e\n", this->IPlot::uid());
			
			for(size_t row=0; row < this->_rows; ++row){
				for(size_t col=0; col < this->_columns; ++col){
					fmt::print(fptr, "{} ", this->_at(*(this->_matrix), row, col));
				}
				fmt::print(fptr, "\n");
			}
			fmt::print(fptr, "e\n");
		}
		
	};
	
	// Construction Helper
	template<PtrOrMoved U1>
	auto heatmap(U1&& matrix, size_t rows, size_t columns,
				 std::function<double(const remove_ptr_t<std::remove_reference_t<U1>>&, size_t, size_t)> at,
				 Text title = "") {
		using T = remove_ptr_t<std::remove_reference_t<U1>>;
		return Heatmap<T>(optional_ptr<T>(std::forward<U1>(matrix)), rows, columns, at);
	}
	
	// Construction Helper for common matrix objects with common interfaces
	template<MatrixLike U1>
	auto heatmap(U1&& matrix) 
	{
		using T = std::remove_reference_t<U1>;
		
		auto at = [](const T& matrix, size_t row, size_t col) -> double {
			return static_cast<double>(matrix.at(row, col));
		};
		
		return Heatmap<T>(optional_ptr<T>(std::move<U1>(matrix)), matrix.rows(), matrix.columns(), at);
	}
	
	// Construction Helper for common matrix pointers with common interfaces
	template<MatrixLike U1>
	auto heatmap(U1* matrix) 
	{
		using T = std::remove_reference_t<U1>;
		
		auto at = [](const T& matrix, size_t row, size_t col) -> double {
			return static_cast<double>(matrix.at(row, col));
		};
		
		return Heatmap<T>(optional_ptr<T>(matrix), matrix->rows(), matrix->columns(), at);
	}

	// Construction Helper
	template<class T, size_t ROWS, size_t COLS>
	auto heatmap(const T(*array)[ROWS][COLS]) {
		// Custom Access Function
		auto at = [](const T (&matrix)[ROWS][COLS], size_t row, size_t col) -> double {
			return static_cast<double>(matrix[row][col]);
		};

		return heatmap(array, ROWS, COLS, at);
	}

}