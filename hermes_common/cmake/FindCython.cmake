#
# Cython
#

FIND_FILE(CYTHON_BIN cython /usr/bin /usr/local/bin) 

IF (CYTHON_BIN)
	SET(Cython_FOUND TRUE)
ENDIF (CYTHON_BIN)


IF (Cython_FOUND)
	IF (NOT Cython_FIND_QUIETLY)
		MESSAGE(STATUS "Found cython: ${CYTHON_BIN}")
	ENDIF (NOT Cython_FIND_QUIETLY)
ELSE (Cython_FOUND)
	IF (Cython_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find cython")
	ENDIF (Cython_FIND_REQUIRED)
ENDIF (Cython_FOUND)

# This allows to link Cython files
# Examples:
# 1) to compile assembly.pyx to assembly.so:
#   CYTHON_ADD_MODULE(assembly)
# 2) to compile assembly.pyx and something.cpp to assembly.so:
#   CYTHON_ADD_MODULE(assembly something.cpp)

if(NOT CYTHON_INCLUDE_DIRECTORIES)
    set(CYTHON_INCLUDE_DIRECTORIES .)
endif(NOT CYTHON_INCLUDE_DIRECTORIES)

# Cythonizes the .pyx files into .cpp file (but doesn't compile it)
macro(CYTHON_ADD_MODULE_PYX name)
    add_custom_command(
        OUTPUT ${name}.cpp
        COMMAND cython
        ARGS --cplus -I ${CYTHON_INCLUDE_DIRECTORIES} -o ${name}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${name}.pyx
        DEPENDS ${name}.pyx ${name}.pxd
        COMMENT "Cythonizing ${name}.pyx")
endmacro(CYTHON_ADD_MODULE_PYX)

# Cythonizes and compiles a .pyx file
macro(CYTHON_ADD_MODULE name)
    CYTHON_ADD_MODULE_PYX(${name} ${ARGN})
    add_python_library(${name} ${name}.cpp ${ARGN})
endmacro(CYTHON_ADD_MODULE)
