#include "Linker/Parser.h"
#include "utils/Debug.h"

#include <iostream>

namespace Linker {

Elf64_Shdr *Parser::getRawShdrFromIdx(const std::size_t idx) {
  return (Elf64_Shdr *)(fbuf->data() + ELF->getEhdr().e_shoff +
                        (ELF->getEhdr().e_shentsize * idx));
}

char *Parser::getRawBytesFromShdrOffset(Elf64_Shdr &s) {
  return fbuf->data() + s.sh_offset;
}

const char *Parser::getRawBytesFromShdrIdx(const std::size_t idx) {
  Elf64_Shdr *Shdr = getRawShdrFromIdx(idx);
  return getRawBytesFromShdrOffset(*Shdr);
}

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

  ELF->setEhdr(ehdr);
}

void Parser::parseELFSectionHeader() {
  Elf64_Ehdr ehdr = ELF->getEhdr();
  size_t shnum = ELF->getEhdr().e_shnum;

  // Get string table index
  // If the section name string table section index is greater than
  //  or equal to SHN_LORESERVE, this member has the value SHN_XINDEX
  //  and the actual index of the section name string table sectoin is
  //  contained in the sh_link field of the section header at index 0.
  size_t shstrndx = ehdr.e_shstrndx;
  // if (shstrndx == SHN_XINDEX) {
  //   shstrndx = ELF->get_shdr()->at(0).sh_link;
  // }
  ehdr.e_shstrndx = shstrndx;

  const char *StringTable = getRawBytesFromShdrIdx(ehdr.e_shstrndx);

  for (int i = 1; i != shnum; ++i) {
    Elf64_Shdr *shdr = getRawShdrFromIdx(i);
    std::string name(StringTable + shdr->sh_name);

    ELF->setShdr(*shdr, name);
    std::cout << name << std::endl;
  }
}

void Parser::parseElfSymTab() {
  Elf64_Shdr *SymTabShdr = ELF->findSection(SHT_SYMTAB);
  if (SymTabShdr != nullptr) {
    // A symbol table section's sh_info section header member holds
    // the symbol table index for the first non-local symbol.
    std::cout << SymTabShdr->sh_info << std::endl;

    size_t num = SymTabShdr->sh_size / SymTabShdr->sh_entsize;
    std::cout << "Symbol table number: " << num << std::endl;

    // Fill up symtab
    // Get symtab and symbol string
    Elf64_Sym *SymTab = (Elf64_Sym *)getRawBytesFromShdrOffset(*SymTabShdr);
    const char *StringTable = getRawBytesFromShdrIdx(SymTabShdr->sh_link);

    for (int i = 0; i < num; ++i) {
      std::string name(StringTable + SymTab[i].st_name);
      ELF->setSymTab(SymTab[i], name);
      std::cout << name << std::endl;
    }
  }
}

void Parser::Parse() {
  parseELFHeader();
  parseELFSectionHeader();
  parseElfSymTab();
}

} // namespace Linker
