#include "loader/loader.h"

#include <queue>
#include <unordered_set>

#include "storage/storage.h"
#include "website/website.h"

namespace pseudogoogle {

void Loader::LoadIntoStorage(Storage& storage) const {
  // queue (for BFS) of pairs of url and depth
  std::queue<std::pair<std::string, int>> urls;
  std::unordered_set<std::string> visited;
  int node_count = 0;

  urls.emplace(url_, 0);
  visited.insert(url_);

  while (!urls.empty()) {
    auto [url, depth] = urls.front();
    urls.pop();

    std::printf("Loader: indexing '%s' (depth %d)\n", url.c_str(), depth);

    Website website(url);

    // count only valid websites
    if (website.IsValid()) {
      ++node_count;
    }

    // add words to storage
    for (const auto& [word, count] : website.WordCounter()) {
      storage.AddWord(url, word, count);
    }

    // end if node_limit reached
    if (node_count == node_limit_) {
      std::printf("Loader: node_limit reached\n");
      break;
    }

    // add links if max_depth not reached
    if (depth == max_depth_) {
      continue;
    }

    for (const auto& link_url : website.Links()) {
      if (visited.find(link_url) == visited.end()) {
        urls.emplace(link_url, depth + 1);
        visited.insert(link_url);
      }
    }
  }
}

}  // namespace pseudogoogle