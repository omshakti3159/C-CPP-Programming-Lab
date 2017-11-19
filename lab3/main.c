#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "readfile.h"
#include "global.h"
#include "scripts.h"
#include "utf8.h"


int main() {
    int size;
    SCRIPT_T all_scripts[ARR_SIZE];

    size = loadscripts(FILE_PATH, &all_scripts);
    //print_all_scripts(all_scripts, size);

    char line[FILE_SIZE];
    unsigned char *p;
    int bytes_in_char;
    unsigned int codepoint;
    int count[size];
    int i;

    for (i = 0; i < size; i++){
      count[i] = 0;
    }

    while (fgets(line, FILE_SIZE, stdin) != NULL){
      p = (unsigned char *)line;
      //printf("%s\n", p);
      while (*p){
        codepoint = utf8_to_codepoint(p, &bytes_in_char);
        if (codepoint){
          count[find_script(all_scripts, size, codepoint)]++;
           _utf8_incr(p);
        }
        else{
          printf("%c Invalid UTF-8\n", *p);
          p++;
        }
      }
    }

    printf("%d\n", size);

    for (i = 0; i < size; i++){
      printf("Script: %30s\tCount: %d\n", all_scripts[i].name, count[i]);
    }

    //find_script(all_scripts, size);


    return 0;
}
