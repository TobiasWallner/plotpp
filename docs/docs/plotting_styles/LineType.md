In header: `<plotpp/LineType.hpp>`  
In namespace: `plotpp::`

# Enum LineType

| Name           | Value | Description |
|:---------------|------:|:------------|
| `none`         | -1    | No line     | 
| `solid`        | 1     | Solid line  |
| `dashed`       | 2     | Dashed line |
| `dash_dotted`  | 3     | Dashed and dottet line - option 1|
| `dash_dotted2` | 4     | Dashed and dottet line - option 2|

Supports [{fmt}](https://fmt.dev/latest/) formating into its corresponding Gnuplot command.

## Example:
```C++
fmt::println("Line type: {}", LineType::dashed);
```
Output:
```
Line type: dt 2
```

# Related Functions

## Function to_command()

```C++
std::string_view to_command(LineType dt)
```

Turns the LineType into a Gnuplot command.

**Parameter:** [LineType](LineType.md#enum-linetype) **dt:** The line type
**Returns:** [std::string_viewhttps://en.cppreference.com/w/cpp/string/basic_string_view]() a string view that points to a raw c-string with the corresponding Gnuplot command

