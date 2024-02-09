#pragma once
#include <cstdint>
#include <image_process/bitmaps/bitmap.h>
#include <memory>
#include <optional>
#include <span>
#include <string>
namespace image_process {
class Loader {
public:
  virtual ~Loader() = default;
  virtual std::optional<std::unique_ptr<Bitmap_I>>
  load_file(const std::string &file_path) = 0;
  virtual std::optional<std::unique_ptr<Bitmap_I>>
  load(std::span<const uint8_t> buffer) = 0;
  virtual std::string name() const = 0;
};

std::unique_ptr<Loader> get_default_loader();
} // namespace image_process
