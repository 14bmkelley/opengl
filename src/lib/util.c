#include "util.h"

#include <stdio.h>
#include <stdlib.h>

char *convertFileToBuffer(char *file) {
  
  FILE *fptr; // File pointer
  long flen;  // File length
  char *fbuf; // File character buffer
  
  // Open file and check for failure
  fptr = fopen(file, "rb");
  if (!fptr) return NULL;
  
  // Determine length of file
  fseek(fptr, 0, SEEK_END);
  flen = ftell(fptr);
  
  // Allocate a buffer to file size with \0
  fbuf = (char *) malloc(flen + 1);
  
  // Read in file, saving contents to buffer
  fseek(fptr, 0, SEEK_SET);
  fread(fbuf, flen, 1, fptr);
  fclose(fptr);
  
  // Add terminator and return char buffer
  fbuf[flen] = 0;
  return fbuf;
  
}
