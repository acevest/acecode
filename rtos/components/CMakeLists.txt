ADD_SUBDIRECTORY(utils)
ADD_LIBRARY(components $<TARGET_OBJECTS:utils_object>)
