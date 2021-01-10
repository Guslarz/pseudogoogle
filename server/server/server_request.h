#ifndef PSEUDOGOOGLE_SERVER_SERVER_REQUEST_H
#define PSEUDOGOOGLE_SERVER_SERVER_REQUEST_H

#include <string>

namespace pseudogoogle {

/**
 * Class used to read clinet's request send to server.
 * At least for now expects:
 *  - uint32_t length (4 bytes)
 *  - char* word (length bytes)
 */
class ServerRequest {
 public:
  ServerRequest(int socket_fd);

  // non copyable
  ServerRequest(const ServerRequest&) = delete;
  ServerRequest& operator=(const ServerRequest&) = delete;

  ~ServerRequest() = default;

  const std::string& Word() const { return word_; }

 private:
  std::string word_;

  static void ReadToBuffer(int socket_fd, char* buffer, size_t buffer_size);

  static std::uint32_t DecodeLength(char* buffer);
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_SERVER_SERVER_REQUEST_H