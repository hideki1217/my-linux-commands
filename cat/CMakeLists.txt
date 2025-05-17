
FILE(GLOB MyCSources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(cat
    ${MyCSources}
)

install(
    TARGETS cat RUNTIME DESTINATION bin
)