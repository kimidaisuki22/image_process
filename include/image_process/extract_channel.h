#pragma once
#include <image_process/bitmaps/bitmap.h>
#include <memory>
namespace image_process {
std::unique_ptr<Bitmap_I> extract_channel(const Bitmap_I &src, int channel);
} // namespace image_process