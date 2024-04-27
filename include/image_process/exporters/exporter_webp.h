#pragma once
#include <image_process/exporter.h>

namespace image_process {
class Exporter_webp : public Exporter {
public:
  std::optional<std::vector<uint8_t>> export_to_buffer(const Bitmap_I &bitmap);
  // set quality from 0 to 100.
  void set_quality(float quality);

  std::string file_extension() const;

private:
  std::optional<float> quality_factor_;
};
} // namespace image_mix
