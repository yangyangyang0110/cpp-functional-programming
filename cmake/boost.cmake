find_package(Boost 1.79 REQUIRED COMPONENTS system thread)
message(STATUS "Boost Include Dir: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost Library Dir: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost Library Dir: ${Boost_LIBRARIES}")

include_directories(Boost_INCLUDE_DIRS)
link_directories(Boost_LIBRARY_DIRS)
