#include <plotpp.hpp>

int main() {
	using namespace plotpp;
	
	int xdata[] = {0, 1, 2, 3, 4, 5, 6};
	float ydata[] = {1.0, 5.5, 7.8, 9.0, 6.0};
	
	float y2data[] = {1.0, 4.5, 7.8, 9.0, 2.0};
	int x2data[] = {3, 4, 5, 7, 8};
	
	Figure fig("Boxes");
	fig.add(boxes(&xdata, &ydata).label("boxes1"));
	fig.add(boxes(&x2data, &y2data).label("boxes2").relativeBoxWidth(false));
	fig.show();
	fig.save("boxes-plot.svg");

	
	Figure fig2("Boxes with text");
	fig2.ylim(0, 10);
	fig2.xtics({"house", "bottel", "basket", "number", "apple"});
	fig2.add(boxes(&ydata).label("boxes with names"));
	fig2.show();
	fig2.save("boxes-with-named-xtics-plot.svg");

    return 0;
}