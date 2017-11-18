#include <stdio.h>
#include <string.h>
#include "readfile.h"
#include "scripts.h"

#define FILE_PATH "Scripts.txt"
#define INPUT_LEN 100
#define NAME_LEN 30



void readfile(){

    FILE *fp;
    char line[INPUT_LEN];
    char script_name[NAME_LEN];

    SCRIPT_T all_scripts[ARR_SIZE];
    initialize_all_scripts((SCRIPT_T *)&all_scripts, ARR_SIZE);

    int start, end;

    if ((fp = fopen(FILE_PATH, "r")) != NULL){
        printf("Success\n");
        while(fgets(line, INPUT_LEN, fp) != NULL){
            if (readline(line, &start, &end, script_name)){
              continue;
            }
            add_range((SCRIPT_T *)all_scripts, script_name, start, end, 0);
            printf("Script: %s\tStart =  %d\tEnd = %d\n", script_name, start, end);

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
