add_executable(a_star)
target_sources(a_star PRIVATE src/a_star.cpp)
target_link_libraries(a_star PRIVATE node sfml-graphics sfml-window sfml-system)

if (UNIX)
    target_compile_options(a_star PRIVATE $<$<CONFIG:Release>:-O2> -Wall -Werror)

elseif (WIN32)
    target_compile_options(a_star PRIVATE $<$<CONFIG:Release>:/O2>)

endif ()
