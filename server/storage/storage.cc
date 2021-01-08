#include "storage/storage.h"

#include <sstream>
#include <string>

namespace pseudogoogle {

void Storage::AddWord(const std::string& url, const std::string& word,
                      int word_count) {
  auto it = indexed_words_.find(word);
  if (it == indexed_words_.end()) {
    it = indexed_words_.emplace(url, std::set<Record, RecordOrderComparator>())
             .first;
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
  return nullptr;
}

std::string Storage::ToString() const {
  std::stringstream ss;
  for (const auto& [word, record_set] : indexed_words_) {
    ss << word << std::endl;
    for (const auto& record : record_set) {
      ss << "\t" << record.Url() << "\t:\t" << record.WordCount() << std::endl;
    }
    ss << std::endl;
  }
  return ss.str();
}

}  // namespace pseudogoogle
