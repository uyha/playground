from conan import ConanFile
from conans.model.requires import Requirements


class SandboxRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        assert self.requires is not None
        self.requires("fmt/10.1.0")
        self.requires("msgpack-cxx/6.0.0", options={"use_boost": False})
        self.requires("lely-core/2.3.2")
        self.requires("mp-units/2.0.0")
