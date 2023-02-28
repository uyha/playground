from conan import ConanFile


class SandboxRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("fmt/9.1.0")
        self.requires("msgpack-cxx/5.0.0", options={"use_boost": False})
        self.requires("lely-core/2.3.2")
