
#include "image_process/bitmaps/bitmap_rgba.h"
#include "image_process/exporters/exporter_stb.h"
#include "image_process/find/find_same_image.h"
#include "image_process/image_position.h"
#include "image_process/views/color_view.h"
#include "image_process/views/pixel_view.h"
#include <array>
#include <cstdint>
#include <fstream>
#include <gtest/gtest.h>
#include <image_process/draw/rect_border.h>
#include <image_process/draw/rect_fill.h>

TEST(ImageTest, draw) {
  image_process::Bitmap_RGBA basic_image{1024, 1024};
  auto view = image_process::Pixel_view{&basic_image};
  for (int i = 0; i < view.pixel_count(); i++) {
    auto color = view.view_in_1d(i);
    for (auto &c : color.as_span()) {
      c = 255;
    }
  }
  image_process::Bitmap_RGBA red_image{64, 64};
  const image_process::Image_position red_position{182, 75};
  {
    std::array<uint8_t, 4> red{255, 0, 0, 255};
    image_process::Color_view color{red.data(), red.size()};
    image_process::draw::rect_fill(red_image, color, 0, 0, red_image.width(),
                                   red_image.height());
    image_process::draw::rect_fill(basic_image, color, red_position.x(),
                                   red_position.y(), red_image.width(),
                                   red_image.height());
  }

  auto result = image_process::find::find_same_image(basic_image, red_image, 3);
  EXPECT_TRUE(result.has_value());

  EXPECT_EQ(result->x(), red_position.x());
  EXPECT_EQ(result->y(), red_position.y());

  std::array<uint8_t, 4> green_buffer{0, 255, 0, 255};
  image_process::Color_view green{green_buffer.data(), green_buffer.size()};
  image_process::draw::rect_border(basic_image, green, result->x(), result->y(),
                                   red_image.width(), red_image.height());

  image_process::Exporter_stb_png exporter;
  auto image = exporter.export_to_buffer(basic_image);
  EXPECT_TRUE(image.has_value());

  std::ofstream file{"find_sub.png", std::ios::binary};
  file.write(reinterpret_cast<const char*>(image->data()), image->size());
}