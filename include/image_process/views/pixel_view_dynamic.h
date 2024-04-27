#pragma once
#include <image_process/views/color_view.h>
#include <image_process/bitmaps/bitmap.h>
namespace image_process {
// dynamic version of pixel view, it will not keep bitmap info inside it.
// it just calls bitmap to get infos.
class Pixel_view_dynamic {
public:
  Pixel_view_dynamic(Bitmap_I *bitmap) : bitmap_(bitmap) {}
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