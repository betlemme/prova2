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
        )

target_link_libraries(esempio ${OpenCV_LIBRARIES} ${PCL_LIBRARIES})








