#pragma once
#include <image_process/views/pixel_view.h>
#include <cassert>
#include <image_process/bitmaps/bitmap.h>
namespace image_process {
class Pixel_view_clamp {
public:
  Pixel_view_clamp(Bitmap_I *bitmap) : view_(bitmap) {}
  Color_view operator()(int w, int h) {
    assert(width() > 0);
    assert(height() > 0);
    if (width() == 0 || height() == 0) {
      return {nullptr, 0};
    }
    if (w >= width()) {
      w = width() - 1;
    }
    if (w < 0) {
      w = 0;
    }
    if (h >= height()) {
      h = height() - 1;
    }
    if (h < 0) {
      h = 0;
    }
    return view_(w, h);
  }

  int pixel_count() const { return width() * height(); }

  int width() const { return view_.width(); }
  int height() const { return view_.height(); }

private:
  Pixel_view view_;
};
} // namespace image_process