cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)

# Find all source files
file(GLOB_RECURSE VOLT_FILE_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    RELATIVE_PATH
)

find_package (Threads)

add_library(volt_file ${VOLT_FILE_SRCS})
target_include_directories(volt_file PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(volt_file ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(volt_file ${CONAN_LIBS})