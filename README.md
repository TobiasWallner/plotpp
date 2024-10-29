PPlot
=====

A plotting library for C++ that uses Gnuplot as a backend.

Examples
========

You can see all examples in the `examples/` folder.

Line Plot
---------

```C++
using namespace plotpp;
std::vector<double> x(20);
for(size_t i=0; i < x.size(); ++i) x[i] = i;
std::vector<double> y1(20);
for(size_t i=0; i < y1.size(); ++i) y1[i] = 1./i*30;

Figure fig("Line Plot");
fig.add(Line(x, y1, "1/x*30"));
fig.show();
fig.save("line-plot.gp");
fig.save("line-plot.png");
```
![Image of a line plot](images/line-plot.png "Line Plot")

Arrow Plot
----------

```C++
using namespace plotpp;
double arrow_x1[] = {-1, -2, -3, -4, -5};
double arrow_y1[] = {-1, -2, -1, -2, -3};
double arrow_x2[] = {-2, -3, -4, -5, -6};
double arrow_y2[] = {-3, -4, -2, -3, -5};

Figure fig("Arrow-Plot");
fig.add(Arrows(arrow_x1, arrow_y1, arrow_x2, arrow_y2, "arrow plot", DataRelation::relative));
fig.show();
fig.save("arrows.svg");
```

![Image of an arrow plot](images/arrows.svg "Arrows")
