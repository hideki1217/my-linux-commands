
FILE(GLOB MyCSources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(time
    ${MyCSources}
)

install(
    TARGETS time RUNTIME DESTINATION bin
)