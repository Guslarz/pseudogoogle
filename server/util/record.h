#ifndef PSEUDOGOOGLE_UTIL_RECORD_H
#define PSEUDOGOOGLE_UTIL_RECORD_H

#include <string>

namespace pseudogoogle {

/**
 * Stores url and corresponding word count as used in storage
 */
class Record {
 public:
  Record(const std::string& url, int word_count)
      : url_(url), word_count_(word_count) {}

  // non copyable
  Record(const Record&) = delete;
  Record& operator=(const Record&) = delete;

  ~Record() = default;

  const std::string& Url() const { return url_; }
  int WordCount() const { return word_count_; }

 private:
  const std::string url_;
  const int word_count_;
};

/**
 * Orders Records first descending by word count then ascending by url
 */
class RecordOrderComparator {
 public:
  bool operator()(const Record& lhs, const Record& rhs) const {
    int word_count_diff = lhs.WordCount() - rhs.WordCount();
    if (word_count_diff > 0) {
      return true;
    } else if (word_count_diff == 0) {
      return lhs.Url() < rhs.Url();
    } else {
      return false;
    }
  }
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_UTIL_RECORD_H