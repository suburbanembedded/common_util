cmake_minimum_required(VERSION 3.10)

#add_subdirectory(googletest-master)

add_library(common_util

	src/Byte_util.cpp
	src/Comparison_util.cpp
	src/Insertion_sort.cpp
	src/Register_util.cpp

	src/Intrusive_list.cpp
	src/Intrusive_slist.cpp
	src/Non_copyable.cpp

	src/Stack_string_base.cpp
	src/Stack_string.cpp
)

target_include_directories(common_util PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

#add_library(common_util_tests
#	tests/Byte_util_tests.cpp
#	tests/Insertion_sort_tests.cpp
#	tests/Test_Intrusive_list.cpp
#	tests/Test_Intrusive_slist.cpp
#	tests/Test_Stack_string.cpp
#)
#
#target_link_libraries(common_util_tests 
#	common_util
#	gtest
#	gmock
#)
#
#add_executable(common_util_test_runner_linux
#	""
#)
#
#target_link_libraries(common_util_test_runner_linux 
#	gtest_main
#	-Wl,--whole-archive common_util_tests -Wl,--no-whole-archive
#)
