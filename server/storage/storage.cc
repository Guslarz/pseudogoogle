#include "storage/storage.h"

namespace pseudogoogle {

void Storage::AddWord(const std::string& url, const std::string& word,
                      int word_count) {
  // TODO
  // add word and empty ser if first time
  // else add new record to existing set
}

const std::set<Record, RecordOrderComparator>* Storage::FindWord(
    const std::string& word) const {
  // TODO
  // return set of records corresponding to specified word
  // or nullptr if not found
  return nullptr;
}

}  // namespace pseudogoogle
