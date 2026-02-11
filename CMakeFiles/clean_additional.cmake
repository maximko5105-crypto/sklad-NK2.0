# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\sklad2_HK_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\sklad2_HK_autogen.dir\\ParseCache.txt"
  "sklad2_HK_autogen"
  )
endif()
