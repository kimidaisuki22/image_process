find_package(benchmark CONFIG REQUIRED)

function(add_bench target file)

add_executable(${target} ${file})
target_link_libraries(${target} PRIVATE benchmark::benchmark benchmark::benchmark_main image_process)

endfunction()

add_bench(bm_image_resize bm_image_resize.cpp)
add_bench(bm_image_find_sub bm_image_find_sub.cpp)
add_bench(bm_image_gray_check bm_image_gray_check.cpp)