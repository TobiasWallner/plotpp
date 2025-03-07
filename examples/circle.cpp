#include <plotpp.hpp>

int main(){
	using namespace plotpp;
	
	Figure fig("Circle");
	fig.add(circle(0, 0));
	fig.add(circle(4, 0, 1.8).label("circle 2").color(color_map::reds[3]));
	fig.add(circle(5, 6, 1.8, 30).label("circle 3").lineType(LineType::dashed));
	fig.add(circle(0, 4, 1.8, 100, 160).label("circle 4").fillSolid(0.8));
	fig.add(circle(2, 2, 1.8).label("circle 4").fillPattern(2));
	fig.ylim(-4, 10);
	fig.xlim(-3, 8);
	fig.show();
	fig.save("circle-plot.svg");
	
}