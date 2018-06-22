#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "centralfiction.h"
#include "reality.h"

int getMagic(FILE *file, int offset)
{
   /* read first 4 bytes as hex */
   char magic[4]; 
   int x;
   x = fread(&magic, sizeof(char), 4, file);
   return x;
}

int can_we_haz_64(uint32_t magic)
{
   return magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
}

int can_we_haz_byteswap(uint32_t magic)
{
  return magic == MH_CIGAM || magic == MH_CIGAM_64;
}

int dump_seg(const char *filename, FILE *file, uint32_t magic)
{
   int are_we_64b = can_we_haz_64(magic);
   if(are_we_64b == 1)
   {
      printf("%s is a 64 bit binary!\n", filename);
   }
   else if(are_we_64b == 0)
   {
      printf("%s is a 32 bit binary!\n", filename);
   }
   else
   {
      printf("%s is *probably* a fat binary!\n", filename);
   }
   int do_we_need_swap = can_we_haz_byteswap(magic);
}
