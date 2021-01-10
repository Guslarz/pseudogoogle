#ifndef PSEUDOGOOGLE_LOADER_LOADER_H
#define PSEUDOGOOGLE_LOADER_LOADER_H

#include "storage/storage.h"
#include "util/options.h"

namespace pseudogoogle {

/**
 * Class loading websites data and storing it in storage.
 * Starts from options.url, continues using links found in website
 * up to options.max_depth
 */
class Loader {
 public:
  Loader(const Options& options)
      : url_(options.url),
        max_depth_(options.max_depth),
        node_limit_(options.node_limit) {}

  void LoadIntoStorage(Storage& storage) const;

 private:
  const std::string url_;
  const int max_depth_;
  const int node_limit_;
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_LOADER_LOADER_H