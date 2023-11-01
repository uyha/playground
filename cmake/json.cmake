file(READ listings.json output)

string(REGEX REPLACE [[\\([^"])]] [[\\\\\1]] output "${output}")
message(STATUS "${output}")
string(JSON listings GET "${output}" "listings")
string(JSON tests GET "${listings}" "tests")
string(JSON tests_length LENGTH "${tests}")

# CMake foreach loop is inclusive
math(EXPR test_end "${tests_length} - 1")
foreach(index RANGE "${test_end}")
  string(JSON test GET "${tests}" "${index}")
  string(JSON name GET "${test}" "name")
  string(JSON tags GET "${test}" "tags")
  string(JSON tags_length LENGTH "${tags}")

  if("${tags_length}" GREATER 0) 
    math(EXPR tag_end "${tags_length} - 1")

    message(STATUS "${name}")

    foreach(tag_index RANGE "${tag_end}")
      string(JSON tag GET "${tags}" "${tag_index}")
      message(STATUS "${tag}")
    endforeach()
  endif()
endforeach()
