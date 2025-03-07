#include <plotpp.hpp>
#include <cmath>
#include "functions.hpp"

int main(){
	using namespace plotpp;
	
	auto x = linspace<float>(-5, 5, 50);
	auto y = sin(x);
	
	Figure("Impulses")
		.add(impulses(std::move(x), std::move(y)))
		.show().save("impulses-plot.svg");
}