#include <stdio.h>
#include <string.h>
//Lab1_5

int fgetstring(char str[], FILE *file) {
    int i = 0;
    char c;
    while (1) {
        if ((c = fgetc(file)) == '\n' || c == EOF || i > 254) {
            break;
        }
        str[i] = c;
        i++;
    }
    if (i == 0) {
        str[0] = '\0';
        return -1;
    }
    str[i] = '\0';
    return 0;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Invalid count of arguments\n");
        return -1;
    }
    if (strcmp(argv[1], "-fi") == 0) {
        if (argc != 3) {
            printf("Invalid count of arguments\n");
            return -1;
        }
        FILE *f, *list, *output;
        char name[256] = "", c;
        if ((f = fopen(argv[2], "r")) == NULL || (output = fopen("output.txt", "w")) == NULL) {
            printf("Invalid name of file or can't open file\n");
            return -1;
        }
        while (fgetstring(name, f) != -1) {
            if ((list = fopen(name, "r")) == NULL) {
                printf("Name in file is too long or file with this name doesn't exist\n");
                return -1;
            }
            while ((c = fgetc(list)) != EOF) {
                fputc(c, output);
            }
            // name[0] = '\0';
        }
        fclose(f); fclose(list); fclose(output);
    } else if (strcmp(argv[1], "-cin") == 0) {
        if (argc != 2) {
            printf("Invalid count of arguments\n");
            return -1;
        }
        FILE *list, *output;
        char name[256] = "", c;
        printf("Enter each file in new string. For ending stream, write empty string\n");
        if ((output = fopen("output.txt", "w")) == NULL) {
            printf("Can't create file\n");
            return -1;
        }
        while (fgetstring(name, stdin) != -1) {
            if ((list = fopen(name, "r")) == NULL) {
                printf("Can't open file\n");
                return -1;
            }
            while ((c = fgetc(list)) != EOF) {
                fputc(c, output);
            }
        }
        fclose(list); fclose(output);
    } else if (strcmp(argv[1], "-arg") == 0) {
        int i;
        char c;
        FILE *list, *output;
        if ((output = fopen("output.txt", "w")) == NULL) {
            printf("Can't create file\n");
            return -1;
        }
        for (i = 2; i < argc; ++i) {
            if ((list = fopen(argv[i], "r")) == NULL) {
                printf("Can't open file\n");
                return -1;
            }
            while ((c = fgetc(list)) != EOF) {
                fputc(c, output);
            }
        }
        fclose(list); fclose(output);
    }
    return 0;
}