#pragma once

#include "image_process/bitmaps/bitmap.h"
#include "image_process/swizzle.h"
#include "image_process/views/swizzle_view.h"
#include <memory>
namespace image_process::transform {
std::unique_ptr<Bitmap_I> drop_to_gray_scale_image(const Bitmap_I &src) {
  Swizzler swizzler{{Swizzle_item{Swizzle_item::ch0}}};
  return swizzle_image(src, swizzler);
}
} // namespace image_process::transform