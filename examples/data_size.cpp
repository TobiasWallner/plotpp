#include <vector>
#include <plotpp.hpp>

class A : private std::vector<double>{
    public:
    using base = std::vector<double>;
    void push_back(double x) {this->base::push_back(x);}
    auto data() {return this->base::data();}
    auto data() const {return this->base::data();}
    size_t size() const {return this->base::size();}
};

int main(){
    A a;
    a.push_back(1.0);
    a.push_back(2.0);
    a.push_back(3.0);
    a.push_back(5.0);
    a.push_back(8.0);
    a.push_back(13.0);
    a.push_back(8.0);
    a.push_back(5.0);
    a.push_back(3.0);

    plotpp::Figure("Data Size Container Plot")
        .add(plotpp::line(a))
        .show();
}