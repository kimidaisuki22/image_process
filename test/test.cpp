#include "image_process/bitmaps/single_color_bitmap.h"
#include "image_process/exporters/exporter_factory.h"
#include "image_process/resize.h"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <image_process/exporter.h>
#include <string>

TEST(ImageTest, Write_image) {
  image_process::Bitmap_single white{};
  std::string filename = "test_image";
  for (auto ext : image_process::get_available_exporter_names()) {
    auto file_path = std::filesystem::path(filename).replace_extension(ext);
    auto exporter = image_process::get_exporter_by_name(ext);
    EXPECT_TRUE(exporter) << file_path  <<"\n";
    auto large_image = image_process::scale_up_to_height(white, 64);
    ASSERT_TRUE(large_image);
    ASSERT_TRUE(*large_image);
    auto img = exporter->export_to_buffer(**large_image);
    EXPECT_TRUE(img);
    EXPECT_TRUE(!img->empty());

    std::ofstream file{file_path,std::ios::binary};

    file.write(reinterpret_cast<const char*>(img->data()), img->size());
  }
}
