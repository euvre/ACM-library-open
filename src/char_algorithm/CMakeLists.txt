add_library(acm_char_algorithm OBJECT
    "kmp.ixx")

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:acm_char_algorithm>
    PARENT_SCOPE)