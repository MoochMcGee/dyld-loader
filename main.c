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
   FILE *file = fopen(filename, "rb");
   if(!file) /* sanity */
   {
      printf("unable to open %s\n", filename);
      exit(0);
   }
   uint32_t magic = getMagic(file, 0);
   printf("file magic is: %"PRIu32"\n");
   ///list_seg(file);
   fclose(file);
   return(0);
}
