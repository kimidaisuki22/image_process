#include <cassert>
#include <image_process/views/color_view.h>
bool image_process::is_same_color(const Const_color_view &lhs,
                                  const Const_color_view &rhs) {
  if (lhs.channel() != rhs.channel()) {
    return false;
  }
  return memcmp(lhs.as_span().data(), rhs.as_span().data(),
                lhs.as_span().size_bytes()) == 0;
}
void image_process::assign_color(Color_view dest, Const_color_view src) {
  assert(dest.channel() == src.channel());

  if (dest.channel() != src.channel()) {
    return;
  }
  for (int i = 0; i < dest.channel(); i++) {
    dest[i] = src[i];
  }
}
