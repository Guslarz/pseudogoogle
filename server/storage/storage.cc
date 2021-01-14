#include "storage/storage.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace pseudogoogle {

void Storage::AddWord(const std::string& url, const std::string& word,
                      int word_count) {
  auto it = indexed_words_.find(word);
  if (it == indexed_words_.end()) {
    it = indexed_words_.emplace(word, std::set<Record, RecordOrderComparator>())
             .first;
  }
  it->second.emplace(url, word_count);
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

std::set<Record, RecordOrderComparator> Storage::FindAllWords(
    const std::unordered_set<std::string>& words) const {
  // return empty set if no words
  if (words.size() == 0) {
    return {};
  }

  std::vector<const std::set<Record, RecordOrderComparator>*> record_sets;
  std::transform(words.begin(), words.end(), std::back_inserter(record_sets),
                 [=](std::string word) { return FindWord(word); });

  // if set for any word is nullptr then return empty set
  for (const auto* record_set : record_sets) {
    if (record_set == nullptr) {
      return {};
    }
  }

  // return intersection of all sets
  std::set<Record, RecordOrderComparator> result(*record_sets.back());
  record_sets.pop_back();
  for (const auto* record_set : record_sets) {
    for (const auto& record : result) {
      if (record_set->find(record) == record_set->end()) {
        result.erase(record);
      }
    }
  }

  return result;
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
