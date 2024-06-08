# pylint: disable=missing-class-docstring, too-few-public-methods,
# pylint: disable=missing-function-docstring, missing-module-docstring,

from conan import ConanFile  # pylint: disable=import-error


class ProjectName(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def configure(self):
        assert self.options is not None
        self.options["reflect-cpp/*"].with_json = True
        self.options["msgpack-cxx/*"].use_boost = False

    def requirements(self):
        dependencies = [
            "fmt/10.2.1",
            "reflect-cpp/0.10.0",
            "msgpack-cxx/6.1.1",
        ]

        for dep in dependencies:
            self.requires(dep)
