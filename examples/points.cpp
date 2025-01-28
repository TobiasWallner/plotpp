#include <vector>
#include <list>
#include <plotpp.hpp>

#include "functions.hpp" //linspace, apply_func

int main() {
	
	/* Plotting values from different container types */
	std::vector<float> x = linspace<float>(-2, 2, 50);
	std::list<double> y;
	for(const auto& xi : x) y.emplace_back(-xi + xi* xi * xi);
	
	using namespace plotpp;
	
	/* Plotting points */
	Figure("Point Plot from Y")
		.add(points(&y).label("f1").color(Color(0.8, 0.2, 0.2)))
		.grid().show().save("point-plot.svg");
	
    return 0;
}
