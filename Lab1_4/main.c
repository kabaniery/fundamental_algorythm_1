#include <stdio.h>

int fGetString(FILE *file, char str1[], char str2[], char str3[]) {
    char c;
    int i = 0, sw = 1;
    while ((c = fgetc(file)) != '\n') {
        if (c == ' ') {
            if (sw < 4) {
                switch (sw) {
                    case 1:
                        str1[i] = '\0';
                        break;
                    case 2:
                        str2[i] = '\0';
                        break;
                    case 3:
                        str3[i] = '\0';
                        break;
                }
                sw++;
                i = 0;
            } else {
                return -1;
            }
        } else if (c == EOF) {
            return 1;
        } else {
            if (i == 254) {
                return -1;
            }
            switch (sw) {
                case 1:
                    str1[i] = c;
                    break;
                case 2:
                    str2[i] = c;
                    break;
                case 3:
                    str3[i] = c;
                    break;
            }
            i++;
        }
    }
    if (sw != 3) {
        return -1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Invalid count of arguments\n");
        return -1;
    }
    FILE *f, *output;
    if ((f = fopen(argv[1], "r")) == NULL || !(output = fopen(".temp.txt", "w"))) {
        printf("Can't open file\n");
        return -1;
    }
    char first[256], second[256], third[256];
    int usl = 1, temp = 0;
    while (usl) {
        switch (fGetString(f, first, second, third)) {
            case 1:
                fprintf(output,"%s %s %s\n", third, first, second);
                usl = 0;
                break;
            case -1:
                printf("Invalid file format\n");
                usl = -1;
                break;
            default:
                /*
                if (temp) {
                    fprintf(output, "\n");
                } else {
                    temp++;
                }
                 */
                fprintf(output, "%s %s %s\n", third, first, second);
                break;
        }
    }
    fclose(f); fclose(output);
    if (remove(argv[1]) == -1 || rename(".temp.txt", argv[1]) == -1) {
        printf("Critical error, can't finish progress. Please rename file .temp.txt into need name\n");
        return -1;
    }
    return 0;
}
