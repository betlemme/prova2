cmake_minimum_required(VERSION 2.8)

project(ProvaGit)

find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

message(STATUS "OpenCV include dirs found: ${OpenCV_INCLUDE_DIRS}")

include_directories(
	include
	${PCL_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


	

add_executable(esempio
        src/esempio.cpp
        src/face.cpp
        )

target_link_libraries(esempio ${OpenCV_LIBRARIES} ${PCL_LIBRARIES})

#add_executable(face
#        src/face.cpp
#        )
#
#target_link_libraries(face ${OpenCV_LIBRARIES} ${PCL_LIBRARIES})

add_executable(recognition
        src/recognition.cpp
        src/detection.cpp
        )

target_link_libraries(recognition ${OpenCV_LIBRARIES} ${PCL_LIBRARIES})


#add_executable(detection
#        src/detection.cpp
#        )
#
#target_link_libraries(detection ${OpenCV_LIBRARIES} ${PCL_LIBRARIES})


add_executable(training
        src/training.cpp
        src/detection.cpp
        )

target_link_libraries(training ${OpenCV_LIBRARIES} ${PCL_LIBRARIES})


add_executable(ex5
        src/ex5.cpp
        )

target_link_libraries(ex5 ${OpenCV_LIBRARIES} ${PCL_LIBRARIES})

add_executable(3dfeature
        src/3dfeature.cpp
        )

target_link_libraries(3dfeature ${OpenCV_LIBRARIES} ${PCL_LIBRARIES})















