
FILE(GLOB MyCSources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(echo
    ${MyCSources}
)

install(
    TARGETS echo RUNTIME DESTINATION bin
)