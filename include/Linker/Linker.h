#ifndef LINKER_H
#define LINKER_H

#include <string>
#include <vector>

#include "Linker/Parser.h"
#include "utils/ELF.h"

namespace Linker {

class Linker {
 public:
  Linker(const std::string &filename);
  ~Linker() = default;
 public:
  void Parse();
 private:
  // Yes, single file
  std::vector<char> fbuf;
  std::string filename;
  std::unique_ptr<ELF> CurELF;
  std::unique_ptr<Parser> CurParser;
};

} // namespace Linker

#endif // LINKER_H
