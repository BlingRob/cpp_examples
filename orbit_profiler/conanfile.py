from conan import ConanFile
from conan.tools.cmake import CMake

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("OrbitProfiler/1.85.0@https://github.com/google/orbit.git")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()