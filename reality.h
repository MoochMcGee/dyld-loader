#ifndef YR_H
#define YR_H

#include <stdbool.h>
#include "centralfiction.h"

/* parser.c */
static const void *i_can_haz_read(macho_t *input, const void *addr, size_t len);
static const void *i_can_haz_offset(macho_t *input, const void *addr, size_t offset, size_t len);
char *i_can_haz_version(uint32_t ver);
bool the_fun_part(macho_t *input);

#endif /* YR_H */