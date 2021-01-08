#ifndef PSEUDOGOOGLE_WEBSITE_GET_REQUEST_H
#define PSEUDOGOOGLE_WEBSITE_GET_REQUEST_H

#include <string>

namespace pseudogoogle {

class GetRequest {
 public:
  GetRequest(const std::string& url);

  // non copyable
  GetRequest(const GetRequest&) = delete;
  GetRequest& operator=(const GetRequest&) = delete;

  ~GetRequest() = default;

  bool IsValid() const { return valid_; }

  const std::string& ContentType() const { return content_type_; }

  const std::string& Content() const { return content_; }

 private:
  bool valid_;

  std::string content_type_;
  std::string content_;
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_WEBSITE_GET_REQUEST_H