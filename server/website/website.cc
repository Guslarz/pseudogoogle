#include "website/website.h"

#include <myhtml/api.h>

namespace pseudogoogle {

Website::Website(const std::string& url) {
  // TODO
  // http get request to get website
  // verify content-type
  // parse using gumbo
  // add words to word_counter_ and link to links

  // example myhtml code

  char html[] = "<div><span>HTML</span></div>";

  // basic init
  myhtml_t* myhtml = myhtml_create();
  myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

  // first tree init
  myhtml_tree_t* tree = myhtml_tree_create();
  myhtml_tree_init(tree, myhtml);

  // parse html
  myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));

  // print result
  // or see serialization function with callback:
  // myhtml_serialization_tree_callback
  mycore_string_raw_t str = {0};
  myhtml_serialization_tree_buffer(myhtml_tree_get_document(tree), &str);
  printf("%s\n", str.data);

  // release resources
  mycore_string_raw_destroy(&str, false);
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);
}

}  // namespace pseudogoogle