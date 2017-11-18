#include <stdio.h>
#include <string.h>
#include "readfile.h"

#define FILE_PATH "Scripts.txt"

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

    readfile(FILE_PATH);

    return 0;
}
