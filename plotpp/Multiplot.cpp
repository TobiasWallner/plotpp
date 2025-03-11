// std
#include <cstdio>
#include <cstdlib>
#include <vector>

// plotpp
#include "plotpp/Multiplot.hpp"
#include "plotpp/Figure.hpp"




namespace plotpp{
	
	Multiplot::Multiplot(Text title)
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


	FILE* Multiplot::gnuplot_pipe() {
		if(this->gnuplot_pipe_ == nullptr){
			#ifdef WIN32
			this->gnuplot_pipe_ = _popen("gnuplot -persist", "w");
			#else
			this->gnuplot_pipe_ = popen("gnuplot -persist", "w");
			#endif
			
		}
		return this->gnuplot_pipe_;
	}

	void Multiplot::close(){
		if(this->gnuplot_pipe_ != nullptr){
			#ifdef WIN32
			const int status = _pclose(this->gnuplot_pipe_);
			#else
			const int status = pclose(this->gnuplot_pipe_);
			#endif	
			
			if (status != 0) {
				throw std::runtime_error("Could not close the pipe stream");
			}
		}
	}

	Figure& Multiplot::at(size_t row, size_t col) {
		const size_t index = col + row * this->columns_;
		return this->figs_[index];
	}
	
	const Figure& Multiplot::at(size_t row, size_t col) const {
		const size_t index = row + col * this->rows_;
		return this->figs_[index];
	}
	
	Multiplot& Multiplot::xLabel(const Text& xlabel){
		for(Figure& fig : *this) fig.xLabel(xlabel);
		return *this;
	}	
	Multiplot& Multiplot::yLabel(const Text& ylabel){
		for(Figure& fig : *this) fig.yLabel(ylabel);
		return *this;
	}
	
	Multiplot& Multiplot::xMin(float v){
		for(Figure& fig : *this) fig.xMin(v);
		return *this;
	}
			
	Multiplot& Multiplot::xMax(float v){
		for(Figure& fig : *this) fig.xMax(v);
		return *this;
	}
	
	Multiplot& Multiplot::yMin(float v){
		for(Figure& fig : *this) fig.yMin(v);
		return *this;
	}
	
	Multiplot& Multiplot::yMax(float v){
		for(Figure& fig : *this) fig.yMax(v);
		return *this;
	}
	
	Multiplot& Multiplot::xlim(float x_min, float x_max){
		for(Figure& fig : *this) fig.xlim(x_min, x_max);
		return *this;
	}
	
	Multiplot& Multiplot::ylim(float y_min, float y_max){
		for(Figure& fig : *this) fig.ylim(y_min, y_max);
		return *this;
	}
	
	Multiplot& Multiplot::lim(float x_min, float x_max, float y_min, float y_max){
		for(Figure& fig : *this) fig.lim(x_min, x_max, y_min, y_max);
		return *this;
	}
	
	
	Multiplot& Multiplot::xLog(bool b){
		for(Figure& fig : *this) fig.xLog(b);
		return *this;
	}
	
	Multiplot& Multiplot::yLog(bool b){
		for(Figure& fig : *this) fig.yLog(b);
		return *this;
	}
	
	Multiplot& Multiplot::xLogBase(float base){
		for(Figure& fig : *this) fig.xLogBase(base);
		return *this;
	}
		
	Multiplot& Multiplot::yLogBase(float base){
		for(Figure& fig : *this) fig.yLogBase(base);
		return *this;
	}
	
	Multiplot& Multiplot::xReverse(bool b){
		for(Figure& fig : *this) fig.xReverse(b);
		return *this;
	}
		
	Multiplot& Multiplot::yReverse(bool b){
		for(Figure& fig : *this) fig.yReverse(b);
		return *this;
	}
	
	Multiplot& Multiplot::showLegend(bool b){
		for(Figure& fig : *this) fig.showLegend(b);
		return *this;
	}
	
