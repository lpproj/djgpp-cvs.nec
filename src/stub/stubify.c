/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#ifdef __DJGPP__
#include <io.h>
#endif

#ifndef O_BINARY
#define O_BINARY 0
#endif

unsigned char stub_bytes[] = {
#include "stub.h"
};

#define v_printf if(verbose)printf
int verbose=0;

unsigned long
get32(unsigned char *ptr)
{
  return ptr[0] | (ptr[1]<<8) | (ptr[2]<<16) | (ptr[3]<<24);
}

unsigned short
get16(unsigned char *ptr)
{
  return ptr[0] | (ptr[1]<<8);
}

void coff2exe(char *fname)
{
  char ifilename[256];
  char ofilename[256];
  int ifile;
  int ofile;
  char *ofname, *ofext;
  char buf[4096];
  int rbytes, used_temp, i, n;
  long coffset=0;
  unsigned char filehdr_buf[20];
  int max_file_size = 0;
  int coff_file_size = 0;
  int drop_last_four_bytes = 0;

  strcpy(ifilename, fname);
  strcpy(ofilename, fname);
  ofext = 0;
  for (ofname=ofilename; *ofname; ofname++)
  {
    if (strchr("/\\:", *ofname))
      ofext = 0;
    if (*ofname == '.')
      ofext = ofname;
  }
  if (ofext == 0)
    ofext = ofilename + strlen(ofilename);
  strcpy(ofext, ".exe");
  if (access(ofilename, 0) == 0)
    for (ofile=0; ofile<999; ofile++)
    {
      used_temp = 1;
      sprintf(ofext, ".%03d", ofile);
      if (access(ofilename, 0))
	break;
    }
  else
    used_temp = 0;

  ifile = open(ifilename, O_RDONLY|O_BINARY);
  if (ifile < 0)
  {
    perror(fname);
    return;
  }
  while (1)
  {
    lseek(ifile, coffset, 0);
    read(ifile, buf, 6);
    if (buf[0] == 'M' && buf[1] == 'Z') /* stubbed already, skip stub */
    {
      int blocks = (unsigned char)buf[4] + (unsigned char)buf[5] * 256;
      int partial = (unsigned char)buf[2] + (unsigned char)buf[3] * 256;
      coffset += blocks * 512;
      if (partial)
	coffset += partial - 512;
    }
    else if (buf[0] == 0x4c && buf[1] == 0x01) /* it's a COFF */
    {
      break;
    }
    else
    {
      fprintf(stderr, "Warning: input file is not COFF or stubbed COFF\n");
      break;
    }
  }

  coff_file_size = lseek(ifile, 0, SEEK_END) - coffset;
  lseek(ifile, coffset, 0);

  read(ifile, filehdr_buf, 20); /* get the COFF header */
  lseek(ifile, get16(filehdr_buf+16), SEEK_CUR); /* skip optional header */
  n = get16(filehdr_buf + 2);
  for (i=0; i<n; i++) /* for each COFF section */
  {
    int addr, size, flags;
    unsigned char coffsec_buf[40];
    read(ifile, coffsec_buf, 40);
    size = get32(coffsec_buf+16);
    addr = get32(coffsec_buf+20);
    flags = get32(coffsec_buf+36);
    if (flags & 0x60) /* text or data */
    {
      int maybe_file_size = size + addr;
      if (max_file_size < maybe_file_size)
	max_file_size = maybe_file_size;
    }
  }
  if (coff_file_size == max_file_size + 4)
    /* it was built with "gcc -s" and has four too many bytes */
    drop_last_four_bytes = 1;

  lseek(ifile, coffset, 0);

  ofile = open(ofilename, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY, 0666);
  if (ofile < 0)
  {
    perror(ofname);
    return;
  }
  v_printf("stubify: %s -> %s", ifilename, ofilename);
  if (used_temp)
  {
    strcpy(ifilename, ofilename);
    strcpy(ofext, ".exe");
    v_printf(" -> %s", ofilename);
  }
  v_printf("\n");

  write(ofile, stub_bytes, sizeof(stub_bytes));
  
  while ((rbytes=read(ifile, buf, 4096)) > 0)
  {
    int wb;

    if (drop_last_four_bytes && rbytes < 4096)
      rbytes -= 4;

    wb = write(ofile, buf, rbytes);
    if (wb < 0)
    {
      perror(ofname);
      unlink(ofilename);
      close(ifile);
      close(ofile);
      exit(1);
    }
    if (wb < rbytes)
    {
      fprintf(stderr, "%s: disk full\n", ofname);
      unlink(ofilename);
      close(ifile);
      close(ofile);
      exit(1);
    }
  }

  close(ifile);
  close(ofile);

  if (used_temp)
  {
    unlink(ofilename);
    if (rename(ifilename, ofilename))
    {
      printf("rename of %s to %s failed.\n", ifilename, ofilename);
      perror("The error was");
    }
  }
}

int main(int argc, char **argv)
{
  int i;
  if (argc > 1 && strcmp(argv[1], "-v")==0)
  {
    verbose = 1;
    argv++;
    argc--;
  }
  v_printf("stubify for djgpp V2.X executables, Copyright (C) 1995 DJ Delorie\n");
  if (argc < 2)
  {
    fprintf(stderr, "Usage: stubify [-g] <program>  (program may be COFF or stubbed .exe,\n");
    fprintf(stderr, "  and may be COFF with .exe extension.  Resulting file will have .exe)\n");

    fprintf(stderr, "\nThis program is NOT shareware or public domain.  It is copyrighted.\n");
    fprintf(stderr, "It is redistributable but only as part of a complete package.  If you\n");
    fprintf(stderr, "have a copy of this program, the place that you got it from is\n");
    fprintf(stderr, "responsible for making sure you are able to get it's sources as well.\n");

    exit(1);
  }
  if (argc > 2 && strcmp(argv[1], "-g") == 0)
  {
    char ofilename[256], *ofname, *ofext=0;
    int ofile;

    strcpy(ofilename, argv[2]);
    for (ofname=ofilename; *ofname; ofname++)
    {
      if (strchr("/\\:", *ofname))
	ofext = 0;
      if (*ofname == '.')
	ofext = ofname;
    }
    if (ofext == 0)
      ofext = ofilename + strlen(ofilename);
    strcpy(ofext, ".exe");
    
    ofile = open(ofilename, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY, 0666);
    if (ofile < 0)
    {
      printf("Cannot open output file to generate\n");
      perror(ofilename);
      return;
    }
    v_printf("stubify: generate %s\n", argv[2]);

    write(ofile, stub_bytes, sizeof(stub_bytes));
    close(ofile);
  }
  else
    for (i=1; i<argc; i++)
      coff2exe(argv[i]);
  return 0;
}

