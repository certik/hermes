# This allows to link Cython files
# Examples:
# 1) to compile assembly.pyx to assembly.so:
#   CYTHON_ADD_MODULE(assembly)
# 2) to compile assembly.pyx and something.cpp to assembly.so:
#   CYTHON_ADD_MODULE(assembly something.cpp)

if(NOT CYTHON_INCLUDE_DIRECTORIES)
    set(CYTHON_INCLUDE_DIRECTORIES .)
endif(NOT CYTHON_INCLUDE_DIRECTORIES)

macro(CYTHON_ADD_MODULE_COMPILE name)
    add_python_library(${name} ${name}.cpp ${ARGN})
endmacro(CYTHON_ADD_MODULE_COMPILE)

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
    CYTHON_ADD_MODULE_COMPILE(${name} ${ARGN})
endmacro(CYTHON_ADD_MODULE)
