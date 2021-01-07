#ifndef PSEUDOGOOGLE_WEBSITE_WEBSITE_H
#define PSEUDOGOOGLE_WEBSITE_WEBSITE_H

#include <unordered_map>
#include <unordered_set>

namespace pseudogoogle {

/**
 * Class used to get words and referenced websites from website.
 * Processes website from url from constructor parameter.
 * After construction, if IsValid is true WordCounter provides count of each
 * found word and links provides referenced websites found.
 * Website can be deemed invalid e.g. if it isn't html.
 */
class Website {
 public:
  Website(const std::string& url);

  // non copyable
  Website(const Website&) = delete;
  Website& operator=(const Website&) = delete;

  ~Website() = default;

  bool IsValid() const { return valid_; }

  const std::unordered_map<std::string, int>& WordCounter() const {
    return word_counter_;
  }

  const std::unordered_set<std::string>& Links() const { return links_; }

 private:
  bool valid_;
  std::unordered_map<std::string, int> word_counter_;
  std::unordered_set<std::string> links_;
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_WEBSITE_WEBSITE_H