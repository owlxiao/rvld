#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>

#include "utils/ELF.h"

namespace Linker {

class Parser {
public:
  ~Parser() = default;
  Parser(ELF::ELF *ELF, std::vector<char> *buffer) : ELF(ELF), fbuf(buffer){};

public:
  void Parse();
  void parseELFHeader();
  void parseELFSectionHeader();
  void parseElfSymTab();

private:
  /// Parse Helper Class
  Elf64_Shdr *getRawShdrFromIdx(const std::size_t idx);
  char *getRawBytesFromShdrOffset(Elf64_Shdr &s);
  const char *getRawBytesFromShdrIdx(const std::size_t idx);

private:
  ELF::ELF *ELF;
  std::vector<char> *fbuf;
};

} // namespace Linker

#endif // PARSER_H
