#pragma once

#include <cstdint>
namespace image_process {
class Bitmap_I {
public:
  virtual ~Bitmap_I() = default;
  virtual uint8_t* data() = 0;
  virtual const uint8_t *data() const = 0;

  virtual int width() const = 0;
  virtual int height() const = 0;
  virtual int channel() const = 0;

  virtual int stride() const = 0;
};
}