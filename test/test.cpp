#include "image_process/bitmaps/bitmap_rgba.h"
#include "image_process/bitmaps/single_color_bitmap.h"
#include "image_process/exporters/exporter_factory.h"
#include "image_process/resize.h"
#include "image_process/views/pixel_view.h"
#include "image_process/views/pixel_view_clamp.h"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <image_process/exporter.h>
#include <string>

#define EXPECT_EQ_COLOR_VIEW(a, b)                                             \
  EXPECT_EQ(a.as_span().data(), b.as_span().data());                           \
  EXPECT_EQ(a.as_span().size(), b.as_span().size())

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
  EXPECT_EQ_COLOR_VIEW(view.view_in_1d(0), view(0, 0));
  EXPECT_EQ_COLOR_VIEW(view.view_in_1d(1), view(1, 0));
  EXPECT_EQ_COLOR_VIEW(view.view_in_1d(2), view(0, 1));
  EXPECT_EQ_COLOR_VIEW(view.view_in_1d(3), view(1, 1));
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

TEST(ImageTest, Clamp_view) {
  image_process::Bitmap_RGBA image{2, 2};
  image_process::Pixel_view view{&image};
  for (int i = 0; i < 3; i++) {
    auto color_view = view.view_in_1d(i);
    EXPECT_EQ(color_view.channel(), 4);
    color_view[i] = 255;
    color_view[3] = 255;
  }
  image_process::Pixel_view_clamp clamp_view{&image};
  EXPECT_EQ_COLOR_VIEW(view(0, 0), clamp_view(0, 0));
  EXPECT_EQ_COLOR_VIEW(view(0, 0), clamp_view(-1, 0));
  EXPECT_EQ_COLOR_VIEW(view(0, 0), clamp_view(-1, -1));
  EXPECT_EQ_COLOR_VIEW(view(0, 0), clamp_view(0, -1));
  EXPECT_EQ_COLOR_VIEW(view(1, 1), clamp_view(1, 1));
}