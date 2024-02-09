#include "image_process/exporters/exporter_stb_ico.h"
#include "image_process/image_size.h"
namespace  {
struct Icon_dir {
    const uint16_t reserved_{};
    const uint16_t image_type{1}; // 1 or 2, 1 for ICO, 2for CUR
    uint16_t image_count_{};
  };
  struct Icon_dir_entry {
    image_process::Exporter_ico::Image_size size_;
    bool use_color_palette_;
    const uint8_t reserved_{};
    uint16_t dynamic_;
    uint16_t bits_per_pixel_or_pixel_to_top_;
    uint32_t image_buffer_size_;
    uint32_t absolute_offset_in_file_;
  };
}
namespace image_process {

std::optional<std::vector<uint8_t>>
Exporter_ico::export_to_buffer(const Bitmap_I &bitmap) {
  if (bitmap.width() > 256 || bitmap.height() > 256) {
    // image is to big!
    return {};
  }
  Exporter_stb_png exporter;
  auto layer = exporter.export_to_buffer(bitmap);
  if (!layer) {
    // failed to encode file.
    return {};
  }
  reset(); // clear old buffers.

  sizes_.push_back({static_cast<uint8_t>(bitmap.width()),
                    static_cast<uint8_t>(bitmap.height())});
  buffers_.push_back(std::move(*layer));

  return export_to_buffer();
}
std::string Exporter_ico::file_extension() const { return ".ico"; }
void Exporter_ico::reset() { buffers_.clear(); }
std::optional<std::vector<uint8_t>> Exporter_ico::export_to_buffer() {
  auto buffer_size = compute_buffer_size();
  std::vector<uint8_t> buffer;
  buffer.resize(buffer_size);
  Icon_dir header{};
  header.image_count_ = 1;
  std::vector<Icon_dir_entry> entries{};
  uint32_t cursor = compute_header_size();
  for (uint32_t i{}; i < buffers_.size(); i++) {
    Icon_dir_entry entry{};
    entry.image_buffer_size_ = buffers_[i].size();
    entry.size_ = sizes_[i];
    entry.use_color_palette_ = false;
    // Maybe this value is wrong.
    entry.bits_per_pixel_or_pixel_to_top_ = 8;
    entry.absolute_offset_in_file_ = cursor;
    cursor += entry.image_buffer_size_;
    entries.push_back(entry);
  }

  cursor = 0;
  auto insert = [&cursor, &buffer](auto *pt, size_t bytes_count) {
    assert(cursor + bytes_count <= buffer.size());
    memcpy(buffer.data() + cursor, pt, bytes_count);
    cursor += bytes_count;
  };

  insert(&header, sizeof(header));
  for (auto &e : entries) {
    insert(&e, sizeof(e));
  }
  for (auto &img : buffers_) {
    insert(img.data(), img.size());
  }
  assert(cursor == buffer_size);

  return buffer;
}
size_t Exporter_ico::compute_header_size() {
  static_assert(sizeof(Icon_dir) == 6);
  static_assert(sizeof(Icon_dir_entry) == 16);
  return sizeof(Icon_dir) + sizeof(Icon_dir_entry) * buffers_.size();
}
size_t Exporter_ico::compute_buffer_size() {
  auto size = compute_header_size();
  for (auto &b : buffers_) {
    size += b.size();
  }
  return size;
}
} // namespace image_process