#include "image_process/bitmaps/bitmap_flat.h"
#include "image_process/views/pixel_view.h"
#include <cstddef>
#include <image_process/bitmaps/bitmap.h>
#include <image_process/swizzle.h>
#include <image_process/views/swizzle_view.h>
#include <memory>

namespace image_process {
std::unique_ptr<Bitmap_I> swizzle_image(const Bitmap_I &src,
                                        const Swizzler &swizzler) {
  auto output = std::make_unique<Bitmap_flat>(src.width(), src.height(),
                                              swizzler.output_channel());
  auto &dest = *output;

  Const_pixel_view src_view{&src};
  Pixel_view dest_view{&dest};

  for (size_t i{}; i < src_view.pixel_count(); i++) {
    swizzler.swizzle_to(src_view.view_in_1d(i).as_span(),
                        dest_view.view_in_1d(i).as_span());
  }
  return output;
}
} // namespace image_process