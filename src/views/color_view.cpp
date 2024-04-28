#include <image_process/views/color_view.h>
bool image_process::is_same_color(const Const_color_view &lhs,
                                  const Const_color_view &rhs) {
  if (lhs.channel() != rhs.channel()) {
    return false;
  }
  return memcmp(lhs.as_span().data(), rhs.as_span().data(),
                lhs.as_span().size_bytes()) == 0;
}
