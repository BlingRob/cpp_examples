from conan import ConanFile
from conan.tools.cmake import CMake

class PocoExample(ConanFile):
    name = "zip_utility"
    description = "zip test programm"
    topics = ("archiving", "compression")
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("miniz/3.0.2")
        self.requires("argparse/3.1")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()