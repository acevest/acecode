CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_VERBOSE_MAKEFILE on)
SET(RTOS_VERSION_MAJOR 0)
SET(RTOS_VERSION_MINOR 1)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR xtensa)
#SET(CMAKE_FIND_ROOT_PATH /Users/ace/workspace/esp/xtensa-esp32-elf/)
#SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#SET(CMAKE_C_COMPILER xtensa-esp32-elf-gcc)
#SET(CMAKE_ASM_COMPILER xtensa-esp32-elf-gcc)
#SET(CMAKE_LINKER xtensa-esp32-elf-ld)
#SET(CMAKE_CROSSCOMPILING  "TRUE")

SET(CMAKE_C_FLAGS "-nostdlib -nodefaultlibs")
link_directories(/Users/ace/workspace/esp/xtensa-esp32-elf/lib/)
SET(CMAKE_C_COMPILER /Users/ace/workspace/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc)
SET(CMAKE_C_COMPILER_ID xtensa-esp32-elf-gcc)
SET(CMAKE_LINKER /Users/ace/workspace/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-ld)
SET(CMAKE_LINKER_ID xtensa-esp32-elf-ld)

#INCLUDE(CheckCSourceCompiles)
#INCLUDE(CheckCCompilerFlag)
#CHECK_C_COMPILER_FLAG("" toolchain_is_ok)


PROJECT(rtos NONE)
ENABLE_LANGUAGE(C)
ENABLE_LANGUAGE(ASM)


CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/rtos_config.h.in"
	"${PROJECT_BINARY_DIR}/rtos_config.h"
)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}"
	"components/utils"
	"kernel/include")

ADD_SUBDIRECTORY(components)
#ADD_SUBDIRECTORY(kernel)

LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

ADD_EXECUTABLE(rtos rtos.c)
SET_TARGET_PROPERTIES(rtos PROPERTIES LINKER_LANGUAGE C)


# TARGET_LINK_LIBRARIES 参数里 debug optimized general 是关键词，不能用
# TARGET_LINK_LIBRARIES(rtos components kernel)
TARGET_LINK_LIBRARIES(rtos components)
