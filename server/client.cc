#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "util/coding.h"

int main(int argc, char* argv[]) {
  char buffer[128];
  int fd;
  struct sockaddr_in srv;
  struct hostent* addrent;

  addrent = gethostbyname(argv[1]);

  srv.sin_family = AF_INET;
  srv.sin_port = htons(atoi(argv[2]));
  memcpy(&srv.sin_addr.s_addr, addrent->h_addr, addrent->h_length);

  fd = socket(AF_INET, SOCK_STREAM, 0);
  connect(fd, (struct sockaddr*)&srv, sizeof(srv));

  std::string word;
  std::cout << "Slowo: ";
  std::cin >> word;

  char word_length[4];
  pseudogoogle::EncodeFixed32(word_length, word.size());

  // write length of word
  size_t wcount = 0;
  while (wcount != 4) {
    wcount += write(fd, word_length + wcount, 4 - wcount);
  }

  // write word
  wcount = 0;
  while (wcount != word.size()) {
    wcount += write(fd, word.c_str() + wcount, word.size() - wcount);
  }

  // read response type
  uint8_t type;
  while (read(fd, &type, 1) == 0) {
    continue;
  }

  if (type == 1) {
    printf("Word not found\n");
  } else {
    printf("Word found\n");
  }

  close(fd);

  return 0;
}