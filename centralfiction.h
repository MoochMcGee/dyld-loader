#ifndef CF_H
#define CF_H

#include <stdint.h> /* god has left the chat */
#include <stddef.h> /* jesus has left the chat */

#define	MH_MAGIC	0xfeedface	/* the mach magic number */
#define MH_CIGAM	0xcefaedfe	/* NXSwapInt(MH_MAGIC) */
#define MH_MAGIC_64 0xfeedfacf /* the 64-bit mach magic number */
#define MH_CIGAM_64 0xcffaedfe /* NXSwapInt(MH_MAGIC_64) */
#define FAT_MAGIC	0xcafebabe
#define FAT_CIGAM   0xbebafeca
/* bad */
#define MH_MAGIC_NH feedface
#define MH_MAGIC_64_NH feedfacf
#define MH_MAGIC_FLIP_NH cefaedfe
#define MH_MAGIC_FLIP_64_NH cffaedfe
#define MH_MAGIC_FAT_NH cafebabe
#define MH_MAGIC_FLIP_FAT_NH bebafeca

/* anxiety [.../.../.../high F#] */
typedef int	cpu_type_t;
typedef int	cpu_subtype_t;
typedef int	vm_prot_t;

#define OSSwapConstInt32(x) \
    ((uint32_t)((((uint32_t)(x) & 0xff000000) >> 24) | \
                (((uint32_t)(x) & 0x00ff0000) >>  8) | \
                (((uint32_t)(x) & 0x0000ff00) <<  8) | \
                (((uint32_t)(x) & 0x000000ff) << 24)))

#define OSSwapConstInt32(x) \
    ((uint32_t)((((uint32_t)(x) & 0xff000000) >> 24) | \
                (((uint32_t)(x) & 0x00ff0000) >>  8) | \
                (((uint32_t)(x) & 0x0000ff00) <<  8) | \
                (((uint32_t)(x) & 0x000000ff) << 24)))

#define OSSwapConstInt64(x) \
    ((uint64_t)((((uint64_t)(x) & 0xff00000000000000ULL) >> 56) | \
                (((uint64_t)(x) & 0x00ff000000000000ULL) >> 40) | \
                (((uint64_t)(x) & 0x0000ff0000000000ULL) >> 24) | \
                (((uint64_t)(x) & 0x000000ff00000000ULL) >>  8) | \
                (((uint64_t)(x) & 0x00000000ff000000ULL) <<  8) | \
                (((uint64_t)(x) & 0x0000000000ff0000ULL) << 24) | \
                (((uint64_t)(x) & 0x000000000000ff00ULL) << 40) | \
                (((uint64_t)(x) & 0x00000000000000ffULL) << 56)))

#define OSSwapInt16(x) OSSwapConstInt16(x)

#define OSSwapInt32(x) OSSwapConstInt32(x)

#define OSSwapInt64(x) OSSwapConstInt64(x)

#define OSSwapBigToHostInt32(x) ((uint32_t)(x))

struct mach_header {
   uint32_t	magic;		/* mach magic number identifier */
   cpu_type_t	cputype;	/* cpu specifier */
   cpu_subtype_t	cpusubtype;	/* machine specifier */
   uint32_t	filetype;	/* type of file */
   uint32_t	ncmds;		/* number of load commands */
   uint32_t	sizeofcmds;	/* the size of all the load commands */
   uint32_t	flags;		/* flags */
};

struct mach_header_64 {
   uint32_t	magic;		/* mach magic number identifier */
   cpu_type_t	cputype;	/* cpu specifier */
   cpu_subtype_t	cpusubtype;	/* machine specifier */
   uint32_t	filetype;	/* type of file */
   uint32_t	ncmds;		/* number of load commands */
   uint32_t	sizeofcmds;	/* the size of all the load commands */
   uint32_t	flags;		/* flags */
   uint32_t	reserved;	/* reserved */
};

struct load_command {
   uint32_t cmd;		/* type of load command */
   uint32_t cmdsize;	/* total size of command in bytes */
};

struct segment_command { /* for 32-bit architectures */
   uint32_t	cmd;		/* LC_SEGMENT */
   uint32_t	cmdsize;	/* includes sizeof section structs */
   char		segname[16];	/* segment name */
   uint32_t	vmaddr;		/* memory address of this segment */
   uint32_t	vmsize;		/* memory size of this segment */
   uint32_t	fileoff;	/* file offset of this segment */
   uint32_t	filesize;	/* amount to map from the file */
   vm_prot_t	maxprot;	/* maximum VM protection */
   vm_prot_t	initprot;	/* initial VM protection */
   uint32_t	nsects;		/* number of sections in segment */
   uint32_t	flags;		/* flags */
};

struct segment_command_64 { /* for 64-bit architectures */
   uint32_t	cmd;		/* LC_SEGMENT_64 */
   uint32_t	cmdsize;	/* includes sizeof section_64 structs */
   char		segname[16];	/* segment name */
   uint64_t	vmaddr;		/* memory address of this segment */
   uint64_t	vmsize;		/* memory size of this segment */
   uint64_t	fileoff;	/* file offset of this segment */
   uint64_t	filesize;	/* amount to map from the file */
   vm_prot_t	maxprot;	/* maximum VM protection */
   vm_prot_t	initprot;	/* initial VM protection */
   uint32_t	nsects;		/* number of sections in segment */
   uint32_t	flags;		/* flags */
};

struct fat_header {
   unsigned long	magic;		/* FAT_MAGIC */
   unsigned long	nfat_arch;	/* number of structs that follow */
};

struct fat_arch {
   cpu_type_t	cputype;	/* cpu specifier (int) */
   cpu_subtype_t	cpusubtype;	/* machine specifier (int) */
   unsigned long	offset;		/* file offset to this object file */
   unsigned long	size;		/* size of this object file */
   unsigned long	align;		/* alignment as a power of 2 */
};

typedef struct macho {
   const void *file;
   size_t len;
} macho_t;

#endif /* CF_H */