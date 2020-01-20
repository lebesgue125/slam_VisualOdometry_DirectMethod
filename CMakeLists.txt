cmake_minimum_required(VERSION 3.15)
project(VO2)

set(CMAKE_CXX_STANDARD 14)


find_package(OpenCV 3 REQUIRED)
find_package(Sophus REQUIRED)

find_package(Eigen3 3.1.0 REQUIRED)
find_package(Pangolin REQUIRED)

message(status "Pangolin_INCLUDE_DIRS-------" ${Pangolin_INCLUDE_DIRS})
message(status "EIGEN3_INCLUDE_DIR--------" ${EIGEN3_INCLUDE_DIR})
message(status "Sophus_INCLUDE_DIRS-------" ${Sophus_INCLUDE_DIRS})

include_directories(
        ${EIGEN3_INCLUDE_DIR}
        ${Pangolin_INCLUDE_DIRS}
        ${Sophus_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        "/usr/local/boost/include"
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(optflow optical_flow.cpp)
target_link_libraries(optflow ${OpenCV_LIBS})

add_executable(direct direct_method.cpp)
target_link_libraries(direct
        #${EIGEN3_LIBS}
        ${Pangolin_LIBRARIES}
        ${Sophus_LIBRARIES}
        ${OpenCV_LIBS}
        "/usr/local/boost/lib"
        )

add_executable(disparity disparity_calc.cpp)
target_link_libraries(disparity ${OpenCV_LIBS})