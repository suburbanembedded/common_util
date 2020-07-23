project(common_util)

cmake_minimum_required(VERSION 3.10)

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

file(GLOB common_util_PUBLIC_HEADER	include/common_util/*.hpp)

target_include_directories(common_util PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(common_util
	PROPERTIES
		PUBLIC_HEADER
			"${common_util_PUBLIC_HEADER}"
)

if(${BUILD_TESTS})

	add_library(gtest STATIC
		/usr/src/googletest/googletest/src/gtest-all.cc
	)

	target_include_directories(gtest PUBLIC
		/usr/src/googletest/googletest/include
		/usr/src/googletest/googletest/
	)

	add_library(gmock STATIC
		/usr/src/googletest/googlemock/src/gmock-all.cc
	)

	target_include_directories(gmock PUBLIC
		/usr/src/googletest/googlemock/include
		/usr/src/googletest/googlemock/
	)

	set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
	set(THREADS_PREFER_PTHREAD_FLAG TRUE)
	find_package(
		Threads REQUIRED
	)

	add_library(common_util_tests STATIC
		tests/Byte_util_tests.cpp
		tests/Insertion_sort_tests.cpp
		tests/Test_Intrusive_list.cpp
		tests/Test_Intrusive_slist.cpp
		tests/Test_Stack_string.cpp
	)

	target_link_libraries(common_util_tests 
		common_util
		gtest
		gmock

		Threads::Threads
	)

	add_executable(common_util_test_runner_linux
		/usr/src/googletest/googletest/src/gtest_main.cc
	)

	target_link_libraries(common_util_test_runner_linux 
		
		-Wl,--whole-archive common_util_tests -Wl,--no-whole-archive
	)

INSTALL(
	TARGETS
		common_util_test_runner_linux
	RUNTIME DESTINATION
		bin
	ARCHIVE DESTINATION
		lib
	LIBRARY DESTINATION
		lib
)

endif()

if(DEFINED Doxygen::doxygen)
	doxygen_add_docs(common_util_docs
		include/
		src/
	)
endif()

INSTALL(
	TARGETS
		common_util
	ARCHIVE DESTINATION
		lib
	LIBRARY DESTINATION
		lib
	PUBLIC_HEADER DESTINATION 
		include/common_util
)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_VENDOR  "Jacob Schloss")
SET(CPACK_PACKAGE_CONTACT "jacob@schloss.io")
SET(CPACK_DEBIAN_PACKAGE_SECTION "non-free/misc")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libstdc++6, libgcc1")
INCLUDE(CPack)
