#include <stdio.h>
#include <string.h>
#include "loadscripts.h"
#include "scripts.h"
#include "global.h"

int loadscripts(const char* fpath, SCRIPT_T *all_scripts){

    FILE *fp;
    char line[INPUT_LEN];
    char script_name[NAME_LEN];
    int start, end;
    int size = 0;

    //SCRIPT_T all_scripts[ARR_SIZE];
    initialize_all_scripts(all_scripts, ARR_SIZE);

    if ((fp = fopen(fpath, "r")) != NULL){
        printf("\"%s\" successfully opened!\n", fpath);
        while(fgets(line, INPUT_LEN, fp) != NULL){
            if (readline(line, &start, &end, script_name)){
              continue;
            }
            //printf("%s\n", line);
            size = add_range(all_scripts, script_name, start, end, size);
        }
    }

    return size;
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
