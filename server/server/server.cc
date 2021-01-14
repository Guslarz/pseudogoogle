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

#include "server/client_data.h"
#include "server/server_request.h"
#include "server/server_response.h"
#include "storage/storage.h"
#include "website/website.h"

constexpr int kConnectionQueueSize = 5;

namespace pseudogoogle {

void Server::Run() const {
  int server_socket = OpenServerSocket();
  std::fprintf(stdout, "Server running at port %d\n", port_);
  socklen_t socklen = sizeof(sockaddr_in);

  while (1) {
    ClientData* client_data = new ClientData();
    client_data->socket_fd =
        accept(server_socket, (sockaddr*)&client_data->clientaddr, &socklen);
    client_data->storage = &storage_;

    pthread_t thread_id;
    pthread_create(&thread_id, nullptr, HandleRequest, client_data);
    pthread_detach(thread_id);

    std::fprintf(stdout, "Client connected\n");
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

void* Server::HandleRequest(void* arg) {
  ClientData* client_data = reinterpret_cast<ClientData*>(arg);
  ServerRequest request(client_data->socket_fd);

  const auto& result = client_data->storage->FindAllWords(request.Words());

  ServerResponse response(request.Words(), result);
  response.Send(client_data->socket_fd);

  delete client_data;
  return EXIT_SUCCESS;
}

}  // namespace pseudogoogle