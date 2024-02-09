#pragma once
#include <image_process/exporter.h>

namespace image_process {
class Exporter_stb_jpg : public Exporter {
public:
  std::optional<std::vector<uint8_t>> export_to_buffer(const Bitmap_I &bitmap);
  // set quality from 0 to 100.
  void set_quality(int quality);

  std::string file_extension() const;
  private:
  std::optional<int> quality_factor_;
};
class Exporter_stb_png : public Exporter {
public:
  std::optional<std::vector<uint8_t>> export_to_buffer(const Bitmap_I &bitmap);

  std::string file_extension() const;
};

class Exporter_stb_bmp : public Exporter {
public:
  std::optional<std::vector<uint8_t>> export_to_buffer(const Bitmap_I &bitmap);

  std::string file_extension() const;
};
} // namespace image_mix
