find_package(OpenCV REQUIRED)

add_executable(shell-app main.cpp camera.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    	${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(shell-app ${OpenCV_LIBS} ${EIGEN3_LIBS})
