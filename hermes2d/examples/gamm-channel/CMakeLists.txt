if(NOT H2D_REAL)
    return()
endif(NOT H2D_REAL)

project(gamm-channel)

find_package(PythonLibs REQUIRED)
find_package(NumPy REQUIRED)
include(UseCython)

include_directories(${PYTHON_INCLUDE_PATH} ${NUMPY_INCLUDE_PATH})
include_directories(${hermes2d_SOURCE_DIR}/python/hermes2d)

add_executable(${PROJECT_NAME} main.cpp forms.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
include (../CMake.common)

target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
add_dependencies(${PROJECT_NAME} _hermes2d)
