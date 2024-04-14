#pragma once
#include "image_process/views/color_view.h"
#include <cstdint>
#include <image_process/bitmaps/bitmap.h>
namespace image_process {
class Pixel_view {
public:
  Pixel_view(Bitmap_I *bitmap) : bitmap_(bitmap) {}
  Color_view operator()(int w, int h) {
    auto ptr = bitmap_->data() + bitmap_->stride() * h + bitmap_->channel() * w;
    Color_view view{ptr, bitmap_->channel()};
    return view;
  }

  int pixel_count() const { return width() * height(); }
  Color_view view_in_1d(int n) { return (*this)(n % width(), n / width()); }

  int width() const { return bitmap_->width(); }
  int height() const { return bitmap_->height(); }

private:
  Bitmap_I *bitmap_;
};
} // namespace image_process