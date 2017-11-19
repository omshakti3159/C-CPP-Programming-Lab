#include <stdio.h>
#include <string.h>
#include "readfile.h"
#include "global.h"
#include "scripts.h"

int main() {

    // char input[INPUT_LEN];
    // unsigned int start, end;
    // char script_name[NAME_LEN];

//    while(1){
//        printf("Enter anything: ");
//        fgets(input, INPUT_LEN, stdin);
//        readline(input, &start, &end, script_name);
//        printf("%d\t%d\n%s\n", start, end, script_name);
//    }

    int size;
    SCRIPT_T all_scripts[ARR_SIZE];

    size = readfile(FILE_PATH, &all_scripts);
    print_all_scripts(all_scripts, size);
    find_script(all_scripts, size);


    return 0;
}
