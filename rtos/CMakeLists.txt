CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

SET(RTOS_VERSION_MAJOR	0)
SET(RTOS_VERSION_MINOR 1)


PROJECT(rtos)

CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/rtos_config.h.in"
	"${PROJECT_BINARY_DIR}/rtos_config.h"
)

add_subdirectory(components)

include_directories("${PROJECT_BINARY_DIR}"
					"components/debug")

add_executable(rtos rtos.c)

target_link_libraries(rtos components)
