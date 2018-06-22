#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>

#include "centralfiction.h"
#include "reality.h"

static uint32_t swap32(uint32_t input)
{
   return OSSwapInt32(input);
}

static uint32_t nswap32(uint32_t input)
{
   return input;
}

static const void *i_can_haz_read(macho_t *input, const void *addr, size_t len)
{
   if((((uint8_t *)addr) - ((uint8_t *)input->file)) + len > input->len) 
   {
      printf("macho seems incomplete?!\n"); /* probably malformed */
   }
   return addr;
}

static const void *i_can_haz_offset(macho_t *input, const void *addr, size_t offset, size_t len)
{
   void *end = ((uint8_t *) addr) + offset;
   return i_can_haz_read(input, end, len);
}

char *i_can_haz_version(uint32_t ver)
{
   char *end;
   printf(&end, "%"PRIu32".%"PRIu32".%"PRIu32, (ver >> 16) & 0xFF, (ver >> 8) & 0xFF, ver & 0xFF); /* hey it's me */
   return end;
}

bool the_fun_part(macho_t *input)
{
   const uint32_t *magic = i_can_haz_read(input, input->file, sizeof(uint32_t));
   if (magic == NULL)
   {
      printf("no magic found?!\n");
   }
   bool macho_is_64 = false;
   bool macho_needs_a_workout = false; /* fat, get it? */
   uint32_t (*swap32)(uint32_t) = nswap32;
   size_t header_size;
   const struct mach_header *header;
   const struct mach_header_64 *header64;
   const struct fat_header *fat_header;
   switch(*magic) {
      case MH_CIGAM:
         printf("this is an arm mach-o [little endian]\n");
         swap32 = swap32;
      case MH_MAGIC:
         header_size = sizeof(*header);
         header = i_can_haz_read(input, input->file, header_size);
         if (header == NULL) {
            printf("no header?!\n");
         }
         printf("32 bit mach-o file\n");
         break;
      case MH_CIGAM_64:
            printf("this is an arm mach-o [little endian]\n");
            swap32 = swap32;
      case MH_MAGIC_64:
         header_size = sizeof(*header64);
         header64 = i_can_haz_read(input, input->file, sizeof(*header64));
         if (header64 == NULL)
         {
            printf("no header?!\n");
         }
         header = (struct mach_header *) header64;
         printf("64 bit mach-o file\n");
         macho_is_64 = true;
         break;
      case FAT_CIGAM:
      /* todo: implement */
      case FAT_MAGIC:
         fat_header = i_can_haz_read(input, input->file, sizeof(*fat_header));
         macho_needs_a_workout = true;
         printf("universal mach-o file\n");
         break;
      default:
            printf("unknown magic: 0x%" PRIx32 "", *magic);
   }

   if (macho_needs_a_workout)
   {
      uint32_t nfat = OSSwapBigToHostInt32(fat_header->nfat_arch);
      const struct fat_arch *archs = i_can_haz_offset(input, fat_header, sizeof(struct fat_header), sizeof(struct fat_arch));
      if (archs == NULL)
      {
         printf("no arch-s?!\n");
      }
      printf("arch count: %" PRIu32 "\n", nfat);
      for (uint32_t i = 0; i < nfat; i++)
      {
         const struct fat_arch *arch = i_can_haz_read(input, archs + i, sizeof(struct fat_arch));
         if (arch == NULL)
         {
            return false;
         }
         macho_t arch_input;
         arch_input.len = OSSwapBigToHostInt32(arch->size);
         arch_input.file = i_can_haz_offset(input, input->file, OSSwapBigToHostInt32(arch->offset), arch_input.len);
         if (arch_input.file == NULL)
         {
            return false;
         }
         printf("\n"); /* newline bestline */
         if (!the_fun_part(&arch_input))
         {
            return false;
         }
      }
         return true;
    }
    return true;
}