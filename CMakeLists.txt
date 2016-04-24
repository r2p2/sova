cmake_minimum_required(VERSION 3.0)

project("sova" CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Og")


add_executable(sova
	src/main.cc
	src/capture/ctrl.cc
	src/capture/util/time.cc
	src/capture/x/xadapter.cc
	src/capture/storage/stdout.cc
)

target_link_libraries(sova
	X11
	boost_system
)
