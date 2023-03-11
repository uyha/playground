set(path "/a/b.asdf.asdf")
cmake_path(GET path FILENAME filename)
message("${filename}")
