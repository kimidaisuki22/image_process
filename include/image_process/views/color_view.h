#pragma once
#include <cstdint>
#include <image_process/bitmaps/bitmap.h>
#include <span>
namespace image_process {
class Color_view {
public:
  Color_view(uint8_t *data, int size) : channels_(data, size) {}
  uint8_t &operator[](int n) { return channels_[n]; }
  uint8_t operator[](int n) const { return channels_[n]; }
  int channel() const { return channels_.size(); }
  std::span<uint8_t> as_span() { return channels_; };
  std::span<const uint8_t> as_span() const {
    return std::span<const uint8_t>(channels_.data(), channel());
  };

private:
  std::span<uint8_t> channels_{};
};
class Const_color_view {
public:
  Const_color_view(const uint8_t *data, int size) : channels_(data, size) {}
  uint8_t operator[](int n) const { return channels_[n]; }
  int channel() const { return channels_.size(); }
  std::span<const uint8_t> as_span() const { return channels_; };

private:
  std::span<const uint8_t> channels_{};
};
} // namespace image_process