#pragma once
#include <image_process/bitmaps/bitmap.h>
namespace image_process::check {
// for rgb, return true, if all channel has same value.
// for rgba, just check first 3 channels is same and a is 255.
bool is_gray_scale(const Bitmap_I &bitmap);
} // namespace image_process::check