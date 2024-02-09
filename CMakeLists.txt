cmake_minimum_required(VERSION 3.23.0)

option(WITH_BENCHMARK "Build benchmarks" OFF)
if(WITH_BENCHMARK)
  list(APPEND VCPKG_MANIFEST_FEATURES "benchmark")
endif()

if(BUILD_TESTING)
  list(APPEND VCPKG_MANIFEST_FEATURES "test")
endif()

project(image_process VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_library(image_process)

target_sources(image_process PRIVATE
 src/loader.cpp
 src/bitmaps/bitmap_flat.cpp
 src/loaders/loader_stb.cpp
 src/loaders/loader_webp.cpp
)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(image_process PRIVATE fmt::fmt)
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(image_process PRIVATE spdlog::spdlog)

find_package(Stb REQUIRED)
target_include_directories(image_process PRIVATE ${Stb_INCLUDE_DIR})

find_package(WebP CONFIG REQUIRED)
target_link_libraries(image_process PRIVATE WebP::webp WebP::webpdecoder WebP::webpdemux)

target_include_directories(image_process PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
if(WITH_BENCHMARK)
  add_subdirectory(benchmark)
endif()

install(TARGETS image_process DESTINATION lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_NAME update_server_package)
include(CPack)

include(GNUInstallDirs)
