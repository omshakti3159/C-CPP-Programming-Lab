#include <stdio.h>
#include <string.h>
#include "readfile.h"
#include "scripts.h"
#include "global.h"

void readfile(const char* fpath){

    FILE *fp;
    char line[INPUT_LEN];
    char script_name[NAME_LEN];

    SCRIPT_T all_scripts[ARR_SIZE];
    initialize_all_scripts((SCRIPT_T *)&all_scripts, ARR_SIZE);

    int start, end;
    int size = 0;

    if ((fp = fopen(fpath, "r")) != NULL){
        printf("\"%s\" successfully opened!\n", fpath);
        while(fgets(line, INPUT_LEN, fp) != NULL){
            if (readline(line, &start, &end, script_name)){
              continue;
            }
            //printf("%s\n", line);
            size = add_range((SCRIPT_T *)all_scripts, script_name, start, end, size);

        }
    }

    printf("Array size = %d\n", size);

    SCRIPT_T *script;
    int i = 0, j = 0;
    for (i = 0; i < size; i++){
      script = &all_scripts[i];
      printf("Script: %s\n", script->name);
      for (j = 0; j < script->length; j++){
        printf("No. %3d\tStart: %X\tEnd: %X\n", j, *(script->start + j), *(script->end + j));
      }
    }

    unsigned int a;
    char stop = 0;
    printf("Please enter a codepoint: ");
    scanf("%X", &a);

    for (i = 0; i < size; i++){
      script = &all_scripts[i];
      //printf("Script: %s\n", script->name);
      for (j = 0; j < script->length; j++){
        if ((a >= *(script->start + j)) && a <= *(script->end + j)){
          printf("Script Recognized: %s\n", script->name);
          stop = 1;
          break;
        }
      }
      if (stop){
        break;
      }
    }

}

int readline(char * input, int * start, int * end, char * script_name){
    if (3 != sscanf(input, "%x..%x    ; %s ", start, end, script_name)){
        if (2 == sscanf(input, "%x          ; %s ", start, script_name)){
            *end = *start;
        }
        else{
            return 1;
        }
    }
    //printf("%s\n", input);
    return 0;
}
