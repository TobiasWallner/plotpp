#include <vector>
#include <plotpp.hpp>


int main() {
	using namespace plotpp;
	
	double arrow_x1[] = {-1, -2, -3, -4, -5};
	double arrow_y1[] = {-1, -2, -1, -2, -3};
	double arrow_x2[] = {-2, -3, -4, -5, -6};
	double arrow_y2[] = {-3, -4, -2, -3, -5};
	
	Figure("Arrow-Plot")
		.add(arrows(&arrow_x1, &arrow_y1, &arrow_x2, &arrow_y2).label("arrow plot"))
		.show()
		.save("arrows-plot.svg");
	/*
	Figure("Vector-Plot")
		.add(vector(&arrow_x1, &arrow_y1, &arrow_x2, &arrow_y2).label("vector plot"));
		.show();
		.save("vector-plot.svg");
	
	Figure("Quiver-Plot")
		.add(quiver(&arrow_x1, &arrow_y1, &arrow_x2, &arrow_y2).label("quiver plot"));
		.show();
		.save("quiver-plot.svg");
	*/
	
    return 0;
}