set(COUNTER 0 CACHE INTERNAL "")

macro(increment)
  math(EXPR COUNTER "${COUNTER} + 1")
endmacro()

increment()
increment()
increment()
increment()
increment()
increment()

message(STATUS "${COUNTER}")
