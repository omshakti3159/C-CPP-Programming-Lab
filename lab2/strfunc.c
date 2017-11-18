#include "func.h"

void stolower(char *src, char *dst){
  while(*src){
    *dst = tolower(*src);
    dst++;
    src++;
  }
}
