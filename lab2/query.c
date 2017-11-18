#include "func.h"

void printcity(CITY_T city){
  // printf("City: %s\tState: %s\tCountry: %s\nLatitude: %.2f\tLongitude: %.2f\n\n",
  //   city.city, city.state, city.country, city.latitude, city.longitude);
  printf("City: %-20s\tCountry: %-20s\n",
    city.city, city.country);
}

CITY_T *matchcity(char *name, CITY_T *cities, int size){
  int length = strlen(name);
  int match = 0;
  int matchcities[MAX_MATCH];
  int i;
  char input[INPUT_LEN];
  // char* ptr = NULL;
  char *lowname = malloc(sizeof(name));
  char *lowcity = malloc(NAME_LEN * sizeof(char));
  stolower(name, lowname);

  for (i = 0; i < size; i++){
    stolower(cities[i].city, lowcity);
    if (!strncmp(lowname, lowcity, length)){
      matchcities[match] = i;
      //printf("%s\t", matchcities[match].city);
      match++;
      if (match == MAX_MATCH){
        break;
      }
    }
  }
  free(lowname);
  free(lowcity);


  if (!match){
    printf("City \"%s\" cannot be found!\n", name);
    return NULL;
  }

  if (match == 1){
    printf("City \"%s\" is retrived!\n", cities[matchcities[0]].city);
    return &cities[matchcities[0]];
  }

  while (1){
    printf("The name \"%s\" has matched %d cities. Please enter the index of the correct city.\n", name, match);
    for (i = 0; i < match; i++){
          printf("[%d] ", i);
          printcity(cities[matchcities[i]]);
    }
    printf("> ");
    fgets(input, INPUT_LEN, stdin);
    if(!sscanf(input, "%d", &i)){
      printf("Invalid index!\n");
      continue;
    }
    if (i >= 0 && i < match){
      printf("City with name \"%s\" is retrived!\n", cities[matchcities[i]].city);
      return &cities[matchcities[i]];
    }
    else{
      printf("Invalid index!\n");
    }
  }
  return NULL;
}

int scancity(char *keyword, CITY_T *cities, int size, CITY_T **city){
  int length;
  char name[NAME_LEN];
  char input[INPUT_LEN];

  while(1){
    printf("$ Please enter the name of the %s city or \"bye\" to exit.\n", keyword);
    printf("> ");
    fgets(input, INPUT_LEN, stdin);
    strncpy(name, input, NAME_LEN);
    length = strlen(name);

    if (name[length - 1] == '\n'){
      name[--length] = '\0';
    }

    char* lowname = malloc(sizeof(name));
    stolower(name, lowname);

    if (length < MIN_LEN){
      printf("Please enter no less than %d characters\n", MIN_LEN);
      continue;
    }

    if (!strcmp(lowname, EXIT_CMD)){
      printf("Goodbye!\n");
      free(lowname);
      return 1;
    }
    free(lowname);
    *city = matchcity(name, cities, size);
    if (!(*city == NULL)){
      return 0;
    }
  }
  return 0;
}
