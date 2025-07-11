from conan import ConanFile


class SandboxRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def configure(self):
        assert self.options is not None
        self.options["zeromq/*"].with_draft_api = True

    def requirements(self):
        assert self.requires is not None
        self.requires("cppzmq/4.10.0")
        self.requires("flatbuffers/23.5.26")
        self.requires("fmt/11.2.0")
        self.requires("inja/3.4.0")
        self.requires("lely-core/2.3.4")
        self.requires("msgpack-cxx/6.0.0", options={"use_boost": False})
        self.requires("nlohmann_json/3.11.3")
        self.requires("pfr/2.2.0")
        self.requires("re2/20231101")
        self.requires("sqlite3/3.49.1")
