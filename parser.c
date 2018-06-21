#include <stdio.h>
#include <stdint.h>

typedef int	cpu_type_t;
typedef int	cpu_subtype_t;
typedef int	vm_prot_t;

struct mach_header {
   uint32_t      magic;
   cpu_type_t    cputype;
   cpu_subtype_t cpusubtype;
   uint32_t      filetype;
   uint32_t      ncmds;
   uint32_t      sizeofcmds;
   uint32_t      flags;
};

struct segment_command {
   uint32_t  cmd;
   uint32_t  cmdsize;
   char      segname[16];
   uint32_t  vmaddr;
   uint32_t  vmsize;
   uint32_t  fileoff;
   uint32_t  filesize;
   vm_prot_t maxprot;
   vm_prot_t initprot;
   uint32_t  nsects;
   uint32_t  flags;
};

int getMagic(FILE *file, int offset)
{
   uint32_t magic; /* is this even correct? */
   fseek(file, offset, SEEK_SET);
   fread(&magic, sizeof(uint32_t), 1, file);
   return magic;
}

int dump_seg(FILE *file, uint32_t magic)
{
   printf("lol\n");
}
