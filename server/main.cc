#include <cstdio>
#include <cstring>

#include "loader/loader.h"
#include "options.h"
#include "server/server.h"
#include "storage/storage.h"

constexpr int kDefualtFetcherMaxDepth = 5;

namespace pseudogoogle {

/**
 * Print some help about program
 */
void ShowHelp() {
  std::printf("Psudogoogle\n\n");
  std::printf("TODO show info about params.\n");
}

}  // namespace pseudogoogle

int main(int argc, char* argv[]) {
  // if no params or --help param only then show help
  if (argc == 1) {
    pseudogoogle::ShowHelp();
    return 0;
  }

  pseudogoogle::Options options;
  options.max_depth = kDefualtFetcherMaxDepth;

  for (int i = 1; i < argc; ++i) {
    int tmp;
    if (strncmp(argv[i], "--help", 6) == 0) {
      pseudogoogle::ShowHelp();
      return 0;
    } else if (strncmp(argv[i], "--url=", 6) == 0) {
      options.url = std::string(argv[i] + 6);
    } else if (sscanf(argv[i], "--max-depth=%d", &tmp)) {
      options.max_depth = tmp;
    } else {
      std::fprintf(stderr, "Invalid flag '%s'", argv[i]);
      std::exit(1);
    }
  }

  // load websites data into storage
  pseudogoogle::Storage storage;
  pseudogoogle::Loader loader(options);
  loader.LoadIntoStorage(storage);

  // run server
  pseudogoogle::Server server(storage);
  server.Run();

  return 0;
}