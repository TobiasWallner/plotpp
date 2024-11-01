#include <vector>
#include <plotpp.hpp>

int main() {
	using namespace plotpp;

	std::vector<double> x(20);
	for(size_t i=0; i < x.size(); ++i) x[i] = i;
	
	std::vector<double> y1(20);
	for(size_t i=0; i < y1.size(); ++i) y1[i] = 1./i*30;
	
	std::vector<double> y2(20);
	for(size_t i=0; i < y2.size(); ++i) y2[i] = 1./(i*i)*30;
	
	double array[/*rows*/4][/*columns*/3] = {
		{1, 2, 3},
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33}
	};

	double arrow_x1[] = {-1, -2, -3, -4, -5};
	double arrow_y1[] = {-1, -2, -1, -2, -3};
	double arrow_x2[] = {-2, -3, -4, -5, -6};
	double arrow_y2[] = {-3, -4, -2, -3, -5};
	
	Figure fig("Title");
	fig.legend = true;
	fig.add(heatmap(array, "Heatmap"));
	fig.add(line(x, y1, "1/x*30"));
	fig.add(points(x, y2, "1/x^2*30"));
	fig.add(arrows(arrow_x1, arrow_y1, arrow_x2, arrow_y2, "arrow plot"));
	
	fig.show();
	fig.save("mixed-plot.gp");
	fig.save("mixed-plot.jpg");
	
    return 0;
}