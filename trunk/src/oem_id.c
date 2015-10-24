/******************************************************************
    Copyright (C) 2015  Henrik Carlqvist

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
******************************************************************/
#include <stdio.h>

#include "file.h"
#include "oem_id.h"

char *read_oem_id(FILE *fp)
{
   static char szOemId[9];
   int i;

   szOemId[8] = 0;
   if(!read_data(fp, 3, szOemId, 8))
      return NULL;
   /* sanity check */
   for(i=0; i<8; i++)
      if(szOemId[i] < ' ')
	 return NULL;
   return szOemId;
} /* read_oem_id */

int write_oem_id(FILE *fp, const char *szOemId)
{
   static char acOemId[8];
   int i;

   for(i=0; (i<8) && szOemId[i]; i++)
      acOemId[i] = szOemId[i];
   while(i<8)
      acOemId[i++] = ' ';
   return write_data(fp, 3, acOemId, 8);
} /* write_eom_id */
