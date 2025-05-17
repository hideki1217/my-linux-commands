
FILE(GLOB MyCSources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(head
    ${MyCSources}
)

install(
    TARGETS head RUNTIME DESTINATION bin
)