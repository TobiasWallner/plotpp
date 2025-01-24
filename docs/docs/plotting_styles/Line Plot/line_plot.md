Line Plot
=========

Example
-------
```C++
#include <vector>
#include <plotpp.hpp>

int main() {
	// create data
	std::vector<double> y(20);
	for(size_t i=0; i < y.size(); ++i) y[i] = i*i;
	
	// create figure
	Figure fig("Line Plot from Y");
	fig.add(line(std::move(y)).label("x^2").color(0.8, 0.1, 0.1));
	fig.show();
	
    return 0;
}
```

Construction
------------

Create a line from y-values only.
Accepts non-owning raw pointers and moved containers with `begin()` and `end()` iterators.
```C++
template<PtrOrMoved Uy> auto line(Uy&& y)
```

Create a line from x and y-values.
Accepts non-owning raw pointers and moved containers with `begin()` and `end()` iterators.
Containers can be of different type.
```C++
template<PtrOrMoved Ux, PtrOrMoved Uy> auto line(Ux&& x, Uy&& y) 
```

Methods
-------

