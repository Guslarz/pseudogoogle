#ifndef PSEUDOGOOGLE_STORAGE_STORAGE_H
#define PSEUDOGOOGLE_STORAGE_STORAGE_H

#include <set>
#include <unordered_map>
#include <unordered_set>

#include "util/record.h"

namespace pseudogoogle {

/**
 * Class containing indexed words.
 */
class Storage {
 public:
  Storage() = default;

  // non copyable
  Storage(const Storage&) = delete;
  Storage& operator=(const Storage&) = delete;

  ~Storage() = default;

  void AddWord(const std::string& url, const std::string& word, int word_count);

  const std::set<Record, RecordOrderComparator>* FindWord(
      const std::string& word) const;

  std::set<Record, RecordOrderComparator> FindAllWords(
      const std::unordered_set<std::string>& words) const;

  std::string ToString() const;

 private:
  std::unordered_map<std::string, std::set<Record, RecordOrderComparator>>
      indexed_words_;

  static std::unordered_map<std::string, int> RecordSetToMap(
      const std::set<Record, RecordOrderComparator>& record_set);
  static std::set<Record, RecordOrderComparator> RecordMapToSet(
      const std::unordered_map<std::string, int>& record_map);
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_STORAGE_STORAGE_H