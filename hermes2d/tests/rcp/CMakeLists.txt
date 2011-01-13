project(rcp)

add_executable(${PROJECT_NAME} main.cpp)
include (../CMake.common)

set(BIN ${PROJECT_BINARY_DIR}/${PROJECT_NAME})
add_test(rcp ${BIN})

project(allocation)

add_executable(${PROJECT_NAME} allocation.cpp)
include (../CMake.common)

set(BIN ${PROJECT_BINARY_DIR}/${PROJECT_NAME})
add_test(allocation ${BIN})
