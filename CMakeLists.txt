project(CoolVM)
cmake_minimum_required(VERSION 3.14)

file(GLOB_RECURSE COOLVM_SOURCES
	CONFIGURE_DEPENDS
	"include/*.hpp"
	"include/*.inl"
	"include/*.h"
	"src/*.hpp"
	"src/*.inl"
	"src/*.h"
	"src/*.c"
	"src/*.cpp"
)

add_library(CoolVM STATIC ${COOLVM_SOURCES})
target_include_directories(CoolVM PUBLIC include/)

add_executable(test "test/test.cpp")
target_link_libraries(test CoolVM)
