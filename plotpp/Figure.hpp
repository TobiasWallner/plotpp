#pragma once

#include <memory>
#include <string>
#include <list>
#include <ostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <atomic>
#include <thread>

#include "opstream.hpp"

#include "plotpp/TerminalType.hpp"
#include "plotpp/OutputFileType.hpp"
#include "plotpp/Text.hpp"
#include "plotpp/IPlot.hpp"
#include "plotpp/concepts.hpp"

namespace plotpp{

	

	class Figure{
	public:
		std::list<std::shared_ptr<IPlot>> plots;
		
		Text title_;
		Text xlabel;
		Text ylabel;
		
		std::vector<std::string> xtics_labels;
		std::vector<double> xtics_values;
		
		opstream gnuplot_;
		
		float xmin = -1;
		float xmax = +1;
		float ymin = -1;
		float ymax = +1;
		
		float logx_base = 10.0;
		float logy_base = 10.0;
		
		bool xautoscale = true;
		bool yautoscale = true;
		
		bool yreverse = false;
		bool xreverse = false;
		
		bool legend = false;
		
		bool logx_ = false;
		bool logy_ = false;
		
		Figure() = default;
		Figure(const Figure&) = delete;
		Figure(Figure&&)=default;
		
		Figure(std::string title_str);
		
		Figure(Text title, Text xlabel, Text ylabel);
		
	public:
	
	
	private:
		/**
			return the current pipe stream to gnuplot or creates one.
		*/
		opstream& gnuplot() const;
	public:
		/**
			closes this figure. following calls to show() will thus create a new window.
			closes the pipe stream to the curren figure / gnuplot scession;
		*/
		void close();
	
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
		
		void xtics(std::vector<std::string> tic_labels);
		
		template<class T>
		void xtics(const T& tic_labels){
			auto itr = std::begin(tic_labels);
			const auto end = std::end(tic_labels);
			size_t i = 0;
			this->clear_xtics();
			for(; itr != end; ++itr, (void)++i){
				this->xtics_labels.emplace_back(*itr);
				this->xtics_values.emplace_back(static_cast<double>(i));
			}
		}
		
		void xtics(std::vector<std::string> tic_labels, std::vector<double> values);
		
		template<ForwardRange T>
		void xtics(const T& tic_labels, std::vector<double> values){
			auto labels_itr = std::begin(tic_labels);
			const auto labels_end = std::end(tic_labels);
			
			auto values_itr = std::begin(values);
			const auto values_end = std::end(values);
			
			this->clear_xtics();
			for(; labels_itr != labels_end && values_itr != values_end; ++labels_itr, (void)++values_itr){
				this->xtics_labels.emplace_back(*labels_itr);
				this->xtics_values.emplace_back(static_cast<double>(*values_itr));
			}
		}
		
		void clear_xtics();
		
		Figure& logx(bool v = true);
		Figure& logy(bool v = true);
		Figure& logx(float v);
		Figure& logy(float v);
		
		Figure& title(const Text& title);
		Figure& title(Text&& title);
		
		void show(OutputFileType filetype) const;
		
		void show(TerminalType terminalType = TerminalType::NONE) const;
		
		void save(	std::string filename = "", 
					OutputFileType filetype=OutputFileType::NONE, 
					TerminalType terminalType = TerminalType::NONE) const;

		void plot(
			std::ostream& stream, 
			TerminalType terminalType = TerminalType::NONE,
			std::string saveAs = "") const;
		
	};
	
}