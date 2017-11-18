#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NAME_LEN  35
#define ARR_SIZE  1000
#define LINE_LEN  100
#define INPUT_LEN 100
#define MIN_LEN   3
#define MAX_MATCH 30
#define FILE_NAME "world_cities.csv"
// #define FILE_NAME "atom-amd64.deb"
#define EXIT_CMD  "bye"


typedef struct{
  char city[NAME_LEN];
  char state[NAME_LEN];
  char country[NAME_LEN];
  float latitude;
  float longitude;
} CITY_T;

int distance(double lat1, double lon1, double lat2, double lon2);
void printcity(CITY_T city);
int loadcities(FILE *fp, CITY_T *cities);
CITY_T *findcity(char *name, CITY_T *cities, int size);
CITY_T *matchcity(char *name, CITY_T *cities, int size);
int scancity(char *keyword, CITY_T *cities, int size, CITY_T **city);
void stolower(char *src, char *dst);
