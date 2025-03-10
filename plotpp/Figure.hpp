#pragma once

// std
#include <cstdio>
#include <memory>
#include <string>
#include <list>
#include <vector>

// plotpp
#include "plotpp/TerminalType.hpp"
#include "plotpp/OutputFileType.hpp"
#include "plotpp/Text.hpp"
#include "plotpp/IPlot.hpp"
#include "plotpp/concepts.hpp"

namespace plotpp{

	

	class Figure{
	public:
	
		Figure() = default;
		Figure(const Figure&) = delete;
		Figure(Figure&&) = default;
		
		Figure(std::string title_str);
		
		Figure(Text title, Text xlabel, Text ylabel);
		
		~Figure();
		
		Figure& title(const Text& title);
		Figure& title(Text&& title);
		
		Figure& xLabel(const Text& xlabel);
		Figure& xLabel(Text&& xlabel);
		
		Figure& yLabel(const Text& ylabel);
		Figure& yLabel(Text&& ylabel);
	
		Figure& xMin(float v);
		Figure& xMax(float v);
		Figure& yMin(float v);
		Figure& yMax(float v);
		
		Figure& xlim(float x_min, float x_max);
		Figure& ylim(float y_min, float y_max);
		Figure& lim(float x_min, float x_max, float y_min, float y_max);

		Figure& xLog(bool b = true);
		Figure& yLog(bool b = true);
		
		Figure& xLogBase(float base);
		Figure& yLogBase(float base);
		
		Figure& xReverse(bool b = true);
		Figure& yReverse(bool b = true);
		
		Figure& xAutoscale(bool b = true);
		Figure& yAutoscale(bool b = true);
		Figure& autoscale(bool b = true);
		
		Figure& xGrid(bool b = true);
		Figure& yGrid(bool b = true);
		Figure& grid(bool b = true);
		
		Figure& showLegend(bool b = true);
		
		FILE* get_gnuplot_pipe();
		void close_gnuplot_pipe();
	
		template<class T>
		Figure& add(std::shared_ptr<T> plot){
			std::shared_ptr<IPlot> p = std::move(plot);
			this->add(std::move(p));
			return *this;
		}
		
		template<class T>
		Figure& add(T&& plot){
			using rrT = std::remove_reference_t<T>;
			this->add(std::move(std::make_shared<rrT>(std::forward<rrT>(plot))));
			return *this;
		}
		
		Figure& add(std::shared_ptr<IPlot> plot);
		
		Figure& xtics(std::vector<std::string> tic_labels);
		
		template<class T>
		Figure& xtics(const T& tic_labels){
			auto itr = std::begin(tic_labels);
			const auto end = std::end(tic_labels);
			size_t i = 0;
			this->clear_xtics();
			for(; itr != end; ++itr, (void)++i){
				this->xtics_labels_.emplace_back(*itr);
				this->xtics_values_.emplace_back(static_cast<double>(i));
			}
			return *this;
		}
		
		Figure& xtics(std::vector<std::string> tic_labels, std::vector<double> values);
		
		template<ForwardRange T>
		Figure& xtics(const T& tic_labels, std::vector<double> values){
			auto labels_itr = std::begin(tic_labels);
			const auto labels_end = std::end(tic_labels);
			
			auto values_itr = std::begin(values);
			const auto values_end = std::end(values);
			
			this->clear_xtics();
			for(; labels_itr != labels_end && values_itr != values_end; ++labels_itr, (void)++values_itr){
				this->xtics_labels_.emplace_back(*labels_itr);
				this->xtics_values_.emplace_back(static_cast<double>(*values_itr));
			}
			return *this;
		}
		
		Figure& clear_xtics();
		
		const Figure& save(std::string filename = "", 
					OutputFileType filetype=OutputFileType::NONE, 
					TerminalType terminalType = TerminalType::NONE) const;
					
		inline Figure& save(std::string filename = "", 
					OutputFileType filetype=OutputFileType::NONE, 
					TerminalType terminalType = TerminalType::NONE){
			const Figure* cthis = this;
			cthis->save(filename, filetype, terminalType);
			return *this;
		}
		
		Figure& show(OutputFileType filetype);
		
		Figure& show(TerminalType terminalType = TerminalType::NONE);

		const Figure& plot(
			FILE* fptr, 
			TerminalType terminalType = TerminalType::NONE,
			std::string saveAs = "") const;
			
		inline Figure& plot(
			FILE* fptr, 
			TerminalType terminalType = TerminalType::NONE,
			std::string saveAs = "")
		{
			const Figure* cthis = this;
			cthis->plot(fptr, terminalType, saveAs);
			return *this;
		}
		
	private:
		std::list<std::shared_ptr<IPlot>> plots_;
		
		Text title_;
		Text xlabel_;
		Text ylabel_;
		
		std::vector<std::string> xtics_labels_;
		std::vector<double> xtics_values_;
		
		FILE* gnuplot_pipe_ = nullptr;
		
		float min_x_ = -1;
		float max_x_ = +1;
		float min_y_ = -1;
		float max_y_ = +1;
		
		float log_x_base_ = 10.0;
		float log_y_base_ = 10.0;
		
		bool autoscale_x_ = true;
		bool autoscale_y_ = true;
		
		bool reverse_x_ = false;
		bool reverse_y_ = false;
		
		bool show_legend_ = false;
		
		bool log_x_ = false;
		bool log_y_ = false;
		
		bool grid_x_ = false;
		bool grid_y_ = false;
		
	};
	
}