#include "image_process/bitmaps/bitmap_flat.h"
#include "image_process/bitmaps/bitmap_rgba.h"
#include "image_process/check/gray.h"
#include "image_process/views/color_view.h"
#include "image_process/views/pixel_view.h"
#include <gtest/gtest.h>


TEST(Image_gray_check, one_channel) {
  image_process::Bitmap_flat gray{1,1,1};
  EXPECT_TRUE(image_process::check::is_gray_scale(gray));
}
TEST(Image_gray_check, rgba) {
  image_process::Bitmap_RGBA image{2, 2};
  image_process::Pixel_view view{&image};
  for (int i = 0; i < view.pixel_count(); i++) {
    auto color_view = view.view_in_1d(i);
    EXPECT_EQ(color_view.channel(), 4);
    for(int j=0;j<3;j++){
        color_view[j] = i;
    }
    color_view[3] = 255;
  }
  EXPECT_TRUE(image_process::check::is_gray_scale(image));
  view.view_in_1d(view.pixel_count() - 1)[0] = 0;
  EXPECT_FALSE(image_process::check::is_gray_scale(image));
}
