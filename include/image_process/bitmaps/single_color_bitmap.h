#pragma once
#include <array>
#include <image_process/bitmaps/bitmap.h>
namespace image_process {

class Bitmap_single : public Bitmap_I {
public:
  Bitmap_single(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255,
                uint8_t a = 255)
      : data_{r, g, b, a} {}

  uint8_t *data() override { return data_.data(); }
  const uint8_t *data() const override { return data_.data(); }
  int width() const override { return 1; }
  int height() const override { return 1; }
  int channel() const override { return 4; }
  int stride() const override {return 4; }

private:
  std::array<uint8_t, 4> data_;
};
} // namespace image_process