#include "image_process/exporters/exporter_webp.h"
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <webp/encode.h>
namespace image_process {
std::string Exporter_webp::file_extension() const { return ".webp"; }
void Exporter_webp::set_quality(float quality) { quality_factor_ = quality; }
std::optional<std::vector<uint8_t>>
Exporter_webp::export_to_buffer(const Bitmap_I &bitmap) {
  uint8_t *buffer{};
  using Func = decltype(WebPEncodeRGB);
  auto fn = [&] {
    auto channel = bitmap.channel();
    if (channel == 3) {
      return WebPEncodeRGB;
    } else if (channel == 4) {
      return WebPEncodeRGBA;
    } else {
      assert(false);
      return WebPEncodeRGB;
    }
  }();
  size_t buffer_size =
      fn(bitmap.data(), bitmap.width(), bitmap.height(), bitmap.stride(),
         quality_factor_.value_or(80), &buffer);
  if (!buffer_size) {
    return {};
  }

  std::vector<uint8_t> buffer_vector{buffer, buffer + buffer_size};
  free(buffer);
  return buffer_vector;
}
} // namespace image_process
