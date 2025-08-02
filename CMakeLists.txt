cmake_minimum_required(VERSION 3.22)

project(header_hunter CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES   "src/main.cpp"
                    "src/config.cpp"
                    "src/graph.cpp"
                    "src/graphiz_report.cpp"
                    "src/text_report.cpp"
    )


add_executable(header_hunter ${SOURCES})
message ("${CMAKE_BINARY_DIR}/bin")
set_target_properties(header_hunter PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                "${CMAKE_BINARY_DIR}/bin")
set_target_properties(header_hunter PROPERTIES RUNTIME_DEBUG_OUTPUT_DIRECTORY
                                                "${CMAKE_BINARY_DIR}/bin")
set_target_properties(header_hunter PROPERTIES RUNTIME_RELEASE_OUTPUT_DIRECTORY
                                                "${CMAKE_BINARY_DIR}/bin")
