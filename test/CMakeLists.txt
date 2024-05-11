
enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(
  hello_test
  test.cpp
)
target_link_libraries(
  hello_test
  PRIVATE
   GTest::gtest_main
   image_process
)
add_test(image_test hello_test)
