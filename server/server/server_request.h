#ifndef PSEUDOGOOGLE_SERVER_SERVER_REQUEST_H
#define PSEUDOGOOGLE_SERVER_SERVER_REQUEST_H

#include <string>
#include <unordered_set>

namespace pseudogoogle {

/**
 * Class used to read clinet's request send to server.
 * Request is:
 *  - uint32_t length (4 bytes)
 *  - char* query string (`length` bytes)
 * Query string is split into words.
 */
class ServerRequest {
 public:
  ServerRequest(int socket_fd);

  // non copyable
  ServerRequest(const ServerRequest&) = delete;
  ServerRequest& operator=(const ServerRequest&) = delete;

  ~ServerRequest() = default;

  const std::string& QueryString() const { return query_string_; }

  const std::unordered_set<std::string>& Words() const { return words_; }

 private:
  std::string query_string_;
  std::unordered_set<std::string> words_;

  void SplitQueryString();

  static void ReadToBuffer(int socket_fd, char* buffer, size_t buffer_size);
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_SERVER_SERVER_REQUEST_H