#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>

#include "utils/ELF.h"

namespace Linker {

class Parser {
 public:
  ~Parser() = default;
  Parser(ELF *ELF, std::vector<char> *buffer) : ELF(ELF), fbuf(buffer) {};

 public:
  void Parse();
  void parseELFHeader();
  void parseELFSectionHeader();

 private:
  ELF *ELF;
  std::vector<char> *fbuf;
};


}

#endif // PARSER_H
