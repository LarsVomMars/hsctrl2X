#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BATTERY 16

static short ctr = -1;
static char prev[32] = {0};

void append(char *string, char c) {
  size_t len = strlen(string);
  string[len] = c;
  string[len + 1] = '\0';
}

char *ret(char *string) {
  strcpy(prev, string);
  return prev;
}

char *headsetcontrol() {
  if (++ctr % 60 != 0)
    return prev;
  ctr = 0;
  FILE *file;
  char c;
  char result[8] = {0};
  file = popen("headsetcontrol -b -c", "r");

  if (file == NULL)
    return NULL;

  while ((c = fgetc(file)) != EOF)
    append(result, c);

  if (strlen(result) == 0)
    return ret("Off");

  long battery = strtol(result, NULL, 10);

  if (battery == -2)
    return ret("Off");
  else if (battery == -1)
    return ret("Charging");
  else if (battery >= 0 && battery <= 100) {
    double hours = (double)battery * (MAX_BATTERY / 100.0);
    char value[32] = {0};
    sprintf(value, "%ld%% (~%.2fh)", battery, hours);
    return ret(value);
  } else
    return ret("idk m8");
}

