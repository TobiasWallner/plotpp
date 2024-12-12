#include <plotpp.hpp>

#include <list>
#include <vector>
#include <array>

int main(){
	using namespace plotpp;
	
	std::list<int> x({1, 2, 3, 4, 5, 6});
	std::vector<float> y({1.1f, 5.5f, 7.7f, 9.9f, 12.1f, 14.3f});
	std::array<double, 6> err({0.1, 0.5, 0.7, 0.9, 1.1, 1.3});
	
	Figure fig("XError from Different Containers");
	fig.add(xerror(&x, std::move(y), &err).color(Color(0.5, 0.5, 0.0)));
	fig.show();
	
	return 0;
}