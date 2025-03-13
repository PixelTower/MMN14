#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "firstpass.h"

int DC = 0, IC = 0;
void first_scan(FILE *frontinput)
{
    char line[256];
    while (fgets(line, sizeof(line), frontinput))
    {
        char *label = strchr(line, ':');
        if (label)
        {
            label = strtok(line, " \t\n");
            if (label)
            { //LOOP:
                if (label[strlen(label) - 1] == ':')
                {
                    label[strlen(label) - 1] = '\0';
                    label = strtok(NULL, " \t\n");
                }
            }
        }
    }
}
