#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static short ctr = 0;
static char prev[1024];
static const short MAX_BATTERY = 16;

void append(char *string, char c) {
    size_t len = strlen(string);
    string[len] = c;
    string[len + 1] = '\0';
}

char *ret(char *string) {
    strcpy(prev, string);
    return string;
}

char *headsetcontrol() {
    if (++ctr % 60 != 0) return prev;
    ctr = 0;
    FILE *file;
    char c;
    char result[1024];
    file = popen("headsetcontrol -b -c", "r");
    if (file == NULL) return "";
    while ((c = fgetc(file)) != EOF) append(result, c);

    if (strlen(result) == 0) ret("Off");

    // Seems to work
    char tres[strlen(result)];
    strcpy(tres, result);

    long battery = strtol(tres, NULL, 10);

    if (battery == -2) return ret("Off");
    else if (battery == -1) return ret("Charging");
    else if (0 <= battery && battery <= 100) {
        double hours = (double) battery * (MAX_BATTERY / 100.0);
        char value[1024];
        sprintf(value, "%ld%% (~%.2fh)", battery, hours);
        return ret(value);
    } else if (battery == ']') return "sadge";
    else return ret("idk m8");
}