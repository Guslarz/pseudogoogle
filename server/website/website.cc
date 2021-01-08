#include "website/website.h"

#include <cstdio>

#include "website/get_request.h"

namespace pseudogoogle {

Website::Website(const std::string& url) {
  // TODO
  // http get request to get website
  // verify content-type
  // parse using gumbo
  // add words to word_counter_ and link to links
  GetRequest request(url);
  if (!request.IsValid() || request.ContentType() != "text/html") {
    valid_ = false;
    return;
  }
}

}  // namespace pseudogoogle