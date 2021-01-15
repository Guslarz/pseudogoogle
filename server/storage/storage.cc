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

  // if set for any word is nullptr then return empty set
  for (const auto& word : words) {
    if (FindWord(word) == nullptr) {
      return {};
    }
  }

  auto it = words.cbegin();
  std::unordered_map<std::string, int> result = RecordSetToMap(*FindWord(*it));
  for (++it; it != words.cend(); ++it) {
    std::unordered_map<std::string, int> record_map =
        RecordSetToMap(*FindWord(*it));
    std::unordered_map<std::string, int> next_result;
    for (const auto& [url, word_count] : result) {
      auto record_map_it = record_map.find(url);
      if (record_map_it != record_map.end()) {
        next_result.emplace(url, word_count + record_map_it->second);
      }
    }
    result = next_result;
  }

  return RecordMapToSet(result);
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

std::unordered_map<std::string, int> Storage::RecordSetToMap(
    const std::set<Record, RecordOrderComparator>& record_set) {
  std::unordered_map<std::string, int> record_map;
  for (const auto& record : record_set) {
    record_map.emplace(record.Url(), record.WordCount());
  }
  return record_map;
}

std::set<Record, RecordOrderComparator> Storage::RecordMapToSet(
    const std::unordered_map<std::string, int>& record_map) {
  std::set<Record, RecordOrderComparator> record_set;
  for (const auto& [url, word_count] : record_map) {
    record_set.emplace(url, word_count);
  }
  return record_set;
}

}  // namespace pseudogoogle
