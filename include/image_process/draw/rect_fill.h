
#pragma once
#include "image_process/views/color_view.h"
#include "image_process/views/pixel_view.h"
#include <cassert>
#include <image_process/bitmaps/bitmap.h>

namespace image_process ::draw {
inline void rect_fill(Bitmap_I &src, Const_color_view color, int x, int y,
                      int size_x, int size_y) {
  assert(x > 0);
  assert(y > 0);
  assert(x + size_x < src.width());
  assert(y + size_y < src.height());
  assert(src.channel() == color.channel());

  Pixel_view view{&src};

  for (int i = y; i < y + size_y; i++) {
    for (int j = x; j < x + size_x; j++) {
        assign_color(view(j,i), color);
    }
  }
}
} // namespace image_process::draw