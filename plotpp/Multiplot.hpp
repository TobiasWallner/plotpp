#pragma once

#include <vector>

#include <plotpp/Figure.hpp>

namespace plotpp{

	class Multiplot{
	private:
		std::vector<Figure> figs_;
		Text title_;
		size_t rows_ = 0;
		size_t columns_ = 0;
		FILE* gnuplot_pipe_ = nullptr;
		
	public:
	
	private:
		/** gets the current pipe to the current figure or opens a new one */
		FILE* gnuplot_pipe();
	public:
		/**
			closes this figure. following calls to show() will thus create a new window.
			closes the pipe stream to the curren figure / gnuplot scession;
		*/
		void close();
	
		using iterator = std::vector<Figure>::iterator;
		using const_iterator = std::vector<Figure>::const_iterator;
	
		Multiplot() = default;
	
		Multiplot(Text title);
		
		Multiplot(size_t rows, size_t columns, Text title="");
			
		Multiplot(Multiplot&&) = default;
		
		Multiplot& operator=(Multiplot&&) = default;

		Figure& at(size_t row, size_t col);
		
		const Figure& at(size_t row, size_t col) const;
		
		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;
		
		size_t size() const;
		size_t rows() const;
		size_t columns() const;
		
		void resize(size_t rows, size_t columns);
		
		
		void save(	std::string filename = "", 
					OutputFileType filetype=OutputFileType::NONE, 
					TerminalType TerminalType = TerminalType::NONE) const;
		
			
		void show(OutputFileType filetype);
		
		void show(TerminalType terminalType = TerminalType::NONE);
		
		void plot(
			FILE* fptr, 
			TerminalType TerminalType = TerminalType::NONE,
			std::string saveAs = "") const;
		
	};
	
}