#include <plotpp.hpp>
#include <string>
int main(){
	using namespace plotpp;
	
	std::string names[] = {"one", "two", "tree", "four"};
	const std::vector<int> values = {1, 2, 4, 8};
	
	{
		Figure fig("Pie Chart with names");
		fig.add(piechart(&names, &values));
		fig.show();
	}
	
	{
		Figure fig("Pie Chart without names");
		fig.add(piechart(&values));
		fig.show();
	}
	
	return 0;
	
}