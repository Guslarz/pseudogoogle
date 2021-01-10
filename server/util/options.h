#ifndef PSEUDOGOOGLE_UTIL_OPTIONS_H
#define PSEUDOGOOGLE_UTIL_OPTIONS_H

#include <string>

namespace pseudogoogle {

struct Options {
  std::string url;
  int max_depth;
  int node_limit;
  int port;
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_UTIL_OPTIONS_H