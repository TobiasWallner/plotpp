#include <vector>
#include <plotpp.hpp>

#include "functions.hpp" //linspace, apply_func

int main() {
	
	std::vector<float> x = linspace<float>(-2, 2, 100);
	std::vector<double> y = apply_func(x, [](double x){return -x + x * x * x;});
	
	using namespace plotpp;
	
	Figure fig("Line Plot from XY");
	fig.add(line(&x, std::move(y)).label("f1"));
	fig.grid();
	fig.show();
	fig.save("line-plot.svg");
	
    return 0;
}
