
FILE(GLOB MyCSources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(ls
    ${MyCSources}
)

install(
    TARGETS ls RUNTIME DESTINATION bin
)