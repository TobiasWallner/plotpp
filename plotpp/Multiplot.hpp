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