#ifndef ELF_H
#define ELF_H

#include <vector>
#include <elf.h>

class ELF {
public:
  ~ELF() = default;
  ELF() = default;

public:
  void set_ehdr(Elf64_Ehdr &e) { this->ehdr = e; }
  Elf64_Ehdr get_ehdr() { return this->ehdr; };

  std::vector<Elf64_Shdr> *get_shdr() { return &shdr; }

private:
  // ELF header
  Elf64_Ehdr ehdr;
  // section header table
  std::vector<Elf64_Shdr> shdr;
};

#endif // ELF_H
