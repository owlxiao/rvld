#include "Linker/Parser.h"
#include "utils/Debug.h"

#include <iostream>

namespace Linker {

void Parser::parseELFHeader() {
  uint32_t magic = *(uint32_t *)fbuf->data();
  Assert(magic == 0x464c457f, "Not an ELF file");

  Elf64_Ehdr ehdr;
  ehdr = *(Elf64_Ehdr *)fbuf->data();

  // Get the number of entries in the section header table ( e_shnum )
  //
  // If the number of entries in the section header table is larget than
  //  or equal to SHN_LORSERVE, e_shnum holds the value zero
  // and the real number of entries in the section header table is held in
  //  the sh_size number of the initial entry in section header table.
  //
  // To handle this, we will rewrite the real e_shnum to ehdr
  if (ehdr.e_shnum == 0) {
    Elf64_Shdr shdr = *(Elf64_Shdr *)(fbuf->data() + ehdr.e_shoff);
    ehdr.e_shnum = shdr.sh_size;
  }

  ELF->set_ehdr(ehdr);
}

void Parser::parseELFSectionHeader() {
  Elf64_Ehdr ehdr = ELF->get_ehdr();
  size_t shnum = ELF->get_ehdr().e_shnum;

  for (int i = 1; i != shnum; ++i) {
    Elf64_Shdr *shdr_begin = (Elf64_Shdr *)(fbuf->data() + ehdr.e_shoff);
    Elf64_Shdr shdr = *(Elf64_Shdr *)(shdr_begin + i);
    ELF->get_shdr()->push_back(shdr);
  }
}

void Parser::Parse() {
  parseELFHeader();
  parseELFSectionHeader();
}

} // namespace Linker
