#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int myPow(int a, int b) {
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

int getSpecInt(char str[], int ss) {
    int isNegative = 0;
    if (str[0] == '-') {
        isNegative = 1;
    }
    int result = 0;
    for (int i = 0+isNegative; i < strlen(str); i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            if (str[i] - 48 >= ss) {
                return -1;
            } else {
                result = result * ss + str[i] - 48;
            }
        } else if (str[i] >= 65 && str[i] <= 90) {
            if (str[i] - 54 >= ss) {
                return -1;
            } else {
                result = result * ss + str[i] - 54;
            }
        } else if (str[i] >= 97 && str[i] <= 122) {
            if (str[i] - 86 >= ss) {
                return -1;
            } else {
                result = result * ss + str[i] - 86;
            }
        } else {
            return -1;
        }
    }
    return result;
}

char* cinGetStr() {
    char *mass = malloc(sizeof(char)*256), c;
    int i = 0;
    while((c=getc(stdin)) == '\n' || c == ' ' || c == '\t') {}
    while(c != ' ' && c != '\n' && c != '\t' && c != EOF) {
        mass[i] = c;
        i++;
        c = getc(stdin);
        if (i > 254) {
            return NULL;
        }
    }
    if (i == 0) {
        return NULL;
    }
    mass[i] = '\0';
    return mass;

}

int compareToNewSS(int val, int ss, char res[]) {
    int del = ss, i = 0, temp;
    while (val / del > 0) {
        del *= ss;
    }
    while (val != 0) {
        del /= ss;
        temp = val / del;
        if (temp > 9) {
            res[i] = 'A' + temp - 10;
        } else {
            res[i] = '0' + temp;
        }
        i++;
        val -= del*temp;
    }
    res[i] = '\0';
    return 0;
}

int main(int argc, char *argv[]) {
    /*
    if (argc < 4) {
        printf("Invalid count of arguments\n");
        return -1;
    }
     */
    int ss, value, maxValue = -1, isNegative = 0;
    char *c;
    if ((c = cinGetStr()) != NULL) {
        ss = getSpecInt(c, 10);
    }
    while ((c = cinGetStr()) != NULL) {
        if (strcmp(c, "Stop") == 0) {
            break;
        } else if ((value = getSpecInt(c, ss)) != -1) {
            if (value > maxValue) {
                maxValue = value;
                if (c[0] == '-') {
                    isNegative = 1;
                }
            }
        } else {
            printf("One of arguments isn't a value\n");
            return -1;
        }
    }
    if (c == NULL) {
        printf("Warning, you don't write Stop command, please use this word to close input\n");
    }
    char result[256];
    if (isNegative == 1) {
        compareToNewSS(maxValue, 9, result);
        printf("-%s ", result);
        compareToNewSS(maxValue, 18, result);
        printf("-%s ", result);
        compareToNewSS(maxValue, 27, result);
        printf("-%s ", result);
        compareToNewSS(maxValue, 36, result);
        printf("-%s\n", result);
    } else {
        compareToNewSS(maxValue, 9, result);
        printf("%s ", result);
        compareToNewSS(maxValue, 18, result);
        printf("%s ", result);
        compareToNewSS(maxValue, 27, result);
        printf("%s ", result);
        compareToNewSS(maxValue, 36, result);
        printf("%s\n", result);
    }

    /*
    ss = getSpecInt(argv[1], 10);
    int maxIndex;
    for (int i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "Stop") == 0) {
            break;
        } else if ((value = getSpecInt(argv[i], ss)) != -1) {
            if (value > maxValue) {
                maxValue = value;
                maxIndex = i;
            }
        } else {
            printf("One of arguments isn't a value\n");
            return -1;
        }
    }
    char result[256];
    if (argv[maxIndex][0] == '-') {
        compareToNewSS(maxValue, 9, result);
        printf("-%s ", result);
        compareToNewSS(maxValue, 18, result);
        printf("-%s ", result);
        compareToNewSS(maxValue, 27, result);
        printf("-%s ", result);
        compareToNewSS(maxValue, 36, result);
        printf("-%s\n", result);
    } else {
        compareToNewSS(maxValue, 9, result);
        printf("%s ", result);
        compareToNewSS(maxValue, 18, result);
        printf("%s ", result);
        compareToNewSS(maxValue, 27, result);
        printf("%s ", result);
        compareToNewSS(maxValue, 36, result);
        printf("%s\n", result);
    }
     */
    return 0;
}
