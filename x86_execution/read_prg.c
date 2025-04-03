#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <capstone/capstone.h>
#include <elf.h>

void disassemble_text_section(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("fstat");
        close(fd);
        return;
    }

    void *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return;
    }

    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
    Elf64_Shdr *shdr = (Elf64_Shdr *)(map + ehdr->e_shoff);
    const char *shstrtab = (const char *)(map + shdr[ehdr->e_shstrndx].sh_offset);

    for (int i = 0; i < ehdr->e_shnum; i++) {
        if (strcmp(&shstrtab[shdr[i].sh_name], ".text") == 0) {
            uint8_t *code = (uint8_t *)(map + shdr[i].sh_offset);
            size_t size = shdr[i].sh_size;
            uint64_t address = shdr[i].sh_addr;

            csh handle;
            cs_insn *insn;
            size_t count;

            if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
                fprintf(stderr, "Failed to initialize Capstone.\n");
                break;
            }

            count = cs_disasm(handle, code, size, address, 0, &insn);
            if (count > 0) {
                for (size_t j = 0; j < count; j++) {
                    printf("    %lx:\t%s\t%s\n", insn[j].address, insn[j].mnemonic, insn[j].op_str);
                }
                cs_free(insn, count);
            } else {
                fprintf(stderr, "Disassembly failed.\n");
            }

            cs_close(&handle);
            break;
        }
    }

    munmap(map, st.st_size);
    close(fd);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <ELF binary>\n", argv[0]);
        return 1;
    }
    disassemble_text_section(argv[1]);
    return 0;
}
