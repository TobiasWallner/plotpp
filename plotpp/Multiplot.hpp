/*

set terminal pngcairo size 1000,500
set output 'side_by_side.png'

set multiplot layout 1,2 title "Two Side-by-Side Plots"

# First plot
set title "Sine Function"
set xlabel "x"
set ylabel "sin(x)"
plot sin(x) with lines lw 2 lc rgb "blue"

# Second plot
set title "Cosine Function"
set xlabel "x"
set ylabel "cos(x)"
plot cos(x) with lines lw 2 lc rgb "red"

unset multiplot

*/

/*

For empty plots just print a point into the middle with

$empty << EOD
0 0
EOD

plot $empty with points

*/

#pragma once

#include <vector>

#include <plotpp/Figure.hpp>


namespace plotpp{

	class Multiplot{
	private:
		std::vector<Figure> _figs;
		Text _title;
		size_t _rows = 0;
		size_t _columns = 0;
		
		
	public:
	
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
		
		void show(OutputFileType filetype) const;
		
		void show(TerminalType terminalType = TerminalType::NONE) const;
		
		void save(	std::string filename = "", 
					OutputFileType filetype=OutputFileType::NONE, 
					TerminalType TerminalType = TerminalType::NONE) const;
		
		void plot(
			std::ostream& stream, 
			TerminalType TerminalType = TerminalType::NONE,
			std::string saveAs = "") const;
		
	};
	
}