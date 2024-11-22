#include <plotpp.hpp>

int main(){
	using namespace plotpp;
	
	double x[] = {0.0, 10.0, 100.0, 1000.0, 10000.0};
	
	Figure fig("logx");
	fig.add(line(&x, &x));
	fig.logx();
	fig.show();
	
	fig.title("logy");
	fig.logx(false);
	fig.logy();
	fig.show();
	
	fig.title("logxy");
	fig.logx();
	fig.logy();
	fig.show();
	
	return 0;
	
}