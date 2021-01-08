#include "website/get_request.h"

#include <curl/curl.h>

#include <string>

constexpr int kReadBufferSize = 1024;

size_t WriteFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
  data->append(reinterpret_cast<char*>(ptr), size * nmemb);
  return size * nmemb;
}

namespace pseudogoogle {

GetRequest::GetRequest(const std::string& url) {
  // At least initially implemented with curl
  curl_global_init(CURL_GLOBAL_DEFAULT);
  auto curl = curl_easy_init();
  if (!curl) {
    valid_ = false;
    return;
  }

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFunction);

  std::string header;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content_);
  curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &header);

  long response_code;
  char content_type[128];
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
  curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);

  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  valid_ = response_code == 200;
  content_type_ = std::string(content_type);
}

}  // namespace pseudogoogle