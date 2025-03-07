#include <plotpp.hpp>

#include <list>
#include <vector>
#include <array>

int main(){
	using namespace plotpp;
	
	std::list<int> x({1, 2, 3, 4, 5, 6});
	std::vector<float> y({1.1f, 5.5f, 7.7f, 9.9f, 12.1f, 14.3f});
	std::array<double, 6> err({1., 5./2., 7./2., 9./2., 11./2., 3./2.});
	
	Figure fig("YError");
	fig.add(yerror(&x, std::move(y), &err));
	fig.show();
	fig.save("yerror-plot.svg");
	
	return 0;
}