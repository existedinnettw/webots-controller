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

    exports_sources = "CMakeLists.txt", "src/*", "include/*", "patches/*.patch", "LICENSE", "README.md"

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
        if self.settings.os == "Windows" and self.settings.compiler != "gcc":
            self.requires("dirent/1.24")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)
        # tc.variables["BUILD_SHARED_LIBS"] = bool(self.options.shared)
        tc.variables["WEBOTS_CONTROLLER_NO_PLUGINS"] = bool(self.options.no_plugins)
        libcontroller_version = str(self.version)
        if libcontroller_version.startswith("r"):
            libcontroller_version = f"R{libcontroller_version[1:]}"
        tc.variables["LIBCONTROLLER_VERSION"] = libcontroller_version
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
        self.cpp_info.set_property("cmake_file_name", "webots-controller")
        self.cpp_info.set_property("cmake_target_name", "webots-controller::webots-controller")
        self.cpp_info.requires = ["CppController"]

        controller = self.cpp_info.components["Controller"]
        controller.libs = ["webots_controller"]
        controller.includedirs = ["include", "include/controller/c"]
        controller.set_property("cmake_target_name", "webots-controller::Controller")

        cpp_controller = self.cpp_info.components["CppController"]
        cpp_controller.libs = ["webots_cpp_controller"]
        cpp_controller.includedirs = ["include", "include/controller/cpp", "include/controller/c"]
        cpp_controller.requires = ["Controller"]
        cpp_controller.set_property("cmake_target_name", "webots-controller::CppController")
