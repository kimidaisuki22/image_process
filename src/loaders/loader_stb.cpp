#include "image_process/bitmaps/bitmap.h"
#include "image_process/bitmaps/bitmap_flat.h"
#include <cstring>
#include <image_process/loaders/loader_stb.h>
#include <memory>
#include <optional>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
namespace image_process {

std::optional<std::unique_ptr<Bitmap_I>>
Loader_stb::load(std::span<const uint8_t> buffer) {
  return {};
}
std::optional<std::unique_ptr<Bitmap_I>>
Loader_stb::load_file(const std::string &file_path) {
  auto file_ptr = fopen(file_path.c_str(), "rb");
    if (!file_ptr) {
      // failed to open file.
      return {};
    }
    int x{};
    int y{};
    int channel{};

    auto buffer = stbi_load_from_file(file_ptr, &x, &y, &channel, target_channel_);
    fclose(file_ptr);

    if (!buffer) {
      // failed to load file.
      return {};
    }
    Bitmap_flat bitmap{x, y, channel};
    memcpy(bitmap.data(), buffer, bitmap.size_in_bytes());
    stbi_image_free(buffer);

    auto ptr = std::make_unique<Bitmap_flat>(std::move(bitmap));

    return ptr;

}
std::string Loader_stb::name() const { return "stb"; }
void Loader_stb::set_target_channel(int channel) { target_channel_ = channel; }
} // namespace image_process