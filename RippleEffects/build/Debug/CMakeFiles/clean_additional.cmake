# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\RippleEffects_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\RippleEffects_autogen.dir\\ParseCache.txt"
  "RippleEffects_autogen"
  )
endif()
