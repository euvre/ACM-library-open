add_subdirectory(type)

file(GLOB
    acm_common_ixx
    CONFIGURE_DEPENDS
    acm_except.ixx
    ${acm_common_type_ixx})

set(acm_common_ixx ${acm_common_ixx} 
    PARENT_SCOPE)