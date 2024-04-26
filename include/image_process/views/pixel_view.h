#pragma once
#include "image_process/views/color_view.h"
#include <image_process/bitmaps/bitmap.h>
namespace image_process {
class Pixel_view {
public:
  Pixel_view(Bitmap_I *bitmap) : bitmap_(bitmap) {
    data_ = bitmap->data();
    width_ = bitmap->width();
    height_ = bitmap->height();
    channel_ = bitmap->channel();
    stride_ = bitmap->stride();
  }
  Color_view operator()(int w, int h) {
    auto ptr = data_ + stride_ * h + channel_ * w;
    Color_view view{ptr, channel_};
    return view;
  }

  int pixel_count() const { return width() * height(); }
  Color_view view_in_1d(int n) { return (*this)(n % width(), n / width()); }

  int width() const { return width_; }
  int height() const { return height_; }

private:
  Bitmap_I *bitmap_;
  uint8_t *data_{};
  int width_{};
  int height_{};
  int channel_{};
  int stride_{};
};

class Const_pixel_view {
public:
  Const_pixel_view(const Bitmap_I *bitmap) {
    data_ = bitmap->data();
    width_ = bitmap->width();
    height_ = bitmap->height();
    channel_ = bitmap->channel();
    stride_ = bitmap->stride();
  }
  Const_color_view operator()(int w, int h) {
    auto ptr = data_ + stride_ * h + channel_ * w;
    Const_color_view view{ptr, channel_};
    return view;
  }

  int pixel_count() const { return width() * height(); }
  Const_color_view view_in_1d(int n) {
    return (*this)(n % width(), n / width());
  }

  int width() const { return width_; }
  int height() const { return height_; }

private:
  const uint8_t *data_{};
  int width_{};
  int height_{};
  int channel_{};
  int stride_{};
};
} // namespace image_process