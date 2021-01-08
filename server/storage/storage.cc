#include "storage/storage.h"

namespace pseudogoogle {

void Storage::AddWord(const std::string& url, const std::string& word,
                      int word_count) {
  auto it = indexed_words_.find(word);
  if (it == indexed_words_.end()) {
    auto pair = indexed_words_.emplace(word);
    it = pair.first;
  }
  it->second.emplace(word, word_count);
}

const std::set<Record, RecordOrderComparator>* Storage::FindWord(
    const std::string& word) const {
  auto it = indexed_words_.find(word);
  if (it == indexed_words_.end()) {
    return nullptr;
  } else {
    return &it->second;
  }
}

}  // namespace pseudogoogle
