#include "server/server.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "storage/storage.h"
#include "website/website.h"

struct Client {
  int socket_fd;
  sockaddr_in clientaddr;
  const pseudogoogle::Storage* storage;
};

constexpr int kConnectionQueueSize = 5;

void* HandleRequest(void* arg) { return EXIT_SUCCESS; }

namespace pseudogoogle {

void Server::Run() const {
  // TODO
  // Run server
  // Decide how to request data from it and what response is
  // Implement everything
  int server_socket = OpenServerSocket();
  std::fprintf(stdout, "Server running at port %d\n", port_);
  socklen_t socklen = sizeof(sockaddr_in);

  while (1) {
    Client* client = new Client();
    client->socket_fd =
        accept(server_socket, (sockaddr*)&client->clientaddr, &socklen);
    client->storage = &storage_;

    pthread_t thread_id;
    pthread_create(&thread_id, nullptr, HandleRequest, client);
    pthread_detach(thread_id);
  }

  close(server_socket);
}

int Server::OpenServerSocket() const {
  static int on = 1;

  sockaddr_in socket_addr{.sin_family = AF_INET, .sin_port = htons(port_)};
  socket_addr.sin_addr.s_addr = INADDR_ANY;

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
  bind(socket_fd, reinterpret_cast<sockaddr*>(&socket_addr), sizeof(sockaddr));
  listen(socket_fd, kConnectionQueueSize);

  return socket_fd;
}

}  // namespace pseudogoogle