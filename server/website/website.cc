#include "website/website.h"

#include <gumbo.h>

namespace pseudogoogle {

Website::Website(const std::string& url) {
  // TODO
  // http get request to get website
  // verify content-type
  // parse using gumbo
  // add words to word_counter_ and link to links

  GumboOutput* output = gumbo_parse("<h1>Hello, World!</h1>");
  // Do stuff with output->root
  gumbo_destroy_output(&kGumboDefaultOptions, output);
}

}  // namespace pseudogoogle