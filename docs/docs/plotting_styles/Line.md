# Line Plot
----

In header: `<plotpp/Line.hpp>`  
In namespace: `plotpp::`

## Example
----

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

![Image of a line plot](line-plot.svg)

## Construction Helpers
----

### Function: line()
----

```C++
/* 1 */ template<PtrOrMoved Uy> auto line(Uy&& y);
/* 2 */ template<PtrOrMoved Ux, PtrOrMoved Uy> auto line(Ux&& x, Uy&& y);
```

1. Create a Line from y-values only.
2. Create a Line from x and y-values.

Accepts non-owning raw pointers and moved containers with `begin()` and `end()` iterators.
Containers can be of different type.


## Class Line
----

```C++
template<std::ranges::forward_range Tx, std::ranges::forward_range Ty>
class Line : public IPlot;
```

Contains information on how to draw a line in a [Figure](Figure.md).
Inherrits from [IPlot](TODO).

### Constructor

```C++
Line(optional_ptr<Tx> x, optional_ptr<Ty> y);
```

Constructs a Line from two [optional_ptr](TODO) containing the x- and y-coordinates to draw the line. 

**Parameter:** [optional_ptr](TODO)<Tx, Ty> **x, y:** The x- and y-coordinates to draw the line. The x-values are optional and may be assigned a `nullptr`. The y-values are mandatory. The Tx- and Ty-types for the x- and y-values have to be [std::ranges::forward_range](https://en.cppreference.com/w/cpp/ranges/forward_range) (aka. have `begin()` and `end()` iterators that allow incrementation with the `operator++`) as per the classes template definition.

### Line.lineType()
----

```C++
LineType lineType() const;
```
**Returns:** [LineType](LineType.md#Enum-LineType): returns the line type



```C++
Line& lineType(LineType lt) &;
Line&& lineType(LineType lt) &&;
```
**Parameter:** [LineType](LineType.md#Enum-LineType) **lt:** sets the line type  
**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.lineWidth()
----

```C++
float lineWidth() const;
```
**Returns:** float: returns the line width

```C++
Line& lineWidth(float lw) &;
Line&& lineWidth(float lw) &&;
```

Sets the line width.

**Parameter:** [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **lw:** The new line width  
**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.lineColor()
----

```C++
Color lineColor() const;
```

**Returns:** [Color](TODO): Returns the color of the line

```C++
/* 1 */ Line& lineColor(Color col) &;
/* 2 */ Line&& lineColor(Color col) &&;
/* 3 */ Line& lineColor(float r, float g, float b) &;
/* 4 */ Line&& lineColor(float r, float g, float b) &&;		
```

Sets the dash color of the line.

**Parameter (1 and 2):** [Color](TODO) **col:** The new line color  
**Parameter (3 and 4):**

- [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **r:** red color component in a range from [0, 1]
- [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **g:** green color component in a range from [0, 1]
- [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **b:** blue color component in a range from [0, 1]

**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.fillColor()
----

```C++
Color fillColor() const;
```

**Returns:** [Color](TODO): returns the color of the fill

```C++
/* 1 */ Line& fillColor(Color col) &;
/* 2 */ Line&& fillColor(Color col) &&;
/* 3 */ Line& fillColor(float r, float g, float b) &;
/* 4 */ Line&& fillColor(float r, float g, float b) &&;		
```

Sets the fill color of the line.

**Parameter (1 and 2):** [Color](TODO) **col:** The new fill color  
**Parameter (3 and 4):**

- [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **r:** Red color component in a range from [0, 1]
- [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **g:** Green color component in a range from [0, 1]
- [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **b:** Blue color component in a range from [0, 1]

**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.color()
----

```C++
/* 1 */ Line& color(Color col) &;
/* 2 */ Line&& color(Color col) &&;
/* 3 */ Line& color(float r, float g, float b) &;
/* 4 */ Line&& color(float r, float g, float b) &&;		
```

Sets both the line and the fill color. 
Is equivalent to calling: `line.lineColor(color).fillColor(color)`.

**Parameter (1 and 2):** [Color](TODO) **col:** The new line and fill color  
**Parameter (3 and 4):**

- [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **r:** red color component in a range from [0, 1]
- [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **g:** green color component in a range from [0, 1]
- [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **b:** blue color component in a range from [0, 1]

**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.autoLineColor()
----

```C++
Line& autoLineColor() &;
Line&& autoLineColor() &&;
```

Removes the previously set line color and enables automatic coloring of plots.

**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.autoFillColor()
----

```C++
Line& autoFillColor() &;
Line&& autoFillColor() &&;
```

Removes the previously set fill color and enables automatic coloring of plots.

**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.autoColor()
----

```C++
Line& autoColor() &;
Line&& autoColor() &&;
```

Removes both the previously set line and fill color and enables automatic coloring of plots.
Is equivalent to calling `line.autoLineColor().autoFillColor()`.

**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.fill()
----

```C++
Line& fill(float opacity = 0.3) &;
Line&& fill(float opacity = 0.3) &&;
```

Enables the line fill and sets the opacity of the fill.

**Parameter:** [float](https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types) **opacity:** A value in the range of [0, 1] where 0 is fully transparrent and 1 is fully covering.  
**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.fillPattern()
----

```C++
Line& fillPattern(int n) &;
Line&& fillPattern(int n) &&;
```

Select one of Gnuplots fill patterns. May be benefitial for printing figures on paper.

**Parameter:** [int](https://en.cppreference.com/w/cpp/language/types#Integral_types) The index number of the [Gnuplot fill pattern](http://gnuplot.info/docs/loc15652.html)  
**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.noFill()
----

```C++
Line& noFill() &;
Line&& noFill() &&;
```

Disables the line fill.

**Returns:** [Line](Line.md#class-line) Self, for method chaining.

### Line.isFilled()
----

```C++
bool isFilled() const;
```

**Returns:** [bool](https://en.cppreference.com/w/cpp/language/types#Boolean_type)

- `true` if the line fill is enabled
- `false` otherwise

### Line.label()

```C++
/* 1 */ Line& label(const char* label) &;
/* 2 */ Line&& label(const char* label) &&;
/* 3 */ Line& label(std::string_view label) &;
/* 4 */ Line&& label(std::string_view label) &&;
/* 5 */ Line& label(std::string&& label) &;
/* 6 */ Line&& label(std::string&& label) &&;
```

Sets the label string that will be displayed in the legend. 
Overrides the implementation inherrited from [IPlot](TODO).

**Parameter** 

- 1 and 2: const [char](https://en.cppreference.com/w/cpp/language/types#Character_types)\* **label**: The new label as a zero-terminated C-style string  
- 3 and 4: [std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view) **label**: The new label as a reference to a string view  
- 5 and 6: [std::string](https://en.cppreference.com/w/cpp/string/basic_string)&& **label**: The new label as a moved string  

**Returns:** [Line](Line.md#class-line) Self, for method chaining.  

### Line.x()

```C++
Tx* x();
const Tx* x() const;
```

**Returns:** Tx*: A pointer to the range containing the x-Data.

### Line.y()

```C++
Tx* y();
const Tx* y() const;
```

**Returns:** Ty*: A pointer to the range containing the y-Data.

### Line.printPlot()
---- 

```C++
virtual void printPlot(FILE* fptr) const override;
```

The user normally does not need to call this function. 
Overrides the implementation inherrited from [IPlot](TODO).
Writing, opening, and closing files is completelly handelled by [Figure](Figure.md) or [Multifigure](TODO).

Writes the plot command for Gnuplot into the provided file stream.

**Parameter:** [FILE*](https://en.cppreference.com/w/cpp/io/c/FILE) **fptr**: Pointer to a file stream.

### Line.printData()
----

```C++
virtual void printData(FILE* fptr) const override;
```

The user normally does not need to call this function. 
Overrides the implementation inherrited from [IPlot].
Writing, opening, and closing files is completelly handelled by [Figure](Figure.md) or [Multifigure](TODO).

Writes the plot data for Gnuplot into the provided file stream.

**Parameter:** [FILE*](https://en.cppreference.com/w/cpp/io/c/FILE) **fptr**: Pointer to a file stream.

### Methods inherrited from [IPlot](TODO)
----

#### Line.IPlot::label()
----

```C++
const PlotTitle& label() const;
PlotTitle& label();
```

**Returns:** [PlotTitle](TODO): The label of the plot

#### Protected: Line.IPlot::uid()
----

```C++
virtual inline IPlot& uid(size_t& uid_io);
```

Receives a reference to a identification number, assigns itself that number and increments the passed referenced one. 
The UID is used to keep track of data variables in the generated gnuplot scripts. 
The user may overload this for custom plots.

**Parameter:** [size_t](https://en.cppreference.com/w/cpp/language/types#Integral_types) **uid_io**& [in/out]: id number that will be assigned and automatically incremented.  
**Returns:** [IPlot](TODO): For method chaining

```C++
size_t uid() const;
```

**Returns:** [size_t](https://en.cppreference.com/w/cpp/language/types#Integral_types) The UID number of this plot.