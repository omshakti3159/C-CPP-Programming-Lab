#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scripts.h"

int add_range(SCRIPT_T *all_scripts, char *name, int start, int end, int size){
  if (size != 0){
    SCRIPT_T *prev_script = all_scripts + size - 1;
    if (!strcmp(prev_script->name, name)){
      add_range_to_script(prev_script, start, end);
      return size;
    }
  }
  strcpy((all_scripts + size)->name, name);
  add_range_to_script(all_scripts + size, start, end);

  return size + 1;

}

void add_range_to_script(SCRIPT_T *script, int start, int end){
  int length = script->length;
  if (length + 1 > script->maxlength){
    script->start = (int *)realloc(script->start, (script->maxlength + STEP_SIZE) * sizeof(int));
    script->end = (int *)realloc(script->end, (script->maxlength + STEP_SIZE) * sizeof(int));
    script->maxlength += STEP_SIZE;
  }
  if (length == 0){
    *(script->start) = start;
    *(script->end) = end;
    script->length++;
  }
  else{
    if (*(script->end + length - 1) == start - 1){
      *(script->end + length - 1) = end;
    }
    else{
      *(script->start + length) = start;
      *(script->end + length) = end;
      script->length++;
    }
  }
}

void initialize_all_scripts(SCRIPT_T *all_scripts, int max_size){
  int i = 0;
  for (i = 0; i < max_size; i++){
    (all_scripts + i)->length = 0;
    (all_scripts + i)->maxlength = 1;
    (all_scripts + i)->start = (int *)malloc(sizeof(int));
    (all_scripts + i)->end = (int *)malloc(sizeof(int));
    *((all_scripts + i)->start) = 0;
    *((all_scripts + i)->end) = 0;
  }
}

void print_all_scripts(SCRIPT_T *all_scripts, int size){
  SCRIPT_T *script;
  int i = 0, j = 0;
  for (i = 0; i < size; i++){
    script = all_scripts + i;
    printf("Script: %s\n", script->name);
    for (j = 0; j < script->length; j++){
      printf("No. %3d\tStart: %X\tEnd: %X\n", j, *(script->start + j), *(script->end + j));
    }
  }

  printf("Array size = %d\n", size);

}

int find_script(SCRIPT_T *all_scripts, int size){
  int i, j;
  unsigned int a;
  SCRIPT_T *script;

  printf("Please enter a codepoint: ");
  scanf("%X", &a);

  for (i = 0; i < size; i++){
    script = all_scripts + i;
    //printf("Script: %s\n", script->name);
    for (j = 0; j < script->length; j++){
      if ((a >= *(script->start + j)) && a <= *(script->end + j)){
        printf("Script Recognized: %s\n", script->name);
        return i;
      }
    }
  }
  return -1;
}
