#include <stdio.h>
#include <string.h>
#include "readfile.h"

#define FILE_PATH "Scripts.txt"
#define INPUT_LEN 100
#define NAME_LEN 30
#define MAX_ARR_SIZE 1000
#define ARR_SIZE 300

typedef struct script {
  int start;
  int end;
  char name[NAME_LEN];
} SCRIPT_T;

void readfile(){

    FILE *fp;
    char line[INPUT_LEN];
    char script_name[NAME_LEN];

    SCRIPT_T all_scripts[MAX_ARR_SIZE];

    int start, end;
    //int prev;
    int i = 0, j = 0;
    int count = 0, count2 = 0;
    SCRIPT_T *prev_script;

    SCRIPT_T *script;

    if ((fp = fopen(FILE_PATH, "r")) != NULL){
        printf("Success\n");
        while(fgets(line, INPUT_LEN, fp) != NULL){
            if (readline(line, &start, &end, script_name)){
              continue;
            }

            // if (prev_script != NULL && (prev_script->end == start - 1) && !strcmp(prev_script->name, script_name)){
            //   prev_script->end = end;
            // }
            // else{
            //   //printf("test\n");
            //   all_scripts[i].start = start;
            //   all_scripts[i].end = end;
            //   strcpy(all_scripts[i].name, script_name);
            //   prev_script = &(all_scripts[i++]);
            // }

            //prev = end;

            //printf("Script: %s\tStart =  %d\tEnd = %d\ti=%d\n", script_name, start, end, i);
        }
    }

    // prev_script = NULL;
    //
    // for (j = 0; j < i; j++){
    //   script = &all_scripts[j];
    //   printf("Script: %30s\tStart = %X\tEnd = %X\tNo. = %d\n", script->name, script->start, script->end, j);
    //   if (script->start == script->end){
    //     count++;
    //   }
    //   if (prev_script != NULL && (strcmp(prev_script->name, script->name))){
    //     count2++;
    //   }
    //   prev_script = script;
    // }
    //
    // printf("Single Codepoint Count = %d\n", count);
    // printf("Scripts Count = %d\n", count2);

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
