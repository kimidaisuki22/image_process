#pragma once

#include "image_process/bitmaps/bitmap.h"
#include <image_process/loader.h>
#include <memory>
#include <vector>
namespace image_process {
class Loader_set : public Loader {
public:
  std::optional<std::unique_ptr<Bitmap_I>>
  load_file(const std::string &file_path) override {
    for (auto &loader : loaders_) {
      if (auto bitmap = loader->load_file(file_path)) {
        return bitmap;
      }
    }
    return {};
  }

  std::optional<std::unique_ptr<Bitmap_I>>
  load(std::span<const uint8_t> buffer) override {
    for (auto &loader : loaders_) {
      if (auto bitmap = loader->load(buffer)) {
        return bitmap;
      }
    }
    return {};
  }

  void add_load(std::unique_ptr<Loader> &&loader) {
    loaders_.push_back(std::move(loader));
  }

  virtual std::string name() const override { return "Loader set"; }

private:
  std::vector<std::unique_ptr<Loader>> loaders_;
};
} // namespace image_process