cmake_minimum_required(VERSION 3.17)
project(homework6)

set(CMAKE_CXX_STANDARD 17)

find_package(GLUT REQUIRED)
include_directories(SYSTEM ${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARIES})
add_definitions(${GLUT_DEFINITIONS})

find_package(OpenGL REQUIRED)
include_directories(SYSTEM ${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

set(EXTRA_LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


add_executable(homework6 main.cpp)

target_link_libraries(homework6 ${EXTRA_LIBS})
