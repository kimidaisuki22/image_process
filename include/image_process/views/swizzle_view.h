#pragma once
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace image_process {
struct Swizzle_item {
  enum Type {
    const_value = -1, // will use target_value_;
    ch0 = 0,
    // chn = n
  };
  Type type_;

  uint8_t target_value_{};
};
class Swizzler {
public:
  Swizzler(std::vector<Swizzle_item> items) : items_(std::move(items)) {}
  int output_channel() const noexcept { return items_.size(); }
  // if out of range, it will return false.
  bool swizzle_to(std::span<const uint8_t> from, std::span<uint8_t> to) const {
    assert(to.size() == items_.size());
    for (size_t i{}; i < items_.size(); i++) {
      if (items_[i].type_ >= 0) {
        auto index = items_[i].type_;
        if (index >= from.size()) {
          assert(false);
          return false;
        }
        to[i] = from[index];
      } else if (items_[i].type_ == Swizzle_item::const_value) {
        to[i] = items_[i].target_value_;
      } else {
        assert(false);
        return false;
      }
    }
    return true;
  }

private:
  std::vector<Swizzle_item> items_;
};
} // namespace image_process