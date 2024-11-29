from conan import ConanFile
from conan.tools.cmake import CMake

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("asio/1.30.2")
        self.requires("boost/1.85.0")    

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()