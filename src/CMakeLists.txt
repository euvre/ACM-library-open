add_subdirectory(char_algorithm)
add_subdirectory(geo_algorithm)
add_subdirectory(dp_algorithm)
add_subdirectory(ds_algorithm)
add_subdirectory(graph_algorithm)
add_subdirectory(math_algorithm)
add_subdirectory(programming_tech)
add_subdirectory(common)
add_subdirectory(ts)

add_library(acm STATIC ${ALL_OBJECT_FILES})

set(ACM_LIBS acm_char_algorithm
	acm_common)

target_link_libraries(acm
	${ACM_LIBS})