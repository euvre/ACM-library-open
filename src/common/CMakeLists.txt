add_subdirectory(type)

add_library(acm_common OBJECT
    "acm_except.ixx")

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:acm_common>
    PARENT_SCOPE)