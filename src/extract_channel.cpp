#include "image_process/extract_channel.h"
#include "image_process/bitmaps/bitmap.h"
#include "image_process/bitmaps/bitmap_flat.h"
#include "image_process/views/pixel_view.h"
#include <memory>
namespace image_process {
std::unique_ptr<Bitmap_I> extract_channel(const Bitmap_I &src, int channel) {
  std::unique_ptr<Bitmap_flat> output =
      std::make_unique<Bitmap_flat>(src.width(), src.height(), 1);
  if (channel >= src.channel()) {
    return output;
  }
  Const_pixel_view src_view{&src};
  Pixel_view dest_view{output.get()};
  for (int y = 0; y < src_view.height(); y++) {
    for (int x = 0; x < dest_view.height(); x++) {
      dest_view(x, y)[0] = src_view(x, y)[channel];
    }
  }

  return output;
}
} // namespace image_process