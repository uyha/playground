set(output [[All available test cases:
  ConfUpdate serde
      [comm][conf][serde]
  Configurator neoconf/current-conf
      [conf][endpoint]
  Configurator neoconf/update-conf
      [conf][endpoint]
  Configurator neoconf/notify-ping
      [conf][endpoint]
  Configurator neoconf/notify
      [conf][endpoint]
5 test cases

]])
string(STRIP "${output}" output)
string(REPLACE "\n" ";" output "${output}")
list(LENGTH output length)
math(EXPR length "${length} - 2")
list(SUBLIST output 1 "${length}" output)

foreach(line IN LISTS output)
  set(test "${line}")
  if(line MATCHES "^  ([^ ].*)$")
    message(STATUS "${CMAKE_MATCH_1}")
  elseif(line MATCHES "^      (.*)$")
    set(tag "${CMAKE_MATCH_1}")
    message(STATUS "${tag}")
    string(REGEX REPLACE "^\\[" "" tag "${tag}")
    string(REGEX REPLACE "\\]$" "" tag "${tag}")
    string(REPLACE "][" ";" tag "${tag}")
    message(STATUS "${tag}")
  endif()
endforeach()

message(STATUS ${test})
