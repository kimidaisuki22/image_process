#include "image_process/exporter.h"
#include "image_process/exporters/exporter_stb.h"
#include "image_process/exporters/exporter_webp.h"
#include <memory>
namespace image_process {
std::unique_ptr<Exporter> get_exporter_by_name(std::string_view name) {
  if (name == ".jpg") {
    return std::make_unique<Exporter_stb_jpg>();
  } else if (name == ".png") {
    return std::make_unique<Exporter_stb_png>();
  } else if (name == ".bmp") {
    return std::make_unique<Exporter_stb_bmp>();
  } else if (name == ".webp") {
    return std::make_unique<Exporter_webp>();
  }
  return nullptr;
}
std::vector<std::string_view> get_available_exporter_names() {
  return {".jpg", ".png", ".bmp", ".webp"};
}
} // namespace image_process
