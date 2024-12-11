#include "plotpp/Figure.hpp"
#include <cstdlib>
#include <vector>
#include <thread>
#include <future>

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
	
	opstream& Figure::gnuplot() const {
		std::cout << "function: "<< __FUNCTION__ << std::endl;
		if(this->gnuplot_.is_open() == false){
			std::cout << "  if(this->gnuplot_.is_open() == false)" << std::endl;
			/*
			The class Figure, that I am useing is talking to gnuplot over pipestreams, 
			and the figure itself, the data and the plot types will not change, which 
			is what the user will think of when useing the figure. The user will not 
			think about the underlieing communication over pipes with gnuplot. So I 
			think it is ok to violate const there, because all user data will still be 
			kept const and only the setup of a new communication to gnuplot will be a 
			changeing state.
			*/
			const_cast<opstream&>(this->gnuplot_).open("gnuplot -persist");
			
		}
		return const_cast<opstream&>(this->gnuplot_);
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
	
	void Figure::show(OutputFileType filetype) const {
		if(filetype == OutputFileType::gp){
			this->plot(std::cout, TerminalType::NONE);
		}else{
			this->show(to_terminal(filetype));
		}
	}
			
	void Figure::show(TerminalType TerminalType) const {
		this->plot(this->gnuplot(), TerminalType);
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
			std::ofstream fstream(filename);
			this->plot(fstream, terminalType);
		}else{
			this->plot(this->gnuplot(), terminalType, filename);	
		}
	}
	
	void Figure::plot(std::ostream& stream, TerminalType terminalType, std::string saveAs) const {
		{
			size_t i = 0;
			for(const std::shared_ptr<IPlot>& plot : this->plots) plot->uid(i);
		}
		
		if(terminalType != TerminalType::NONE) stream << "set terminal " << to_command(terminalType) << "\n";
		if(!saveAs.empty()) stream << "set output '" << saveAs << "'\n";
		
		if(this->plots.empty()){
			stream << "set xrange [-1 : +1]\n";
			stream << "set yrange [-1 : +1]\n";
			stream << "$empty << EOD\n";
			stream << "0 0\n";
			stream << "EOD\n\n";
			stream << "plot $empty with points notitle\n\n";
			return;
		}
		
		
		// figure and axis configuration
		if(!title_.empty()) stream << "set title " << title_ << "\n";
		if(!xlabel.empty()) stream << "set xlabel " << xlabel << "\n";
		if(!ylabel.empty()) stream << "set ylabel " << ylabel << "\n";
		
		if(this->xautoscale && this->yautoscale){
			stream << "set autoscale\n";	
		}else if(this->xautoscale){
			stream << "set autoscale x\n";
			stream << "set yrange [" << this->ymin << ":" << this->ymax << "]\n";
		}else if(this->yautoscale){
			stream << "set xrange [" << this->xmin << ":" << this->xmax << "]\n";
			stream << "set autoscale y\n";
		}else{
			stream << "set xrange [" << this->xmin << ":" << this->xmax << "]\n";
			stream << "set yrange [" << this->ymin << ":" << this->ymax << "]\n";
		}
		
		if(this->xreverse) stream << "set xrange reverse\n";
		if(this->yreverse) stream << "set yrange reverse\n";
		
		if(this->logx_) stream << "set logscale x " << this->logx_base << "\n";
		if(this->logy_) stream << "set logscale y " << this->logy_base << "\n";
		
		// set x-tics
		if(!this->xtics_labels.empty()){
			auto xlabel_itr = this->xtics_labels.cbegin();
			auto xval_itr = this->xtics_values.cbegin();
			
			stream << "set xtics(";
			
			// TODO: checkout https://github.com/CommitThis/zip-iterator/tree/master
			// for python-zip like iteration through parallel lists
			for(; xlabel_itr != this->xtics_labels.cend() && xval_itr != this->xtics_values.cend(); ++xlabel_itr, (void)++xval_itr){
				if(xlabel_itr != this->xtics_labels.begin()) stream << ", ";
				stream << "\"" << *xlabel_itr << "\" " << *xval_itr;
			}
			stream << ")\n";
		}
		
		// write settings demanded by plots
		{
			auto plt_itr=this->plots.cbegin();
			for(; plt_itr!=this->plots.cend(); ++plt_itr){
				(*plt_itr)->printSettings(stream);
			}
		}

		// write data variables
		{
			auto plt_itr=this->plots.cbegin();
			size_t i = 0;
			for(; plt_itr!=this->plots.cend(); ++plt_itr, (void)++i){
				(*plt_itr)->printData(stream);
			}
		}
		
		

		// write plot commands			
		{
			if(!this->plots.empty()) stream << "plot ";
			auto plot_itr = this->plots.cbegin();
			for(; plot_itr!=this->plots.cend(); ++plot_itr){
				if (plot_itr!=this->plots.cbegin()) stream << "     ";
				(*plot_itr)->printPlot(stream);
				auto next = plot_itr; 
				++next;
				if(next!=this->plots.cend()) stream << ", \\";
				stream << "\n";
			}
		}
		stream << "\n";

		if(!saveAs.empty()) stream << "set output" << std::endl; // reset to default
		
		stream.flush();
	}

}