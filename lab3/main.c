#include <stdio.h>
#include "loadscripts.h"
#include "global.h"
#include "scripts.h"
#include "readfile.h"

/*
  If you want to change the global variables
  (like scripts.txt path, maximum input length, etc),
  please go to "global.h".
*/


int main() {
    int size;
    SCRIPT_T all_scripts[ARR_SIZE];


    /*
      1. Load all the scripts name and codepoint ranges from the file
    */
    if ((size = loadscripts(FILE_PATH, &all_scripts)) <= 0){
      printf("Error: Please check the file \"%s\"!\n", FILE_PATH);
      return 1;
    }

    //print_all_scripts(all_scripts, size);

    /*
      2. Read the input and count the scripts.
      Then display the script with the greatest count.
    */
    int *count = initialize_count(size);
    read_and_count(all_scripts, count, size);
    print_max_count(all_scripts, count, size);




    return 0;
}
