# Create library
set(SOURCES
    serial_interface.cpp
    serial_interface.h
)

set(INCLUDE_DIRS
    .
)

idf_component_register(SRCS ${SOURCES} INCLUDE_DIRS ${INCLUDE_DIRS})
