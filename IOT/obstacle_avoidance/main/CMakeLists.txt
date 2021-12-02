# Create library
set(SOURCES
    app_main.cpp
)

set(INCLUDE_DIRS
    .
)

idf_component_register(SRCS ${SOURCES} INCLUDE_DIRS ${INCLUDE_DIRS} REQUIRES depthai-spi-api)
