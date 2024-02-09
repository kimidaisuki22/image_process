#pragma once

#include "image_process/exporter.h"
#include <memory>
namespace image_process {
std::unique_ptr<Exporter> get_exporter_by_name(std::string_view name);
std::vector<std::string_view> get_available_exporter_names();
} // namespace image_process
