#include <Windows.h>
#include <cmath>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>


const double e = 2.7182818284590452353602874713527;

double sinh_impl(double x) {
    return (1 - pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double cosh_impl(double x) {
    return (1 + pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double tanh_impl(double x) {
    return sinh_impl(x) / cosh_impl(x);
}

struct Pet {
    Pet(const std::string& name) : name(name) { }
    void setName(const std::string& name_) { name = name_; }
    const std::string& getName() const { return name; }

    std::string name;
};

class YieldCurve {

public:

    YieldCurve(double x) : t(x) {
        for (int i = 0; i < 100; i++) {
            vectorD.push_back(i);
        }
    }
    const std::string& getName() const { return name; }
    const double getT() const { return t; }
    std::vector<double> getVector() const { return vectorD; }

private:
    std::vector<double> vectorD;
    double t;
    std::string name;
};

namespace py = pybind11;

PYBIND11_MODULE(superfastcode2, m) {
    m.def("fast_tanh2", &tanh_impl, R"pbdoc(
        Compute a hyperbolic tangent of a single argument expressed in radians.
    )pbdoc");


    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string&>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName);

    py::class_<YieldCurve>(m, "YieldCurve")
        .def(py::init<double>())
        .def("getT", &YieldCurve::getT)
        .def("getName", &YieldCurve::getName)
        .def("getVector", &YieldCurve::getVector);


#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}

