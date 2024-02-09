#include <image_process/exporters/exporter_stb.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
namespace image_process {
std::optional<std::vector<uint8_t>>
Exporter_stb_jpg::export_to_buffer(const Bitmap_I &bitmap) {
  std::vector<uint8_t> buffer_vector{};
  auto write_back = [](void *context, void *data, int size) {
    auto buffer = reinterpret_cast<std::vector<uint8_t> *>(context);
    auto data_u8 = reinterpret_cast<uint8_t *>(data);
    buffer->insert(buffer->end(), data_u8, data_u8 + size);
  };
  stbi_write_jpg_to_func(write_back, &buffer_vector, bitmap.width(),
                         bitmap.height(), bitmap.channel(), bitmap.data(),
                         quality_factor_.value_or(70));

  return buffer_vector;
}
void Exporter_stb_jpg::set_quality(int quality) { quality_factor_ = quality; }
std::string Exporter_stb_jpg::file_extension() const { return ".jpg"; }
std::string Exporter_stb_png::file_extension() const { return ".png"; }
std::optional<std::vector<uint8_t>>
Exporter_stb_png::export_to_buffer(const Bitmap_I &bitmap) {
  std::vector<uint8_t> buffer_vector{};
  auto write_back = [](void *context, void *data, int size) {
    auto buffer = reinterpret_cast<std::vector<uint8_t> *>(context);
    auto data_u8 = reinterpret_cast<uint8_t *>(data);
    buffer->insert(buffer->end(), data_u8, data_u8 + size);
  };
  stbi_write_png_to_func(write_back, &buffer_vector, bitmap.width(),
                         bitmap.height(), bitmap.channel(), bitmap.data(),
                         bitmap.stride());

  return buffer_vector;
}
std::optional<std::vector<uint8_t>>
Exporter_stb_bmp::export_to_buffer(const Bitmap_I &bitmap) {
  std::vector<uint8_t> buffer_vector{};
  auto write_back = [](void *context, void *data, int size) {
    auto buffer = reinterpret_cast<std::vector<uint8_t> *>(context);
    auto data_u8 = reinterpret_cast<uint8_t *>(data);
    buffer->insert(buffer->end(), data_u8, data_u8 + size);
  };
  stbi_write_bmp_to_func(write_back, &buffer_vector, bitmap.width(),
                         bitmap.height(), bitmap.channel(), bitmap.data());

  return buffer_vector;
}
std::string Exporter_stb_bmp::file_extension() const { return ".bmp"; }
} // namespace image_process