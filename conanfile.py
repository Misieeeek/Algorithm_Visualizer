from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import valid_min_cppstd
from conan.tools.cmake import cmake_layout
from conan.tools.scm import Version


class FormatterRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("sfml/3.0.2")

    def build_requirements(self):
        self.tool_requires("cmake/4.3.0")
        self.tool_requires("ninja/1.13.2")
        self.tool_requires("doxygen/1.16.1")

    def validate(self):
        if not valid_min_cppstd(self, 23):
            raise ConanInvalidConfiguration("Task requires atleast C++23")

        compiler = self.settings.compiler
        version = Version(self.settings.compiler.version)

        if compiler == "gcc" and version < "14":
            raise ConanInvalidConfiguration("This project requires GCC >= 14")
        if compiler == "clang" and version < "16":
            raise ConanInvalidConfiguration("This project requires Clang >= 16")
        if compiler == "msvc" and version < "194":
            raise ConanInvalidConfiguration(
                "This project requires MSVC >= 19.4 (VS 2022)"
            )

    def layout(self):
        cmake_layout(self)
