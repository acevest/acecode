SET(CMAKE_ASM_FLAGS "-c")
ADD_LIBRARY(debug
	debug.c
	asm_debug.S
)

