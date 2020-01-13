cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)

# Find all source files
file(GLOB_RECURSE VOLT_FILE_TEST_LOAD_FORMAT_SRCS
    "src/*.cpp"
    RELATIVE_PATH
)

# Copy resource files to build output
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR}/bin/.)

add_executable(ts_volt_file_load_formats ${VOLT_FILE_TEST_LOAD_FORMAT_SRCS})
target_include_directories(ts_volt_file_load_formats PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(ts_volt_file_load_formats volt_file)

# Add as test
add_test(NAME load_formats_test COMMAND ts_volt_file_load_formats WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/.)