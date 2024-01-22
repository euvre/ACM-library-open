add_subdirectory(char_algorithm)
add_subdirectory(geo_algorithm)
add_subdirectory(dp_algorithm)
add_subdirectory(ds_algorithm)
add_subdirectory(graph_algorithm)
add_subdirectory(math_algorithm)
add_subdirectory(programming_tech)
add_subdirectory(common)
add_subdirectory(ts)

add_library(acm_ixx)

target_sources(acm_ixx
    PUBLIC
    FILE_SET core_cxx_modules TYPE CXX_MODULES FILES
    ${acm_char_ixx}
    ${acm_common_ixx} "char_algorithm/manacher.ixx")