
#include <plotpp/Multiplot.hpp>
#include <plotpp/Figure.hpp>

#include <vector>


namespace plotpp{
	
	Multiplot::Multiplot(Text title="")
		: _figs(0)
		, _title(title)
		, _rows(0)
		, _columns(0){}
	
	Multiplot::Multiplot(size_t rows, size_t columns, Text title) 
		: _figs(rows * columns)
		, _title(title)
		, _rows(rows)
		, _columns(columns){}

	Figure& Multiplot::at(size_t row, size_t col) {
		const size_t index = col + row * this->_columns;
		return this->_figs[index];
	}
	
	const Figure& Multiplot::at(size_t row, size_t col) const {
		const size_t index = row + col * this->_rows;
		return this->_figs[index];
	}
	
	Multiplot::iterator Multiplot::begin() {return this->_figs.begin();}
	Multiplot::const_iterator Multiplot::begin() const {return this->_figs.begin();}
	Multiplot::const_iterator Multiplot::cbegin() const {return this->_figs.cbegin();}
	
	Multiplot::iterator Multiplot::end() {return this->_figs.end();}
	Multiplot::const_iterator Multiplot::end() const {return this->_figs.end();}
	Multiplot::const_iterator Multiplot::cend() const {return this->_figs.cend();}
	
	size_t Multiplot::size() const {return this->_figs.size();}
	size_t Multiplot::rows() const {return this->_rows;}
	size_t Multiplot::columns() const {return this->_columns;}
	
	void Multiplot::resize(size_t rows, size_t columns){
		this->_figs.resize(rows * columns);
		this->_rows = rows;
		this->_columns = columns;
	}
	
	
	void Multiplot::show(OutputFileType filetype) const {
		if(filetype == OutputFileType::gp){
			this->plot(std::cout, TerminalType::NONE);
		}else{
			this->show(to_terminal(filetype));
		}
	}
			
	void Multiplot::show(TerminalType TerminalType) const {
		opstream gnuplot("gnuplot -persist");
		this->plot(gnuplot, TerminalType);
	}
			
	void Multiplot::save(std::string filename, OutputFileType filetype, TerminalType terminalType) const {
		if(filename.empty()) filename = this->_title;
		
		if(filetype == OutputFileType::NONE){
			filetype = filetype_from_filename(filename);
			if(filetype == OutputFileType::NONE){
				filetype = OutputFileType::png;
				filename += ".png";
			}
		}else if(!filename.ends_with(std::string(to_file_ending(filetype)))){
				filename += to_file_ending(filetype);
		}
		
		if(terminalType == TerminalType::NONE){
			terminalType = to_terminal(filetype);	
		}
		
		if(filetype==OutputFileType::gp){
			std::ofstream fstream(filename);
			this->plot(fstream, terminalType);
		}else{
			opstream gnuplot("gnuplot -persist");
			this->plot(gnuplot, terminalType, filename);	
		}
	}
	
	void Multiplot::plot(std::ostream& stream, TerminalType TerminalType, std::string saveAs) const {
		if(TerminalType != TerminalType::NONE) stream << "set terminal " << to_command(TerminalType) << "\n";
		if(!saveAs.empty()) stream << "set output '" << saveAs << "'\n";
		
		stream << "set multiplot layout " << this->_rows << "," << this->_columns << " title " << this->_title << "\n\n";
		
		{
			size_t row = 0;
			size_t column = 0;
			for (const auto& fig : this->_figs){
				stream << "\n# Figure at (" << row << ", " << column << ")\n";
				
				fig.plot(stream);
				
				++column;
				if(column >= this->_columns){
					column = 0;
					++row;
				}
			}
		}
		
		stream.flush();
		
		if(!saveAs.empty()) stream << "set output ''\n"; // reset the output
	}
	
}