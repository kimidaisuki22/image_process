#pragma once
#include "image_process/bitmaps/bitmap.h"
#include <memory>
#include <optional>
namespace image_process {
std::optional<std::unique_ptr<Bitmap_I>> scale_down_to_height(Bitmap_I &bitmap,
                                                          int target_height);
} // namespace image_process