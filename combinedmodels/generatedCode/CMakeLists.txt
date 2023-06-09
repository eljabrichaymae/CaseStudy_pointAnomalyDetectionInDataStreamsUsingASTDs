cmake_minimum_required(VERSION 3.18)
project(COMBINEMODELS)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Python3  COMPONENTS Interpreter Development Development.Module NumPy)
add_executable(COMBINEMODELS    combinemodels.cpp
                                    Code.cpp 
                                    ${PROJECT_SOURCE_DIR}/learning_models/KDE/kde.cpp 
                                    ${PROJECT_SOURCE_DIR}/window/window.cpp
                                    ${PROJECT_SOURCE_DIR}/learning_models/KMEANS/kmeans.cpp
                                    ${PROJECT_SOURCE_DIR}/learning_models/LOF/lof.cpp )
include_directories(${PYTHON_INCLUDE_DIRS} ${Python_NumPy_INCLUDE_DIRS})
target_link_libraries(COMBINEMODELS PRIVATE Python3::Python PRIVATE Python3::NumPy)
target_include_directories(COMBINEMODELS PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${Python_NumPy_INCLUDE_DIRS}"
                           "${PROJECT_SOURCE_DIR}/learning_models"
                           "${PROJECT_SOURCE_DIR}/window"
                           "${PROJECT_SOURCE_DIR}/learning_models/KDE"
                           "${PROJECT_SOURCE_DIR}/learning_models/LOF"
                           "${PROJECT_SOURCE_DIR}/learning_models/KMEANS")