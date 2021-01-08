#include "loader/loader.h"

#include <stack>
#include <unordered_set>

#include "storage/storage.h"
#include "website/website.h"

namespace pseudogoogle {

void Loader::LoadIntoStorage(Storage& storage) const {
  // stack of pairs of url and depth
  std::stack<std::pair<std::string, int>> urls;
  std::unordered_set<std::string> visited;

  urls.emplace(url_, 0);
  visited.insert(url_);

  while (!urls.empty()) {
    const auto& [url, depth] = urls.top();

    Website website(url);

    // add words to storage
    for (const auto& [word, count] : website.WordCounter()) {
      storage.AddWord(url, word, count);
    }

    // add links
    for (const auto& link_url : website.Links()) {
      if (visited.find(link_url) == visited.end()) {
        urls.emplace(link_url, depth + 1);
        visited.insert(link_url);
      }
    }

    urls.pop();
  }
}

}  // namespace pseudogoogle