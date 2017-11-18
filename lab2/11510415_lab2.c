#include "func.h"

int main(){

  CITY_T cities[ARR_SIZE];
  FILE *fp;
  int count;
  CITY_T *city1 = NULL;
  CITY_T *city2 = NULL;

  printf("Part 1: Load the data\n");

  if ((fp = fopen(FILE_NAME, "r")) != NULL){
    if (!(count = loadcities(fp, cities))){
      printf("Data is not loaded!\n");
      return 1;
    }
    fclose(fp);
  }
  else{
    perror(FILE_NAME);
    return 1;
  }

  printf("Part 2: Query\n");

  while (1){
    if (scancity("first", cities, count, &city1)){
      return 0;
    }
    printf("\n");
    if (scancity("second", cities, count, &city2)){
      return 0;
    }
    printf("\n");
    if (city1 == NULL){
      printf("City1 is NULL.\n");
    }
    printf("! The distance from %s to %s is %d km.\n\n",
      (*city1).city, (*city2).city,
      distance((*city1).latitude, (*city1).longitude,
                (*city2).latitude, (*city2).longitude));
  }

  return 0;
}
