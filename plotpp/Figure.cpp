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
		, xlabel_(xlabel)
		, ylabel_(ylabel)
	{}
	
	Figure::~Figure(){
		this->close_pipe();
	}
	
	
	Figure& Figure::title(const Text& title) {this->title_ = title; return *this;}
	Figure& Figure::title(Text&& title) {this->title_ = std::move(title); return *this;}
	
	Figure& Figure::xLabel(const Text& xlabel) {this->xlabel_ = xlabel; return *this;}
	Figure& Figure::xLabel(Text&& xlabel) {this->xlabel_ = std::move(xlabel); return *this;}
	Figure& Figure::yLabel(const Text& ylabel) {this->ylabel_ = ylabel; return *this;}
	Figure& Figure::yLabel(Text&& ylabel) {this->ylabel_ = std::move(ylabel); return *this;}
			
	Figure& Figure::xMin(float v){this->min_x_ = v; return *this;}
	Figure& Figure::xMax(float v){this->max_x_ = v; return *this;}
	Figure& Figure::yMin(float v){this->min_y_ = v; return *this;}
	Figure& Figure::yMax(float v){this->max_y_ = v; return *this;}
	
	Figure& Figure::xLogBase(float base){this->log_x_base_ = base; return *this;}
	Figure& Figure::yLogBase(float base){this->log_y_base_ = base; return *this;}
	
	Figure& Figure::xReverse(bool b){this->reverse_x_ = b; return *this;}
	Figure& Figure::yReverse(bool b){this->reverse_y_ = b; return *this;}
	
	Figure& Figure::xAutoscale(bool b){this->autoscale_x_ = b; return *this;}
	Figure& Figure::yAutoscale(bool b){this->autoscale_y_ = b; return *this;}
	
	Figure& Figure::xLog(bool b){this->log_x_ = b; return *this;}
	Figure& Figure::yLog(bool b){this->log_y_ = b; return *this;}
	
	Figure& Figure::showLegend(bool b){this->show_legend_ = b; return *this;}
	
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
		this->plots_.push_back(std::move(plot));
		return *this;
	}
	
	void Figure::xtics(std::vector<std::string> tic_labels){
		this->xtics_labels_ = std::move(tic_labels);
		this->xtics_values_.clear();
		for(size_t i = 0; i < this->xtics_labels_.size(); ++i){
			this->xtics_values_.emplace_back(static_cast<double>(i));
		}
	}
	
	void Figure::xtics(std::vector<std::string> tic_labels, std::vector<double> tic_values){
		this->xtics_labels_ = std::move(tic_labels);
		this->xtics_values_ = std::move(tic_values);
	}
	
	void Figure::clear_xtics(){
		this->xtics_labels_.clear();
		this->xtics_values_.clear();
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
			for(const std::shared_ptr<IPlot>& plot : this->plots_) plot->uid(i);
		}
		
		if(terminalType != TerminalType::NONE) fmt::print(fptr, "set terminal {}\n", to_command(terminalType));
		if(!saveAs.empty()) fmt::print(fptr, "set output '{}'\n", saveAs);
		
		if(this->plots_.empty()){
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
		if(!xlabel_.empty()) fmt::print(fptr, "set xlabel {}\n", this->xlabel_);
		if(!ylabel_.empty()) fmt::print(fptr, "set ylabel {}\n", this->ylabel_);
		
		if(this->autoscale_x_ && this->autoscale_y_){
			fmt::print(fptr, "set autoscale\n");
		}else if(this->autoscale_x_){
			fmt::print(fptr, 
				"set autoscale x\n"
				"set yrange [{}:{}]\n",
				this->min_y_, this->max_y_);
		}else if(this->autoscale_y_){
			fmt::print(fptr,
				"set xrange [{}:{}]\n"
				"set autoscale y\n",
				this->min_x_, this->max_x_);
		}else{
			fmt::print(fptr,
				"set xrange [{}:{}]\n"
				"set yrange [{}:{}]\n",
				this->min_x_, this->max_x_, this->min_y_, this->max_y_);
		}
		
		// optionally reverse the x and or y axis
		if(this->reverse_x_) fmt::print(fptr, "set xrange reverse\n");
		if(this->reverse_y_) fmt::print(fptr, "set yrange reverse\n");
		
		if(this->log_x_) fmt::print(fptr, "set logscale x {}\n", this->log_x_base_);
		if(this->log_y_) fmt::print(fptr, "set logscale y {}\n", this->log_y_base_);
		
		// set x-tics
		if(!this->xtics_labels_.empty()){
			auto xlabel_itr = this->xtics_labels_.cbegin();
			auto xval_itr = this->xtics_values_.cbegin();
			
			fmt::print(fptr, "set xtics(");
			
			// TODO: checkout https://github.com/CommitThis/zip-iterator/tree/master
			// for python-zip like iteration through parallel lists
			for(; xlabel_itr != this->xtics_labels_.cend() && xval_itr != this->xtics_values_.cend(); ++xlabel_itr, (void)++xval_itr){
				const char* seperator = (xlabel_itr != this->xtics_labels_.begin()) ? ", " : "";
				fmt::print(fptr, "{}\"{}\" {}", seperator, *xlabel_itr, *xval_itr);
			}
			
			fmt::print(fptr, ")\n");
		}
		
		// write settings demanded by plots_
		{
			auto plt_itr=this->plots_.cbegin();
			for(; plt_itr!=this->plots_.cend(); ++plt_itr){
				(*plt_itr)->printSettings(fptr);
			}
		}
		
		// write data variables
		{
			auto plt_itr=this->plots_.cbegin();
			size_t i = 0;
			for(; plt_itr!=this->plots_.cend(); ++plt_itr, (void)++i){
				(*plt_itr)->printData(fptr);
			}
		}
		
		// write plot commands			
		{
			if(!this->plots_.empty()) fmt::print(fptr, "plot ");
			auto plot_itr = this->plots_.cbegin();
			for(; plot_itr!=this->plots_.cend(); ++plot_itr){
				if (plot_itr!=this->plots_.cbegin()) fmt::print(fptr, "     ");
				(*plot_itr)->printPlot(fptr);
				
				auto next = plot_itr; 
				++next;
				
				if(next!=this->plots_.cend()) fmt::print(fptr, ", \\");
				fmt::print(fptr, "\n");
			}
		}
		fmt::print(fptr, "\n");
		
		if(!saveAs.empty()) fmt::print(fptr, "set output\n"); // reset to default
		
		std::fflush(fptr);
	}

}