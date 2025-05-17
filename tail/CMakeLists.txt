
FILE(GLOB MyCSources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(tail
    ${MyCSources}
)

install(
    TARGETS tail RUNTIME DESTINATION bin
)