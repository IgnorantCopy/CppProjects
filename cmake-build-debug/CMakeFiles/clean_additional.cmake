# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CppProjects_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CppProjects_autogen.dir\\ParseCache.txt"
  "CppProjects_autogen"
  )
endif()
