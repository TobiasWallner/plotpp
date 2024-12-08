
#include <plotpp/Multiplot.hpp>
#include <plotpp/Figure.hpp>

#include <vector>

namespace plotpp{
	
	Multiplot::Multiplot(Text title="")
		: figs_(0)
		, title_(title)
		, rows_(0)
		, columns_(0){
			title_.height = 20;
			title_.bold = true;
		}
	
	Multiplot::Multiplot(size_t rows, size_t columns, Text title) 
		: figs_(rows * columns)
		, title_(title)
		, rows_(rows)
		, columns_(columns){
			title_.height = 20;
			title_.bold = true;
		}

	Figure& Multiplot::at(size_t row, size_t col) {
		const size_t index = col + row * this->columns_;
		return this->figs_[index];
	}
	
	const Figure& Multiplot::at(size_t row, size_t col) const {
		const size_t index = row + col * this->rows_;
		return this->figs_[index];
	}
	
	Multiplot::iterator Multiplot::begin() {return this->figs_.begin();}
	Multiplot::const_iterator Multiplot::begin() const {return this->figs_.begin();}
	Multiplot::const_iterator Multiplot::cbegin() const {return this->figs_.cbegin();}
	
	Multiplot::iterator Multiplot::end() {return this->figs_.end();}
	Multiplot::const_iterator Multiplot::end() const {return this->figs_.end();}
	Multiplot::const_iterator Multiplot::cend() const {return this->figs_.cend();}
	
	size_t Multiplot::size() const {return this->figs_.size();}
	size_t Multiplot::rows() const {return this->rows_;}
	size_t Multiplot::columns() const {return this->columns_;}
	
	void Multiplot::resize(size_t rows, size_t columns){
		this->figs_.resize(rows * columns);
		this->rows_ = rows;
		this->columns_ = columns;
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
		if(filename.empty()) filename = this->title_;
		
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
		
		stream << "set multiplot layout " << this->rows_ << "," << this->columns_ << " title " << this->title_ << "\n\n";
		
		{
			size_t row = 0;
			size_t column = 0;
			for (const auto& fig : this->figs_){
				stream << "\n# Figure at (" << row << ", " << column << ")\n";
				
				fig.plot(stream);
				
				++column;
				if(column >= this->columns_){
					column = 0;
					++row;
				}
			}
		}
		
		stream << "\n";
		stream << "unset multiplot\n";
		if(!saveAs.empty()) stream << "set output\n";
		
		stream.flush();
	}
	
}