import os
from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout, CMakeDeps, CMakeToolchain
from conan.tools.files import copy

class NovaLLMConan(ConanFile):
    name = "NovaLLM"
    version = "0.1.0" # Match your project version
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps","CMakeToolchain"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "log_spdlog": [True, False], # Corresponds to NOVA_LLM_ENABLE_LOGGING
        "build_tests": [True, False], # Corresponds to NOVA_LLM_BUILD_TESTS
        "integrate_tvm": [True, False], # Option to integrate TVM
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "log_spdlog": True,
        "build_tests": False,
        "integrate_tvm": False, # Default to NOT integrating TVM
    }

    # Requirements - these are the dependencies your project uses
    def requirements(self):
        self.requires("fmt/11.1.3")
        if self.options.log_spdlog:
            self.requires("spdlog/1.15.1")
        if self.options.build_tests:
            self.requires("gtest/1.12.1")
        if self.options.integrate_tvm: #TODO
            # *** IMPORTANT ***
            # Replace 'user/channel' with the actual user and channel 
            # you used when creating the local TVM package.
            self.requires("tvm/0.20.0@user/channel") 

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def generate(self):
        pass

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.libs = ["NovaLLM"]

    # Note: For a project conanfile.py, you typically don't implement build(), package(), etc.
    # Those are for creating packages of YOUR project. This conanfile is just for managing requirements. 