add_library(common_util

	src/Byte_util.cpp
	src/Insertion_sort.cpp
	src/Register_util.cpp
)

target_include_directories(common_util PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(${BUILD_COMMON_UTIL_TESTS})
	add_library(common_util_tests
		tests/Byte_util_tests.cpp
		tests/Insertion_sort_tests.cpp
	)
	
	target_link_libraries(common_util_tests
		common_util
		googletest
		googlemock
	)
endif(${BUILD_COMMON_UTIL_TESTS})