	Multiplot& Multiplot::xAutoscale(bool b){
		for(Figure& fig : *this) fig.xAutoscale(b);
		return *this;
	}
		
	Multiplot& Multiplot::yAutoscale(bool b){
		for(Figure& fig : *this) fig.yAutoscale(b);
		return *this;
	}

	Multiplot& Multiplot::autoscale(bool b){
		for(Figure& fig : *this) fig.autoscale(b);
		return *this;
	}
	
	Multiplot& Multiplot::xGrid(bool b){
		for(Figure& fig : *this) fig.xGrid(b);
		return *this;
	}

	Multiplot& Multiplot::yGrid(bool b){
		for(Figure& fig : *this) fig.yGrid(b);
		return *this;
	}
	
	Multiplot& Multiplot::grid(bool b){
		for(Figure& fig : *this) fig.grid(b);
		return *this;
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
	
	Multiplot& Multiplot::resize(size_t rows, size_t columns){
		this->figs_.resize(rows * columns);
		this->rows_ = rows;
		this->columns_ = columns;
		return *this;
	}
			
	const Multiplot& Multiplot::save(std::string filename, OutputFileType filetype, TerminalType terminalType) const {
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
			
			#if (defined(__STDC_LIB_EXT1__) && (__STDC_WANT_LIB_EXT1__ == 1)) || defined(_MSC_VER)
				FILE* fptr = nullptr;
				errno_t error = fopen_s(&fptr, filename.c_str(), "w");
				if(0 != error){
					fmt::println(stderr, 
					"Error [plotpp]: could not open the file '{}' for saving.\n"
					"  fopen_s returned the error code: {}\n"
					"  In file: {}, at line: {}", 
					filename, static_cast<int>(error), __FILE__, __LINE__);
					return *this;
				}
			#else
				FILE* fptr = fopen(filename.c_str(), "w");
			#endif
			
			this->plot(fptr, terminalType);
			fclose(fptr);
		}else{
			
			#ifdef WIN32
			FILE* fptr = _popen("gnuplot -persist", "w");
			#else
			FILE* fptr = popen("gnuplot -persist", "w");
			#endif
			
			if (fptr == nullptr) {
				throw std::runtime_error("Could not open the pipe stream: 'gnuplot -persist'");
			}
			
			this->plot(fptr, terminalType, filename);	
			
			#ifdef WIN32
			const int status = _pclose(fptr);
			#else
			const int status = pclose(fptr);
			#endif	
			
			if (status != 0) {
				throw std::runtime_error("Could not close the pipe stream");
			}
		}
		return *this;
	}	
	
	Multiplot& Multiplot::show(OutputFileType filetype) {
		if(filetype == OutputFileType::gp){
			this->plot(stdout, TerminalType::NONE);
		}else{
			this->show(to_terminal(filetype));
		}
		return *this;
	}
			
	Multiplot& Multiplot::show(TerminalType TerminalType) {
		this->plot(this->gnuplot_pipe(), TerminalType);
		return *this;
	}
	
	const Multiplot& Multiplot::plot(FILE* fptr, TerminalType TerminalType, std::string saveAs) const {
		if(TerminalType != TerminalType::NONE) fmt::print(fptr, "set terminal {:s}\n", to_command(TerminalType));
		if(!saveAs.empty()) fmt::print(fptr, "set output '{}'\n", saveAs);
		
		fmt::print(fptr, "set multiplot layout {:d},{:d} title {}\n\n", this->rows_, this->columns_, this->title_);
		
		{
			size_t row = 0;
			size_t column = 0;
			for (const auto& fig : this->figs_){
				fmt::print(fptr, "\n# Figure at ({:d}, {:d})\n", row, column);
				
				fig.plot(fptr);
				
				++column;
				if(column >= this->columns_){
					column = 0;
					++row;
				}
			}
		}
		
		fmt::print(fptr, "\nunset multiplot\n");
		if(!saveAs.empty()) fmt::print(fptr, "set output\n");
		std::fflush(fptr);
		
		return *this;
	}
	
}