from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class plotppRecipe(ConanFile):
    name = "plotpp"
    version = "0.1"
    package_type = "library"

    # Optional metadata
    license = "MIT"
    author = "Tobias Wallner tobias.wallner1@gmx.net"
    url = "https://github.com/TobiasWallner/plotpp"
    description = "A plotting library for C++ that uses Gnuplot as its backend"
    topics = ("Plotting", "Figures")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "plotpp.hpp", "plotpp/*"

    def requirements(self):
        self.requires("fmt/11.1.1", transitive_headers=True)

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)
    
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        

    def package_info(self):
        self.cpp_info.libs = ["plotpp"]
        self.cpp_info.requires = ["fmt::fmt"]  # This makes fmt a public dependency
        