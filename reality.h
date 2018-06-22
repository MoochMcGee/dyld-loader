#ifndef YR_H
#define YR_H

int getMagic(FILE *file, int offset);
int can_we_haz_64(uint32_t magic);
int can_we_haz_byteswap(uint32_t magic);
int dump_seg(const char *filename, FILE *file, uint32_t magic);

unsigned char* hexstr_to_char(const char* hexstr);
int byteArrayToHexString(uint8_t *byte_array, int byte_array_len, char *hexstr, int hexstr_len);

#endif /* YR_H */