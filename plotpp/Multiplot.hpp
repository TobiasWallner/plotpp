#pragma once

// std
#include <cstdio>
#include <vector>

// plotpp
#include "plotpp/Figure.hpp"

namespace plotpp{
	
	/// @example multiplot.cpp
	
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
		
		/// default constructor
		Multiplot() = default;
	
		/**
			@brief construct with title
			@param title : Text - The title of the multiplot
		*/
		Multiplot(Text title="");
		
		/**
			@brief construct a multiplot
			@param rows : size_t - The number of rows of figures
			@param columns : size_t - The number of columns of figures
			@param title : Text - The title of the multiplot
		*/
		Multiplot(size_t rows, size_t columns, Text title="");
		
		/// move constructor
		Multiplot(Multiplot&&) = default;
		
		/// move assignment
		Multiplot& operator=(Multiplot&&) = default;

		/**
			@brief Access a figure in the multiplot at a specific row and column index
			@param row : size_t - The row index (starts at 0)
			@param col : size_t - The column index (starts at 0)
			@returns Figure& - A reference to the figure at the [row, col] position
		*/
		Figure& at(size_t row, size_t col);
		
		/**
			@brief Access a figure in the multiplot at a specific row and column index
			@param row : size_t - The row index (starts at 0)
			@param col : size_t - The column index (starts at 0)
			@returns Figure& - A reference to the figure at the [row, col] position
		*/
		const Figure& at(size_t row, size_t col) const;
		
		
		///	@returns the start iterator to iterate over the figures (Figure) contained in the multiplot
		iterator begin();
		
		///	@returns the start iterator to iterate over the figures (Figure) contained in the multiplot
		const_iterator begin() const;
		
		///	@returns the start iterator to iterate over the figures (Figure) contained in the multiplot
		const_iterator cbegin() const;
		
		///	@returns the end iterator to iterate over the figures (Figure) contained in the multiplot
		iterator end();
		
		///	@returns the end iterator to iterate over the figures (Figure) contained in the multiplot
		const_iterator end() const;
		
		///	@returns the end iterator to iterate over the figures (Figure) contained in the multiplot
		const_iterator cend() const;
		
		/// @returns the number of figures contained in the multiplot
		size_t size() const;
		
		/// @returns the number of rows contained in the multiplot
		size_t rows() const;
		
		/// @returns the number of columns contained in the multiplot
		size_t columns() const;
		
		/**
			@brief resize the dimensions, number of rows and columns
			@param rows : size_t - the new number of rows
			@param columns : size_t the new number of columns
		*/
		Multiplot& resize(size_t rows, size_t columns);
		
		/**
			@brief Saves a figure to a file like: .png, .svg, .pdf, ... etc.
			@param filename : std::string - The filename as which the plot should be stored in. If the file type is provided in the name (e.g.: image file "*.png", vector graphics "*.svg", gnuplot script "*.gp") the `filetype` and `TerminalType` will be automatically deduced.
			@param filetype : OutputFileType - The output file type like : .png, .svg, .pdf. If set to `OutputFileType::NONE` (default) it is derived from the provided filename ending.
			@param terminalType : TerminalType - The terminal that gnuplot should use to create the file. If set to `TerminalType::NONE` it is derived from the filetype.
		*/
		const Multiplot& save(std::string filename = "", 
					OutputFileType filetype=OutputFileType::NONE, 
					TerminalType terminalType = TerminalType::NONE) const;
					
		inline Multiplot& save(std::string filename = "", 
					OutputFileType filetype=OutputFileType::NONE, 
					TerminalType terminalType = TerminalType::NONE){
			const Multiplot* cthis = this;
			cthis->save(filename, filetype, terminalType);
			return *this;
		}
		
		/**
			@brief Plots or re-plots the figure in a window. 
			@param terminalType : TerminalType - The terminal that gnuplot should use to creat the window and the plot. If `TerminalType::NONE` is provided, then gnuplot's default terminal will be used. 
		*/
		Multiplot& show(TerminalType terminalType = TerminalType::NONE);
		
		/**
			@brief Plots or re-plots the figure in a window.
			
			Like show(TerminalType terminalType) but will infere the terminal-type from the file-type. 
			Except for the gnuplot script file type `OutputFileType::gp`. 
			If that is provided the gnuplot script will be printed to stdout (the command line).
			
			@param filetype : OutputFileType - The file type as which the plot should be made and which should be used to deduce gnuplots plotting terminal from.
		*/
		Multiplot& show(OutputFileType filetype);
		
		
		/**
			@brief Plots the Multiplot to the provided file stream. 
			
			Will be used as a backend of save(std::string, OutputFileType, TerminalType) and show(TerminalType), that create a pipe stream to gnuplot that will then be fed the gnuplot script - so use those functions instead. Alternatively it can be used for debugging by providing stdout to the parameter `fptr` which will print the gnuplot script for the plot to the standard output (command line terminal).
			
			@param fptr : FILE* - A filepointer to which the gnuplot script should be streamed to
			@param terminalType : TerminalType - The terminal type that should be used for the plot. If `TerminalType::NONE` is provided, gnuplot's default one will be used
			@param saveAs : std::string - [You should probably use save(std::string, OutputFileType, TerminalType) instead.] Filename under which to store the figure. If empty nothing will be stored. If not empty a command will be sent to save the current figure under that name. Note that this function will not derive the terminal type or plotting device from the file ending. So providing "plot.png", may not result in a PNG-file, if the wrong `terminalType` has been selected.
		*/
		const Multiplot& plot(
			FILE* fptr, 
			TerminalType terminalType = TerminalType::NONE,
			std::string saveAs = "") const;
			
		Multiplot& plot(
			FILE* fptr, 
			TerminalType terminalType = TerminalType::NONE,
			std::string saveAs = "")
		{
			const Multiplot* cthis = this;
			cthis->plot(fptr, terminalType, saveAs);
			return *this;
		}
		
	};
	
}