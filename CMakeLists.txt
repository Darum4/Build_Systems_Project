cmake_minimum_required(VERSION 4.0)

project("Zetto Archiver" VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_FAST -D_FILE_OFFSET_BITS=64)

find_package(ZLIB REQUIRED)

if(NOT ZLIB_FOUND)
    message(FATAL_ERROR "zlib not found! Please install its lib and development files.")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

add_executable(compress src/compress.cpp)

target_link_libraries(compress PRIVATE ZLIB::ZLIB)

target_include_directories(compress PRIVATE ${ZLIB_INCLUDE_DIRS})

add_executable(uncompress src/uncompress.cpp)

target_link_libraries(uncompress PRIVATE ZLIB::ZLIB)

target_include_directories(uncompress PRIVATE ${ZLIB_INCLUDE_DIRS})

install(TARGETS compress uncompress RUNTIME DESTINATION bin)


