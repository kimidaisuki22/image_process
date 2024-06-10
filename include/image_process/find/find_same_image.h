#pragma once
#include "image_process/bitmaps/bitmap.h"
#include <image_process/image_position.h>
#include <optional>

namespace image_process::find {
std::optional<image_process::Image_position>
find_same_image(const Bitmap_I &main_image, const Bitmap_I &sub_image,
                int total_channel);
} // namespace image_process::find