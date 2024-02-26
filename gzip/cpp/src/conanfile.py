# pylint: disable=missing-class-docstring, too-few-public-methods,
# pylint: disable=missing-function-docstring, missing-module-docstring,

from conan import ConanFile  # pylint: disable=import-error


class ProjectName(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def configure(self):
        assert self.options is not None
        self.options["msgpack-cxx/*"].use_boost = False

    def requirements(self):
        dependencies = [
            "cppzmq/4.10.0",
            "fmt/10.1.1",
            "msgpack-cxx/6.1.0",
            "zlib/1.3.1",
        ]

        for dep in dependencies:
            self.requires(dep)
