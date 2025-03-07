#include <plotpp.hpp>

#include <list>
#include <vector>
#include <array>

int main(){
	using namespace plotpp;
	
	std::list<int> x({1, 2, 3, 4, 5, 6});
	std::vector<float> y({1.1f, 5.5f, 7.7f, 9.9f, 12.1f, 14.3f});
	std::array<double, 6> err({0.1f, 0.5f, 0.7f, 0.9f, 0.1f, 0.43f});
	
	Figure fig("YError");
	fig.add(xyerror(&x, std::move(y), &err, &err));
	fig.show();
	fig.save("xyerror-plot.svg");
	
	return 0;
}