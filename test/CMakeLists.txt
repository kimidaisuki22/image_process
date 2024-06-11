
enable_testing()
find_package(GTest CONFIG REQUIRED)

function(add_image_test name file)
  add_executable(
  ${name}
  ${file}
)
target_link_libraries(
  ${name}
  PRIVATE
   GTest::gtest_main
   image_process
)
add_test(${name} ${name})
endfunction()

add_image_test(image_test test.cpp)

add_image_test(find_image_test find_sub_test.cpp)
add_image_test(gray_check gray_check.cpp)