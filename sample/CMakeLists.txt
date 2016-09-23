set(PROJECT_NAME2 "testLib")

include(CheckCXXCompilerFlag)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")


include_directories("../lib/include")
message(${PROJECT_NAME2})
link_directories("../bin/lib")
add_executable(${PROJECT_NAME2} main.cpp)
target_link_libraries(${PROJECT_NAME2} -l${CMAKE_PROJECT_NAME} -lluajit-5.1)
