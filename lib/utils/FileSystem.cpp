#include <fstream>

#include "utils/Debug.h"
#include "utils/FileSystem.h"

namespace utils {
namespace FileSystem {

void readFile(const std::string &filename, std::vector<char> &buffer) {
  std::ifstream fs(filename, std::ios::binary | std::ios::in | std::ios::ate);
  Assert(fs.is_open(), "Failed to open");

  std::streamsize fsize = fs.tellg();
  buffer.resize(fsize);
  fs.seekg(0, std::ios::beg);

  if (!fs.read(buffer.data(), fsize)) {
    panic("Failed to read");
  }
  Assert(!buffer.empty(), "File buffer empty");

  fs.close();
}

} // namespace FileSystem
} // namespace utils
