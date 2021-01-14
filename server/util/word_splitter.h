#ifndef PSEUDOGOOGLE_UTIL_WORDS_H
#define PSEUDOGOOGLE_UTIL_WORDS_H

#include <regex>

namespace pseudogoogle {

class WordSplitter {
 public:
  WordSplitter(const std::string& target) : target_(target) {}

  // non copyable
  WordSplitter(const WordSplitter&) = delete;
  WordSplitter& operator=(const WordSplitter&) = delete;

  ~WordSplitter() = default;

  std::sregex_iterator begin() const;

  std::sregex_iterator end() const { return std::sregex_iterator(); }

 private:
  const std::string& target_;
};

}  // namespace pseudogoogle

#endif