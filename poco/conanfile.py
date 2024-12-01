from conan import ConanFile
from conan.tools.cmake import CMake

class PocoExample(ConanFile):
    name = "poco_example_programms"
    description = "test_programm"
    topics = ("networking", "multithreadings")
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("poco/1.13.3")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()