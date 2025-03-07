#include <plotpp.hpp>

#include <list>
#include <vector>
#include <array>

int main(){
	using namespace plotpp;
	
	// data in different containers and datatypes
	std::list<int> x({1, 2, 3, 4, 5, 6});
	std::vector<float> y({1.1f, 5.5f, 7.7f, 9.9f, 12.1f, 14.3f});
	std::array<double, 6> err({1.1, 0.5, 0.9, 0.7, 0.1, 1.3});
	
	// plot from different containers, datatypes, and variable-passing (move or reference)
	Figure fig("XError");
	fig.add(xerror(&x, std::move(y), &err).color(Color(0.5, 0.5, 0.0)));
	fig.show();
	fig.save("xerror-plot.svg");
	
	return 0;
}