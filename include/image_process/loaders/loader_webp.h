#pragma once

#include <image_process/loader.h>

namespace image_process {
class Loader_webp : public Loader {
public:
  std::optional<std::unique_ptr<Bitmap_I>>
  load_file(const std::string &file_path) override;

  std::optional<std::unique_ptr<Bitmap_I>>
  load(std::span<const uint8_t> buffer) override;

  std::string name() const override;

  // on: load image as rgba
  // off: load image as rgb
  // default is on
  void set_load_as_rgba(bool on);

private:
  bool load_as_rgba_{true};
};
} // namespace image_process