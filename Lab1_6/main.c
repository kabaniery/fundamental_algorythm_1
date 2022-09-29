#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int newName(char str[], char newValue[]) {
    for (int i = 0; i < strlen(newValue); ++i) {
        str[i] = newValue[i];
    }
    str[strlen(newValue)] = '\0';
    return 0;
}

int readValue(FILE *input, FILE *out) {
    char c, name[256];
    while((c = fgetc(input)) == ' ' || c == '\t' || c == '\n') {}
    if (c == EOF) {
        return 1;
    }
    int i = 0;
    int currentSystem, maxSystem = 1;
    while (c != ' ' && c != '\t' && c != '\n') {
        if (c == EOF) {
            break;
        }
        if (i >= 255) {
            return -1;
        }
        if ((int)c >= 48 && (int)c <= 57) {
            name[i] = c;
            if (c-47 > maxSystem) {
                maxSystem = c - 47;
            }
        } else if ((int)c >= 65 && (int)c <= 90) {
            name[i] = c;
            if (c - 54 > maxSystem) {
                maxSystem = c - 54;
            }
        } else if ((int)c >= 97 && (int)c <= 122) {
            name[i] = c - 32;
            if (c - 86 > maxSystem) {
                maxSystem = c - 86;
            }
        } else {
            return -1;
        }
        i++;
        c = getc(input);
    }
    name[i] = '\0';
    long long result = 0;
    for (i = 0; i < strlen(name); ++i) {
        result *= maxSystem;
        if ((int)name[i] >= 48 && (int)name[i] <= 57) {
            result += name[i] - 48;
        } else {
            result += name[i] - 65;
        }
    }
    fprintf(out, "%s %d %lld \n", name, maxSystem, result);
    if (c == EOF) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid count of arguments\n");
        return -1;
    }
    FILE *f, *out;

    char *nameOut = malloc((size_t)strlen("out_") + (size_t)strlen(argv[1]) + 1);
    if (!nameOut) {
        printf("Can't use memory\n");
        return -1;
    }
    memcpy(nameOut, "out_", 4);
    memcpy(nameOut + 4, argv[1], strlen(argv[1]));
    nameOut[4 + strlen(argv[1])] = '\0';
    if (!(f = fopen(argv[1], "r"))) {
        printf("Can't open file\n");
        return -1;
    }
    if (!(out = fopen(nameOut, "w"))) {
        printf("Can't create out file\n");
        return -1;
    }
    int sw = 1;
    while (sw) {
        switch (readValue(f, out)) {
            case -1:
                printf("Content of file is invalid\n");
                return -1;
            case 1:
                sw = 0;
                break;
        }
    }
    fclose(f); fclose(out); free(nameOut);
    return 0;
}
