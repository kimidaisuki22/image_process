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
 src/resize.cpp
 src/bitmaps/bitmap_flat.cpp
 src/loaders/loader_stb.cpp
 src/loaders/loader_webp.cpp
 src/exporters/exporter_stb.cpp
 src/exporters/exporter_stb_ico.cpp
 src/exporters/exporter_webp.cpp
 src/exporters/exporter_factory.cpp
)


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


include(GNUInstallDirs)
install(TARGETS image_process
  EXPORT image-process-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

include(CPack)

install(EXPORT image-process-targets
    FILE image-process-targets.cmake
    NAMESPACE image_process::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/image-process
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakeFindDependencyMacro)
find_dependency(Stb)
find_dependency(WebP)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/image-process-config.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/image-process-config.cmake
               @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/image-process-config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/image-process)
