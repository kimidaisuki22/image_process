#pragma once
#include "image_process/exporter.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <optional>
#include <string>
#include <vector>
namespace image_process {

// It store image layers in PNG format, which was introduced in Windows Vista.
class Exporter_ico : public Exporter {
public:
  // Max export size is 256 * 256.
  std::optional<std::vector<uint8_t>> export_to_buffer(const Bitmap_I &bitmap);

  std::string file_extension() const;

  struct Image_size {
    uint8_t width_;
    uint8_t height_;
  };
private:
  void reset();
  std::optional<std::vector<uint8_t>> export_to_buffer();

  size_t compute_header_size();
  size_t compute_buffer_size();

  std::vector<Image_size> sizes_;
  std::vector<std::vector<uint8_t>> buffers_;
};
} // namespace image_mix
