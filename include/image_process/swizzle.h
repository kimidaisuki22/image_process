#pragma once
#include <image_process/bitmaps/bitmap.h>
#include <image_process/views/swizzle_view.h>
#include <memory>

namespace image_process {
std::unique_ptr<Bitmap_I> swizzle_image(const Bitmap_I &src,
                                        const Swizzler &swizzler);
} // namespace image_process