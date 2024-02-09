#pragma once
#include "image_process/bitmaps/bitmap_flat.h"
#include <image_process/bitmaps/bitmap.h>
#include <vector>
namespace image_process {
class Bitmap_RGBA : public Bitmap_flat {
public:
  Bitmap_RGBA(int width, int height) : Bitmap_flat(width, height, 4) {}
};
} // namespace image_process