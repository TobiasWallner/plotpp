#include "plotpp/Figure.hpp"

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
			
	Figure& Figure::add(std::unique_ptr<IPlot>&& plot){
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
			stream << 	"set xrange [-1 : +1]\n"
						"set yrange [-1 : +1]\n"
						"$empty << EOD\n"
						"0 0\n"
						"EOD\n"
						"\n"
						"plot $empty with points notitle\n\n";	
			return;
		}
		
		
		// figure and axis configuration
		if(!title.empty()) stream << "set title " << title << "\n";
		if(!xlabel.empty()) stream << "set xlabel " << xlabel << "\n";
		if(!ylabel.empty()) stream << "set ylabel " << ylabel << "\n";
			
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
				var_name += std::to_string(i);
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
		
		if(!saveAs.empty()) stream << "set output\n"; // reset to default
		
		stream.flush();
	}

}