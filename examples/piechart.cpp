#include <plotpp.hpp>
#include <string>
int main(){
	using namespace plotpp;
	
	std::string names[] = {"one", "two", "tree", "four"};
	const std::vector<int> values = {1, 2, 4, 8};
	
	Figure("Pie Chart")
		.add(piechart(&names, &values))
		.lim(-2, 2, -2, 2)
		.show()
		.save("piechart-plot.svg");

	return 0;
	
}