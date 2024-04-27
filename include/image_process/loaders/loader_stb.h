#pragma once

#include <image_process/loader.h>

namespace image_process {
class Loader_stb : public Loader {
public:
  std::optional<std::unique_ptr<Bitmap_I>>
  load_file(const std::string &file_path) override;

  std::optional<std::unique_ptr<Bitmap_I>>
  load(std::span<const uint8_t> buffer) override;

  std::string name() const override;

public:
  // 0 is use channels in file.
  void set_target_channel(int channel);

private:
  int target_channel_{};
};
} // namespace image_process