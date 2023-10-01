# pylint: disable=missing-class-docstring, too-few-public-methods,
# pylint: disable=missing-function-docstring, missing-module-docstring,

from conan import ConanFile  # pylint: disable=import-error


class ProjectName(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def configure(self):
        assert self.options is not None
        self.options["sol2/*"].with_lua = "luajit"

    def requirements(self):
        dependencies = [
            "fmt/10.1.1",
            "luajit/2.1.0-beta3",
            "sol2/3.3.1",
        ]

        assert self.requires is not None
        for dep in dependencies:
            self.requires(dep)
