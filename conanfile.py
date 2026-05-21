from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy
from conan.tools.microsoft import is_msvc

class WebotsControllerConan(ConanFile):
    name = "webots-controller"
    version = "r2025a"
    package_type = "library"

    settings = "os", "arch", "compiler", "build_type"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "no_plugins": [True, False],
    }
    default_options = {
        "shared": True,
        "fPIC": True,
        "no_plugins": True,
    }

    exports_sources = "CMakeLists.txt", "src/*", "include/*", "LICENSE", "README.md"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        # plugins use dlopen therefore ABI need to be match (same compiler type and compiler version)
        if self.options.get_safe("no_plugins", True):
            return

        if self.settings.os == "Windows" and is_msvc(self):
            raise ValueError("Official windows webots is build under msys2 mingw(gcc), rather than MSVC.")

    def requirements(self):
        # self.requires("stb/cci.20240531")
        pass

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)
        # tc.variables["BUILD_SHARED_LIBS"] = bool(self.options.shared)
        tc.variables["WEBOTS_CONTROLLER_NO_PLUGINS"] = bool(self.options.no_plugins)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_folder, dst=f"{self.package_folder}/licenses")

    def package_info(self):
        self.cpp_info.libs = ["webots_cpp_controller", "webots_controller"]
        self.cpp_info.includedirs = ["include", "include/controller/cpp", "include/controller/c"]
