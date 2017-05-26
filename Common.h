#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

struct MyFile {
  char const *filename;
  FILE *f;
  MyFile(char const *filename);
  void read(void *buf, size_t cnt);
  void seek(size_t pos);
  ~MyFile();
};
void fail(char *str);
void quit( int code );
#endif
