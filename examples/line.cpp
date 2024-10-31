#include <vector>
#include <plotpp.hpp>

int main() {
	using namespace plotpp;
	
	std::vector<double> x(20);
	for(size_t i=0; i < x.size(); ++i) x[i] = i;
	
	std::vector<double> y1(20);
	for(size_t i=0; i < y1.size(); ++i) y1[i] = 1./i*30;
	
	Figure fig("Line Plot");
	fig.add(line(x, y1, "1/x*30"));
	fig.show();
	fig.save("line-plot.gp");
	fig.save("line-plot.png");
	
    return 0;
}