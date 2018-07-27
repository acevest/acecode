SET(utils_sources
	debug.c
	debug.S
)
ADD_LIBRARY(utils_object OBJECT ${utils_sources})
ADD_LIBRARY(utils        STATIC ${utils_sources})
