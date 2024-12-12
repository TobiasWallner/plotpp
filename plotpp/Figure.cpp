#include "plotpp/Figure.hpp"

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <thread>
#include <future>

// {fmt}
#include <fmt/core.h>

namespace plotpp{
	
	Figure::Figure(std::string title_str){
		title_.str = title_str;
		title_.height = 20;
		title_.bold = true;
	}

	Figure::Figure(Text title, Text xlabel, Text ylabel)
		: title_(title)
		, xlabel(xlabel)
		, ylabel(ylabel)
	{}
	
	Figure::~Figure(){
		this->close_pipe();
	}
	
	void Figure::close_pipe(){
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
	
	FILE* Figure::gnuplot_pipe() {
		if(this->gnuplot_pipe_ == nullptr){
			#ifdef WIN32
			this->gnuplot_pipe_ = _popen("gnuplot -persist", "w");
			#else
			this->gnuplot_pipe_ = popen("gnuplot -persist", "w");
			#endif
		}
		return this->gnuplot_pipe_;
	}
	
	void Figure::close() {
		this->gnuplot_.close();
	}
	
	Figure& Figure::add(std::shared_ptr<IPlot> plot){
		this->plots.push_back(std::move(plot));
		return *this;
	}
	
	void Figure::xtics(std::vector<std::string> tic_labels){
		this->xtics_labels = std::move(tic_labels);
		this->xtics_values.clear();
		for(size_t i = 0; i < this->xtics_labels.size(); ++i){
			this->xtics_values.emplace_back(static_cast<double>(i));
		}
	}
	
	void Figure::xtics(std::vector<std::string> tic_labels, std::vector<double> tic_values){
		this->xtics_labels = std::move(tic_labels);
		this->xtics_values = std::move(tic_values);
	}
	
	void Figure::clear_xtics(){
		this->xtics_labels.clear();
		this->xtics_values.clear();
	}
	
	Figure& Figure::logx(bool v) {
		this->logx_ = v; 
		return *this;
	}
	
	Figure& Figure::logy(bool v) {
		this->logy_ = v; 
		return *this;
	}
	
	Figure& Figure::logx(float v) {
		this->logx_ = true; 
		this->logx_base = v; 
		return *this;
	}
	
	Figure& Figure::logy(float v) {
		this->logy_ = true; 
		this->logy_base = v; 
		return *this;
	}
	
	Figure& Figure::title(const Text& title) {
		this->title_ = title; 
		return *this;
	}
	
	Figure& Figure::title(Text&& title) {
		this->title_ = std::move(title); 
		return *this;
	}
			
	void Figure::save(std::string filename, OutputFileType filetype, TerminalType terminalType) const {
		if(filename.empty()) filename = title_;
		
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
			FILE* fptr = fopen(filename.c_str(), "w");
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
	}
	

	void Figure::show(OutputFileType filetype) {
		if(filetype == OutputFileType::gp){
			this->plot(stdout, TerminalType::NONE);
		}else{
			this->show(to_terminal(filetype));
		}
	}

	void Figure::show(TerminalType TerminalType) {
		FILE* fptr = this->gnuplot_pipe();
		this->plot(fptr, TerminalType);
	}
	
	void Figure::plot(FILE* fptr, TerminalType terminalType, std::string saveAs) const {
		{
			size_t i = 0;
			for(const std::shared_ptr<IPlot>& plot : this->plots) plot->uid(i);
		}
		
		if(terminalType != TerminalType::NONE) fmt::print(fptr, "set terminal {}\n", to_command(terminalType));
		if(!saveAs.empty()) fmt::print(fptr, "set output '{}'\n", saveAs);
		
		if(this->plots.empty()){
			fmt::print(fptr, 
				"set xrange [-1 : +1]\n"
				"set yrange [-1 : +1]\n"
				"$empty << EOD\n"
				"0 0\n"
				"EOD\n\n"
				"plot $empty with points notitle\n\n");
			return;
		}
		
		// figure and axis configuration
		if(!title_.empty()) fmt::print(fptr, "set title {}\n", this->title_);
		if(!xlabel.empty()) fmt::print(fptr, "set xlabel {}\n", this->xlabel);
		if(!ylabel.empty()) fmt::print(fptr, "set ylabel {}\n", this->ylabel);
		
		if(this->xautoscale && this->yautoscale){
			fmt::print(fptr, "set autoscale\n");
		}else if(this->xautoscale){
			fmt::print(fptr, 
				"set autoscale x\n"
				"set yrange [{}:{}]\n",
				this->ymin, this->ymax);
		}else if(this->yautoscale){
			fmt::print(fptr,
				"set xrange [{}:{}]\n"
				"set autoscale y\n",
				this->xmin, this->xmax);
		}else{
			fmt::print(fptr,
				"set xrange [{}:{}]\n"
				"set yrange [{}:{}]\n",
				this->xmin, this->xmax, this->ymin, this->ymax);
		}
		
		// optionally reverse the x and or y axis
		if(this->xreverse) fmt::print(fptr, "set xrange reverse\n");
		if(this->yreverse) fmt::print(fptr, "set yrange reverse\n");
		
		if(this->logx_) fmt::print(fptr, "set logscale x {}\n", this->logx_base);
		if(this->logy_) fmt::print(fptr, "set logscale y {}\n", this->logy_base);
		
		// set x-tics
		if(!this->xtics_labels.empty()){
			auto xlabel_itr = this->xtics_labels.cbegin();
			auto xval_itr = this->xtics_values.cbegin();
			
			fmt::print(fptr, "set xtics(");
			
			// TODO: checkout https://github.com/CommitThis/zip-iterator/tree/master
			// for python-zip like iteration through parallel lists
			for(; xlabel_itr != this->xtics_labels.cend() && xval_itr != this->xtics_values.cend(); ++xlabel_itr, (void)++xval_itr){
				const char* seperator = (xlabel_itr != this->xtics_labels.begin()) ? ", " : "";
				fmt::print(fptr, "{}\"{}\" {}", seperator, *xlabel_itr, *xval_itr);
			}
			
			fmt::print(fptr, ")\n");
		}
		
		// write settings demanded by plots
		{
			auto plt_itr=this->plots.cbegin();
			for(; plt_itr!=this->plots.cend(); ++plt_itr){
				(*plt_itr)->printSettings(fptr);
			}
		}
		
		// write data variables
		{
			auto plt_itr=this->plots.cbegin();
			size_t i = 0;
			for(; plt_itr!=this->plots.cend(); ++plt_itr, (void)++i){
				(*plt_itr)->printData(fptr);
			}
		}
		
		// write plot commands			
		{
			if(!this->plots.empty()) fmt::print(fptr, "plot ");
			auto plot_itr = this->plots.cbegin();
			for(; plot_itr!=this->plots.cend(); ++plot_itr){
				if (plot_itr!=this->plots.cbegin()) fmt::print(fptr, "     ");
				(*plot_itr)->printPlot(fptr);
				
				auto next = plot_itr; 
				++next;
				
				if(next!=this->plots.cend()) fmt::print(fptr, ", \\");
				fmt::print(fptr, "\n");
			}
		}
		fmt::print(fptr, "\n");
		
		if(!saveAs.empty()) fmt::print(fptr, "set output\n"); // reset to default
		
		std::fflush(fptr);
	}

}