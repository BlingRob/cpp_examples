#include <pybind11/pybind11.h>

int add(int a, int b) 
{
    return a + b;
}

class MyTestClass 
{
public:
    MyTestClass(const std::string &name) : name_(name) { }

    const std::string &GetName() const { return name_; }
    void SetName(const std::string &name) { name_ = name; }

private:
    std::string name_;
};

namespace py = pybind11;

PYBIND11_MODULE(pybind_test, m) 
{
    py::class_<MyTestClass>(m, "MyTestClass")
        .def(py::init<const std::string &>())
        .def("name", &MyTestClass::GetName)
        .def("setName", &MyTestClass::SetName);

    m.def("add", &add, "A function that adds two numbers");

    m.attr("global_lib_var") = 100;
}
