#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "scripts.h"
#include "utf8.h"

int* initialize_count(int size){
  int i;
  int* count = (int *) malloc(size * sizeof(int));
  for (i = 0; i < size; i++){
    *(count + i) = 0;
  }
  return count;
}

void read_and_count(SCRIPT_T *all_scripts, int *count, int size){
  char line[FILE_SIZE];
  unsigned char *p;
  int bytes_in_char;
  unsigned int codepoint;

  while (fgets(line, FILE_SIZE, stdin) != NULL){
    p = (unsigned char *)line;
    while (*p){
      codepoint = utf8_to_codepoint(p, &bytes_in_char);
      if (codepoint){
        (*(count + find_script(all_scripts, size, codepoint)))++;
         _utf8_incr(p);
      }
      else{
        p++;
      }
    }
  }
}

void print_max_count(SCRIPT_T *all_scripts, int *count, int size){
  int i = 0;
  int max_cnt = 0;
  int max_index = -1;
  for (i = 0; i < size; i++){
    if (*(count + i) > max_cnt){
      max_cnt = *(count + i);
      max_index = i;
    }
  }

  if (max_index == -1){
    printf("No script is found in the file! Please check your file!\n");
    return;
  }

  printf("Script: %s\t\tCount: %d\n", (all_scripts + max_index)->name, max_cnt);

}
