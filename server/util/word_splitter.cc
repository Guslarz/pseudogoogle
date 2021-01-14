#include "util/word_splitter.h"

#include <regex>

const static std::regex kWordRegex(R"([^\W_]+(?:['_-][^\W_]+)*)");

namespace pseudogoogle {

std::sregex_iterator WordSplitter::begin() const {
  return std::sregex_iterator(target_.begin(), target_.end(), kWordRegex);
}

}  // namespace pseudogoogle
