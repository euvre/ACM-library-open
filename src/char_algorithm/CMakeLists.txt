file(GLOB
    acm_char_ixx
    CONFIGURE_DEPENDS
    kmp.ixx
    manacher.ixx)

set(acm_char_ixx ${acm_char_ixx} 
    PARENT_SCOPE)