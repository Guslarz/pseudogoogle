#include "loader/loader.h"

#include <stack>
#include <unordered_set>

#include "storage/storage.h"
#include "website/website.h"

namespace pseudogoogle {

void Loader::LoadIntoStorage(Storage& storage) const {
  // TODO
  // Load websites using Website class  until max_depth_
  // Store results in storage

  // pair of url and depth
  std::stack<std::pair<std::string, int>> urls;
  std::unordered_set<std::string> visited;

  urls.emplace(url_, 0);

  while (!urls.empty()) {
    const auto& [url, depth] = urls.top();
    urls.pop();

    Website website(url);
  }
}

}  // namespace pseudogoogle