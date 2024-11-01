#include "plotpp/Figure.hpp"
#include <cstdlib>
#include <vector>

namespace plotpp{
		
	Figure::Figure(std::string title_str){
		title.str = title_str;
		title.height = 20;
		title.bold = true;
	}

	Figure::Figure(Text title, Text xlabel, Text ylabel)
		: title(title)
		, xlabel(xlabel)
		, ylabel(ylabel)
	{}
			
	Figure& Figure::add(std::shared_ptr<IPlot>&& plot){
		this->plots.push_back(std::move(plot));
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
		opstream gnuplot("gnuplot -persist");
		this->plot(gnuplot, TerminalType);
	}
			
	void Figure::save(std::string filename, OutputFileType filetype, TerminalType terminalType) const {
		if(filename.empty()) filename = title;
		
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
	
	void Figure::plot(std::ostream& stream, TerminalType terminalType, std::string saveAs) const {
		
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
		if(!title.empty()) stream << "set title " << title << "\n";
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
		
		// write settings demanded by plots
		{
			auto plt_itr=this->plots.cbegin();
			for(; plt_itr!=this->plots.cend(); ++plt_itr){
				(*plt_itr)->print_settings(stream);
			}
		}

		// write data variables
		std::vector<std::string> data_vars;
		data_vars.reserve(this->plots.size());
		{
			auto plt_itr=this->plots.cbegin();
			size_t i = 0;
			
			for(; plt_itr!=this->plots.cend(); ++plt_itr, (void)++i){
				std::string var_name("data");
				
				//generate random number for plot names
				var_name += std::to_string(std::rand());
				
				data_vars.push_back(var_name);
				stream << "$" << var_name << " << EOD\n";
				
				(*plt_itr)->print_data(stream);
				
				stream << "EOD\n\n";
			}	
		}
		
		

		// write plot commands			
		{
			if(!this->plots.empty()) stream << "plot ";
			auto plot_itr = this->plots.cbegin();
			auto var_itr = data_vars.cbegin();
			for(; plot_itr!=this->plots.cend() && var_itr!=data_vars.cend(); ++plot_itr, (void)++var_itr){
				if (plot_itr!=this->plots.cbegin()) stream << "     ";
				stream << "$" << *var_itr << " ";
				(*plot_itr)->print_plot(stream);
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