#pragma once
#include "image_process/image_size.h"
#include <cstddef>
#include <image_process/bitmaps/bitmap.h>
#include <vector>
namespace image_process {
class Bitmap_flat : public Bitmap_I {
public:
  Bitmap_flat(int width, int height, int channel);
  uint8_t *data();
  const uint8_t *data() const;

  int width() const;
  int height() const;
  int channel() const;

  size_t size_bytes() const;

private:
  std::vector<uint8_t> storage_;
  Image_size size_;
  int channel_{};
};
} // namespace image_process