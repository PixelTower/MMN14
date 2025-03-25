#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "firstpass.h"

int IC = 0; // Instruction Counter
int DC = 0; // Data Counter

// פונקציה לבדיקת תקינות שם תווית
int is_valid_label(const char *label)
{
    int i = 0;
    if (!isalpha(label[0]))
        return 0; // שם תווית חייב להתחיל באות
    for (i = 1; label[i] != '\0'; i++)
    {
        if (!isalnum(label[i]))
            return 0; // תווית יכולה להכיל רק אותיות וספרות
    }
    return 1;
}

// פונקציה לקביעת גודל משתנה .data או .string
int calculate_data_size(const char *line)
{
    if (strncmp(line, ".string", 7) == 0)
    {
        char *start = strchr(line, '\"');
        if (!start)
            return 0; // אין גרשיים בכלל

        char *end = strchr(start + 1, '\"');
        if (!end)
            return 0; // אין גרש סוגר

        return (end - start - 1) + 1; // אורך המחרוזת + תו סיום
    }
    return 4;
    למה דווקא 4 ? ? // עבור .data נניח שכל משתנה תופס 4 בייט
}

// פונקציה לחישוב גודל פקודה
int get_instruction_size(const char *line)
{
    return 4;
    למה 4 ? ? // נניח שכל פקודה רגילה תופסת 4 בייט
}

// פונקציה לביצוע המעבר הראשון - איסוף תוויות וקביעת כתובות
void first_pass(FILE *input)
{
    char line[256];
    rewind(input); // מחזיר את קובץ הקלט להתחלה

    while (fgets(line, sizeof(line), input))
    {
        // מסירים תו ירידת שורה
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        // דילוג על שורות ריקות או הערות
        if (line[0] == '\0' || line[0] == ';')
        {
            continue;
        }

        // הסרת רווחים מתחילת השורה
        char *trimmed_line = line;
        while (*trimmed_line && isspace(*trimmed_line))
        {
            trimmed_line++;
        }

        // זיהוי ושמירת תוויות
        char *colon = strchr(trimmed_line, ':');
        if (colon)
        {
            *colon = '\0'; // מסיר את הנקודתיים

            if (!is_valid_label(trimmed_line))
            {
                fprintf(stderr, "ERROR: Invalid label name: %s\n", trimmed_line);
                continue;
            }

            register_label(trimmed_line, IC); // רושם תווית עם הכתובת הנוכחית של IC

            // בדיקה אם יש הוראה אחרי התווית
            char *instruction_part = colon + 1;
            while (*instruction_part && isspace(*instruction_part))
            {
                instruction_part++;
            }

            if (*instruction_part != '\0')
            {
                IC = IC + get_instruction_size(instruction_part);
            }
        }
        else
        {
            // אם זה משתנה (הנחיית .data או .string), יש לעדכן את DC
            if (strncmp(trimmed_line, ".data", 5) == 0 || strncmp(trimmed_line, ".string", 7) == 0)
            {
                DC += calculate_data_size(trimmed_line);
            }
            else
            {
                // זיהוי פקודות והגדלת IC בהתאם לגודל הפקודה
                IC += get_instruction_size(trimmed_line);
            }
        }
    }

    printf("First pass completed. IC = %d, DC = %d, Total labels: %d\n", IC, DC, get_label_count());
}
