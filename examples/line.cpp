#include <vector>
#include <plotpp.hpp>
#include <memory>
#include <chrono>

#include <fmt/core.h>

int main() {
	using namespace plotpp;
	
	{
		std::vector<double> x(20);
		for(size_t i=0; i < x.size(); ++i) x[i] = i;
		
		std::vector<double> y1(20);
		for(size_t i=0; i < y1.size(); ++i) y1[i] = 1./i*30;
		
		Figure fig("Line Plot from XY");
		fig.add(line(&x, &y1).label("1/x*30"));
		
		{
			
			auto start = std::chrono::high_resolution_clock::now();
			fig.show();
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> duration = end - start;
			fmt::print("fig.show(): execution time: {} s\n", duration.count());
		}
		{
			auto start = std::chrono::high_resolution_clock::now();
			fig.show_fmt();
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> duration = end - start;
			fmt::print("fig.show_fmt(): execution time: {} s\n", duration.count());
		}
		
		//fig.save("line-plot.gp");
		//fig.save("line-plot.png");
	}
	
	{
		std::vector<double> y(20);
		for(size_t i=0; i < y.size(); ++i) y[i] = i*i;
		
		Figure fig("Line Plot from Y");
		fig.add(line(std::move(y)).label("x^2"));
		fig.show();
		//fig.save("line-plot.gp");
		//fig.save("line-plot.png");
	}
    return 0;
}