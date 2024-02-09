
#include "image_process/loader.h"
#include "image_process/loaders/loader_set.h"
#include <memory>
namespace image_process {

std::unique_ptr<Loader> get_default_loader() {
    auto loader = std::make_unique<Loader_set>();
    return loader;
}
}
