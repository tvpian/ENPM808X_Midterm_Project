find_package( OpenCV REQUIRED)

set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    detector_test.cpp
    tracker_test.cpp
    camera_test.cpp
    humanTracker_test.cpp
    ../app/detector.cpp
    ../app/tracker.cpp
    ../app/camera.cpp
    ../app/humanTracker.cpp
    ../app/obstacle.cpp
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include
                                           ${OpenCV_INCLUDE_DIRS})  
                                         
                                         
                                         
target_link_libraries(cpp-test PUBLIC gtest ${OpenCV_LIBS} )
