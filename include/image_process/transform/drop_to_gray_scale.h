#pragma once

#include "image_process/bitmaps/bitmap.h"
#include <memory>
namespace image_process::transform {
    // remove other channel, only keep first channel.
std::unique_ptr<Bitmap_I> drop_to_gray_scale_image(const Bitmap_I &src);
}