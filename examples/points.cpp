#include <vector>
#include <plotpp.hpp>

int main() {
	using namespace plotpp;
	std::vector<double> x(20);
	for(size_t i=0; i < x.size(); ++i) x[i] = i;
	
	std::vector<double> y2(20);
	for(size_t i=0; i < y2.size(); ++i) y2[i] = 1./(i*i)*30;
	
	Figure fig("Points-Plot");
	fig.add(points(x, y2, "1/x^2*30"));
	fig.show();
	fig.save("points-plot.gp");
	fig.save("points-plot.png");
	
    return 0;
}