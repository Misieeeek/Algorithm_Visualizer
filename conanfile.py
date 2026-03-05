from conan import ConanFile
from conan.tools.cmake import cmake_layout

class FormatterRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("sfml/2.6.1")

    def build_requirements(self):
        self.tool_requires("cmake/4.2.3")

    def layout(self):
        cmake_layout(self)

    def configure(self):
        self.settings.compiler.cppstd = "20"
