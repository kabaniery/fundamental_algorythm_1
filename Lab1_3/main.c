#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Invalid count of arguments\n");
        return -1;
    }
    if (argv[1][0] != '/' && argv[1][0] != '-') {
        printf("Invalid flag. Any flag may start with symbol '-' or '/'\n");
        return -1;
    }
    int index = 1;
    FILE *fileRead;
    FILE *fileResult;
    if (argv[1][1] == 'n') {
        if (argc != 4) {
            printf("Invalid count of arguments\n");
            return -1;
        }
        index += 1;
        if (!(fileResult = fopen(argv[3], "w"))) {
            printf("Can't create result file\n");
            return -1;
        }
    } else {
        if (argc != 3) {
            printf("Invalid count of arguments\n");
            return -1;
        }
        char *nameOut = malloc((size_t)strlen("out_") + (size_t)strlen(argv[1]) + 1);
        if (!nameOut) {
            printf("Can't use memory\n");
            return -1;
        }
        memcpy(nameOut, "out_", 4);
        memcpy(nameOut + 4, argv[1], strlen(argv[1]));
        nameOut[4 + strlen(argv[1])] = '\0';
        if (!(fileResult = fopen(nameOut, "w"))) {
            printf("Can't create result file\n");
            return -1;
        }
    }
    if (sizeof(argv[1])/sizeof(argv[1][0]) != index + 1 ) {
        printf("Invalid flag\n");
    }
    if (!(fileRead = fopen(argv[2], "r"))) {
        printf("Can't open file\n");
        return -1;
    }
    if (argv[1][index] == 'd') {
        char c;
        while ((c = fgetc(fileRead)) != EOF) {
            if (c < 48 || c > 57) {
                fputc(c, fileResult);
            }
        }
    } else if (argv[1][index] == 'i') {
        char c;
        int count = 0;
        while ((c = fgetc(fileRead)) != EOF) {
            if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
                count++;
            } else if (c == '\n') {
                fprintf(fileResult, "%d\n", count);
                count = 0;
            }
        }
        if (count != 0) {
            fprintf(fileResult, "%d", count);
        }
    } else if (argv[1][index] == 's') {
        char c;
        int count = 0;
        while ((c = fgetc(fileRead)) != EOF) {
            if (c == '\n') {
                fprintf(fileResult, "%d\n", count);
                count = 0;
            } else if ((c < 48 || c > 57) && (c < 65 || c > 90) && (c < 97 || c > 122)) {
                count++;
            }
        }
        if (count != 0) {
            fprintf(fileResult, "%d", count);
        }
    } else if (argv[1][index] == 'a') {
        char c;
        while ((c = fgetc(fileRead)) != EOF) {
            if (c >= 48 && c <= 57) {
                fputc(c, fileResult);
            } else {
                fprintf(fileResult, "%d", c);
            }
        }
    } else if (argv[1][index] == 'f') {
        char c;
        int count = 0;
        while ((c = fgetc(fileRead)) != EOF) {
            while (c == ' ' || c == '\n') {
                c = fgetc(fileRead);
            }
            count++;
            if (c == EOF) {
                break;
            }
            while (c != ' ' && c != '\n') {
                if (count % 2 == 0 && c >= 65 && c <= 90) {
                    c = c + 32;
                }
                if (count % 5 == 0) {
                    fprintf(fileResult, "%d", c);
                } else {
                    fputc(c, fileResult);
                }
            }
        }
    } else {
        printf("Invalid flag\n");
        return -1;
    }
    fclose(fileRead);
    fclose(fileResult);
    return 0;
}
