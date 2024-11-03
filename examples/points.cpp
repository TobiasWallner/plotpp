#include <vector>
#include <plotpp.hpp>

int main() {
	using namespace plotpp;
	
	{
		std::vector<double> x(20);
		for(size_t i=0; i < x.size(); ++i) x[i] = i;
		
		std::vector<double> y2(20);
		for(size_t i=0; i < y2.size(); ++i) y2[i] = 1./(i*i)*30;
		
		Figure fig("Points-Plot from XY values");
		fig.add(points(x, y2).label("1/x^2*30"));
		fig.show();
		//fig.save("points-plot.gp");
		//fig.save("points-plot.png");	
	}
	
	{
		std::vector<double> y(20);
		for(size_t i=0; i < y.size(); ++i) y[i] = i*i;
		
		Figure fig("Points-Plot from Y values");
		fig.add(points(std::move(y)).label("i^2"));
		fig.show();
		//fig.save("points-plot.gp");
		//fig.save("points-plot.png");	
	}
    return 0;
}