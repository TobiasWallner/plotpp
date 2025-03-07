#include <vector>
#include <plotpp.hpp>

#include "functions.hpp" //linspace, apply_func

int main() {
	
	std::vector<float> x = linspace<float>(-2, 2, 10);
	std::vector<double> y = apply_func(x, [](double x){return -x + x * x * x;});
	std::vector<double> err = apply_func(x, [](double x){return 1.0 + x * x / 2.;});
	
	using namespace plotpp;
	
	Figure fig("Line Plot from XY");
	fig.add(yerrorline(&x, &y, &err).label("f1"));
	fig.grid();
	fig.show();
	fig.save("yerrorline-plot.svg");
	
    return 0;
}
