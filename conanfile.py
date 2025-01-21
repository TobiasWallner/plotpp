from conan import ConanFile

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CmakeDeps"
    
    def requirements(self):
        self.requires("fmt/11.1.1")
        
    
    