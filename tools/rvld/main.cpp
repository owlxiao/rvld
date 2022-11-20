#include <string>
#include <vector>

#include "Linker/Linker.h"
#include "utils/Debug.h"

int main(int argc, char **argv) {
  Assert(argc > 1, "Unknown filename");

  Linker::Linker Linker(static_cast<std::string>(argv[1]));
  Linker.Parse();

  return 0;
}
