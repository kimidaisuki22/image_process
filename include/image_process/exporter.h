#pragma once
#include <image_process/bitmaps/bitmap.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
namespace image_process {
class Exporter {
public:
  virtual ~Exporter() = default;
  virtual std::optional<std::vector<uint8_t>>
  export_to_buffer(const Bitmap_I &bitmap) = 0;
  virtual std::string file_extension() const = 0;
};
} // namespace image_process
