# pylint: disable=missing-class-docstring, too-few-public-methods,
# pylint: disable=missing-function-docstring, missing-module-docstring,

from conan import ConanFile  # pylint: disable=import-error


class ProjectName(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def configure(self):
        assert self.options is not None
        self.options["zeromq/*"].with_draft_api = True

    def requirements(self):
        dependencies = [
            "fmt/10.1.1",
            "cppzmq/4.10.0",
        ]

        for dep in dependencies:
            self.requires(dep)
