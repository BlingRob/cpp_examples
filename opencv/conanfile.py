from conan import ConanFile
from conan.tools.cmake import CMake

class OpenCV(ConanFile):
    name = "opencv_test_package"
    description = "test_programm"
    topics = ("computer-vision", "deep-learning", "image-processing")
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("opencv/4.10.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()