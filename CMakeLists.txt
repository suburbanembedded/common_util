add_library(common_util

	src/Byte_util.cpp
	src/Insertion_sort.cpp
)


target_include_directories(common_util PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

#target_link_libraries(common_util
#	
#)