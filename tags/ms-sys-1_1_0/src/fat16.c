#include <stdio.h>

#include "file.h"
#include "fat16.h"

int is_fat_16_fs(FILE *fp)
{
   char *szMagic = "FAT16   ";

   return contains_data(fp, 0x36, szMagic, strlen(szMagic));
} /* is_fat_16_fs */

int is_fat_16_br(FILE *fp)
{
   /* A "file" is probably some kind of FAT16 boot record if it contains the
      magic chars 0x55, 0xAA at positions 0x1FE */
   unsigned char aucRef[] = {0x55, 0xAA};
   unsigned char aucMagic[] = {'M','S','W','I','N','4','.','1'};

   if( ! contains_data(fp, 0x1FE, aucRef, sizeof(aucRef)))
      return 0;
   if( ! contains_data(fp, 0x03, aucMagic, sizeof(aucMagic)))
      return 0;
   return 1;
} /* is_fat_16_br */

int entire_fat_16_br_matches(FILE *fp)
{
   #include "br_fat16_0x0.h"
   #include "br_fat16_0x3e.h"

   return
      ( contains_data(fp, 0x0, br_fat16_0x0, sizeof(br_fat16_0x0)) &&
	/* BIOS Parameter Block might differ between systems */
	contains_data(fp, 0x3e, br_fat16_0x3e, sizeof(br_fat16_0x3e)) );
} /* entire_fat_16_br_matches */

int write_fat_16_br(FILE *fp)
{
   #include "br_fat16_0x0.h"
   #include "br_fat16_0x3e.h"

   return
      ( write_data(fp, 0x0, br_fat16_0x0, sizeof(br_fat16_0x0)) &&
	/* BIOS Parameter Block should not be overwritten */
	write_data(fp, 0x3e, br_fat16_0x3e, sizeof(br_fat16_0x3e)) );
} /* write_fat_16_br */
