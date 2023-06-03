cmake_minimum_required(VERSION 3.18)
project(DETECTIONONEMODEL)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Python3  COMPONENTS Interpreter Development Development.Module NumPy)
add_executable(DETECTIONONEMODEL    detectiononemodel.cpp
                                    Code.cpp 
                                    ${PROJECT_SOURCE_DIR}/KDE/kde.cpp 
                                    ${PROJECT_SOURCE_DIR}/window/window.cpp)
include_directories(${PYTHON_INCLUDE_DIRS} ${Python_NumPy_INCLUDE_DIRS})
target_link_libraries(DETECTIONONEMODEL PRIVATE Python3::Python PRIVATE Python3::NumPy)
target_include_directories(DETECTIONONEMODEL PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/nlohmann"
                           "${Python_NumPy_INCLUDE_DIRS}"
                           "${PROJECT_SOURCE_DIR}/KDE"
                           "${PROJECT_SOURCE_DIR}/window")