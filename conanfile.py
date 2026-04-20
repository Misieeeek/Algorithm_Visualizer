from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import valid_min_cppstd
from conan.tools.cmake import cmake_layout
from conan.tools.scm import Version


class FormatterRecipe(ConanFile):
    name = "formatter"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    _min_compiler_version = {
        "gcc": "14",
        "clang": "16",
        "apple-clang": "15",
        "msvc": "194",
    }

    def requirements(self):
        self.requires("sfml/3.0.2")

    def build_requirements(self):
        self.tool_requires("cmake/[>=4.3]")
        self.tool_requires("doxygen/[>=1.16]")

    def validate(self):
        if not valid_min_cppstd(self, 23):
            raise ConanInvalidConfiguration("formatter requires at least C++23")

        compiler = str(self.settings.compiler)
        min_version = self._min_compiler_version.get(compiler)

        if min_version is None:
            self.output.warning(
                f"compiler '{compiler}' is not tested; use at your own risk"
            )
        elif Version(self.settings.compiler.version) < min_version:
            raise ConanInvalidConfiguration(
                f"formatter requires {compiler} >= {min_version} for C++23 "
                f"(got {self.settings.compiler.version})"
            )

    def layout(self):
        cmake_layout(self)
