#include "func.h"

int loadcities(FILE *fp, CITY_T *cities){
  char line[LINE_LEN];
  int i = 0;

  while (fgets(line, LINE_LEN, fp) != NULL && i < ARR_SIZE){
    switch(
      sscanf(line, "%[^,],%[^,],%[^,],%f,%f",
          cities[i].city, cities[i].state, cities[i].country,
          &cities[i].latitude, &cities[i].longitude)){
        case 1: sscanf(line, "%[^,],,%[^,],%f,%f",
                  cities[i].city, cities[i].country,
                  &cities[i].latitude, &cities[i].longitude);
                  break;
        case 2: sscanf(line, "%[^,],%[^,],,%f,%f",
                  cities[i].city, cities[i].state,
                  &cities[i].latitude, &cities[i].longitude);
                  break;
        case 5: break;
        default: printf("Something is wrong with %dth row in the file!\n", i);
                  return 0;
      };
    i++;
  }
  //printf("Count:%d\n", i);
  printf("Data is loaded successfully. There are %d entries in total!\n\n", i);
  return i;
}
