#ifndef OEM_ID_H
#define OEM_ID_H

/* Returns zero terminated string with OEM ID or NULL at failure */
char *read_oem_id(FILE *fp);

/* Writes OEM ID to file system */
int write_oem_id(FILE *fp, const char *szOemId);

#endif
