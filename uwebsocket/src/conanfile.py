# pylint: disable=missing-class-docstring, too-few-public-methods,
# pylint: disable=missing-function-docstring, missing-module-docstring,

from conan import ConanFile  # pylint: disable=import-error


class ProjectName(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        dependencies = [
            "fmt/10.2.1",
            "uwebsockets/20.64.0",
        ]

        for dep in dependencies:
            self.requires(dep)
