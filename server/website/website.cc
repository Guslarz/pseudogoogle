#include "website/website.h"

#include <gumbo.h>

#include <cstdio>
#include <regex>
#include <stack>

#include "website/get_request.h"

namespace pseudogoogle {

Website::Website(const std::string& url) {
  GetRequest request(url);
  if (!request.IsValid() || request.ContentType() != "text/html") {
    valid_ = false;
    return;
  }
  valid_ = true;
  Parse(request.Content());
}

void Website::Parse(const std::string& document) {
  GumboOutput* output = gumbo_parse(document.c_str());
  std::stack<GumboNode*> nodes;
  nodes.push(output->root);

  while (!nodes.empty()) {
    const auto* node = nodes.top();
    nodes.pop();

    const GumboElement* element;
    const GumboVector* children;

    switch (node->type) {
      case GUMBO_NODE_TEXT:
        HandleText(node);
        break;
      case GUMBO_NODE_ELEMENT:
        element = &node->v.element;
        // ignore scripts and styles
        if (element->tag == GUMBO_TAG_SCRIPT ||
            element->tag == GUMBO_TAG_STYLE) {
          break;
        }

        if (element->tag == GUMBO_TAG_A) {
          HandleLink(node);
        }

        // add children
        children = &element->children;
        for (unsigned int i = 0; i < children->length; ++i) {
          nodes.push(reinterpret_cast<GumboNode*>(children->data[i]));
        }
        break;
      default:
        break;
    }
  }

  gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void Website::HandleText(const GumboNode* node) {
  const static std::regex kWordRegex(R"([^\W_]+(?:['_-][^\W_]+)*)");

  std::string text = std::string(node->v.text.text);
  for (std::sregex_iterator it =
           std::sregex_iterator(text.begin(), text.end(), kWordRegex);
       it != std::sregex_iterator(); ++it) {
    AddWord(it->str());
  }
}

void Website::HandleLink(const GumboNode* node) {
  GumboAttribute* href =
      gumbo_get_attribute(&node->v.element.attributes, "href");
  if (href) {
    links_.emplace(href->value);
  }
}

void Website::AddWord(const std::string& word) {
  auto it = word_counter_.find(word);
  if (it != word_counter_.end()) {
    it->second = it->second + 1;
  } else {
    word_counter_.emplace(word, 1);
  }
}

}  // namespace pseudogoogle