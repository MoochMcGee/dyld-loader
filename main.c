/*
* honestly i have no clue what this is gonna be lmao
* but hey, i'm bored
* and it's summer, so why the fuck not?
* wen eta hypervisor for xnu
*/

//sorry if the spacing is fuck-y i'm using nano lul

#define version "0.1 Beta"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "reality.h"
#include "centralfiction.h"

int main(int argc, char *argv[])
{
   printf("dyld-loader\n");
   printf("version: %s\nBuild on %s at %s\n", version, __DATE__, __TIME__); //compiler macros still exist right
   if(argc != 2)
   {
      printf("usage: %s <mach-o>\n", argv[0]);
      exit(0);
   }
   const char *filename = argv[1];
   int f = open(filename, O_RDONLY);
   if(f < 0)
   {
      printf("unable to open %s", filename);
      exit(0);
   }
   struct stat stbuf;
   if(fstat(f, &stbuf) != 0)
   {
      printf("fstat err\n");
   }
   void *stuff = mmap(NULL, stbuf.st_size, PROT_READ, MAP_FILE|MAP_PRIVATE, f, 0);
   if(stuff == MAP_FAILED)
   {
      printf("lol wtf mmap died\n");
      exit(0);
   }
   macho_t input_file;
   input_file.file = stuff;
   input_file.len = stbuf.st_size;
   printf("parsing: %s\n", filename);
   if (!the_fun_part(&input_file)) {
      printf("failed to parse %s", filename);
   }
   munmap(stuff, stbuf.st_size);
   close(f);
   return(0);
}