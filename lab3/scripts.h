#ifndef SCRIPTS_H
#define SCRIPTS_H

#define ARR_SIZE 300
#define STEP_SIZE 10
#define NAME_LEN 30

typedef struct script {
  int *start;
  int *end;
  char name[NAME_LEN];
  int length;
  int maxlength;
} SCRIPT_T;

int add_range(SCRIPT_T *all_scripts, char *name, int start, int end, int size);
void add_range_to_script(SCRIPT_T *script, int start, int end);
void initialize_all_scripts(SCRIPT_T *all_scripts, int max_size);



#endif
