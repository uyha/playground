cmake_minimum_required(VERSION 3.18)
project(custom_target LANGUAGES NONE)

add_subdirectory(subdir)

set(asd asd PARENT_SCOPE)

add_custom_target(asdf PRIVATE asdasd)

set(asdasd "asd\;" CACHE INTERNAL FORCE)

block(SCOPE_FOR POLICIES VARIABLES PROPAGATE asd)
aksdjfaksdjfkjasdf()
endblock()

function(fn)
  for()
    continue()
  endfor()
  return()
endfunction()

include(RESULT_VARIABLE asdf OPTIONAL NO_POLICY_SCOPE)
unset(asdf PARENT_SCOPE CACHE)

list(LENGTH list out)
list(GET list out)
list(FIND list out)
list(APPEND list out)
list(FILTER list out)
list(INSERT list out)
list(POP_BACK list out)
list(POP_FRONT list out)
list(PREPEND list out)
list(REMOVE_ITEM list out)
list(REMOVE_AT list out)
list(REMOVE_DUPLICATES list out)
list(TRANSFORM list STRIP OUTPUT_VARIABLE asd asdfasdf asdf asdf as dfasdf )
list(REVERSE list)
list(SORT list asdf)
add_asd($CACHE{asdasd})
add_asd($ENV{asdasd})
