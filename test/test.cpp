#include "image_process/bitmaps/bitmap_rgba.h"
#include "image_process/bitmaps/single_color_bitmap.h"
#include "image_process/exporters/exporter_factory.h"
#include "image_process/resize.h"
#include "image_process/views/pixel_view.h"
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
    EXPECT_TRUE(exporter) << file_path << "\n";
    auto large_image = image_process::scale_up_to_height(white, 64);
    ASSERT_TRUE(large_image);
    ASSERT_TRUE(*large_image);
    auto img = exporter->export_to_buffer(**large_image);
    EXPECT_TRUE(img);
    EXPECT_TRUE(!img->empty());

    std::ofstream file{file_path, std::ios::binary};

    file.write(reinterpret_cast<const char *>(img->data()), img->size());
  }
}
TEST(ImageTest, View_image) {
  image_process::Bitmap_RGBA image{2, 2};
  std::string filename = "view_image";
  image_process::Pixel_view view{&image};
  for (int i = 0; i < 3; i++) {
    auto color_view = view.view_in_1d(i);
    EXPECT_EQ(color_view.channel(), 4);
    color_view[i] = 255;
    color_view[3] = 255;
  }
  EXPECT_EQ(view.pixel_count(), 2 * 2);
  for (int i = 0; i < view.pixel_count(); i++) {
    auto color_view = view.view_in_1d(i);
    EXPECT_EQ(view.view_in_1d(i).as_span().data() - image.data(),
              i * image.channel());
  }
  EXPECT_EQ(view.view_in_1d(0).as_span().data(), view(0, 0).as_span().data());
  EXPECT_EQ(view.view_in_1d(1).as_span().data(), view(1, 0).as_span().data());
  EXPECT_EQ(view.view_in_1d(2).as_span().data(), view(0, 1).as_span().data());
  EXPECT_EQ(view.view_in_1d(3).as_span().data(), view(1, 1).as_span().data());
  for (auto ext : image_process::get_available_exporter_names()) {
    auto file_path = std::filesystem::path(filename).replace_extension(ext);
    auto exporter = image_process::get_exporter_by_name(ext);
    EXPECT_TRUE(exporter) << file_path << "\n";
    auto img = exporter->export_to_buffer(image);
    EXPECT_TRUE(img);
    EXPECT_TRUE(!img->empty());

    std::ofstream file{file_path, std::ios::binary};

    file.write(reinterpret_cast<const char *>(img->data()), img->size());
  }
}