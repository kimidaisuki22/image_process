#include "image_process/bitmaps/bitmap_flat.h"
#include "webp/decode.h"
#include <_types/_uint8_t.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <image_process/loaders/loader_webp.h>
#include <istream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace image_process {

std::optional<std::unique_ptr<Bitmap_I>>
Loader_webp::load(std::span<const uint8_t> buffer) {
  int x{};
  int y{};
  int channel{};
  uint8_t *data{};
  if (load_as_rgba_) {
    channel = 4;
    data = WebPDecodeRGBA(reinterpret_cast<const uint8_t *>(buffer.data()),
                         buffer.size(), &x, &y);
  } else {
    channel = 3;
    data = WebPDecodeRGB(reinterpret_cast<const uint8_t *>(buffer.data()),
                         buffer.size(), &x, &y);
  }

  if (!data) {
    // failed to parse image.
    return {};
  }

  Bitmap_flat bitmap{x, y, channel};
  memcpy(bitmap.data(), data, bitmap.size_bytes());

  free(data);

  return std::make_unique<Bitmap_flat>(std::move(bitmap));
}
std::optional<std::unique_ptr<Bitmap_I>>
Loader_webp::load_file(const std::string &file_path) {
  std::ifstream file{file_path, std::ios::binary};
  if (!file.is_open()) {
    // failed to open file.
    return {};
  }
  std::vector<uint8_t> buffer{std::istreambuf_iterator<char>{file}, {}};
  return load(buffer);
}
std::string Loader_webp::name() const { return "webp"; }
void Loader_webp::set_load_as_rgba(bool on) { load_as_rgba_ = on; }
} // namespace image_process