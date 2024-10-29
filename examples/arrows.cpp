#include <vector>
#include <plotpp.hpp>


int main() {
	using namespace plotpp;
	
	double arrow_x1[] = {-1, -2, -3, -4, -5};
	double arrow_y1[] = {-1, -2, -1, -2, -3};
	double arrow_x2[] = {-2, -3, -4, -5, -6};
	double arrow_y2[] = {-3, -4, -2, -3, -5};
	
	Figure fig("Arrow-Plot");
	fig.add(Arrows(arrow_x1, arrow_y1, arrow_x2, arrow_y2, "arrow plot", DataRelation::relative));
	fig.show();
	fig.save("arrows.svg");
	
    return 0;
}