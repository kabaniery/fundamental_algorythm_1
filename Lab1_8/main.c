#include <stdio.h>
#include <string.h>

int abs(int val) {
    if (val < 0) {
        return val * -1;
    } else {
        return val;
    }
}

int getInt(FILE *file, int *val) {
    char c;
    while((c = fgetc(file)) == ' ' || c == '\n' || c == '\t') {
    }
    if (c == EOF) {
        return 2;
    }
    int isNegative = 0;
    if (c == '-') {
        isNegative = 1;
        c = fgetc(file);
    }
    *val = 0;
    if (c >= 48 && c <= 57) {
        while (c >= 48 && c <= 57) {
            *val = *val * 10 + c - 48;
            c = fgetc(file);
        }
    } else {
        return -1;
    }
    if (isNegative == 1) {
        *val = *val * -1;
    }
    if (c == EOF) {
        return 1;
    }
    return 0;

}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid count of arguments\n");
        return -1;
    }
    FILE *f;
    if (!(f = fopen(argv[1], "r"))) {
        printf("Can't open file\n");
        return -1;
    }
    int mass[128];
    long mass2[64];
    int i = 0, usl = 1;
    while (usl) {
        switch (getInt(f, &mass[i])) {
            case 2:
                if (i == 0) {
                    printf("File hasn't values\n");
                    return -1;
                } else {
                    usl = 0;
                    break;
                }
            case 1:
                usl = 0;
                break;
            case -1:
                printf("Value in file isn't number\n");
                return -1;
        }
        i++;
    }
    if (strcmp(argv[2], "a") == 0) {
        for (int a = 0; a < i; a += 2) {
            printf("%d ", mass[a]);
            mass2[a/2] = mass[a];
        }
        printf("\n");
    } else if (strcmp(argv[2], "b") == 0) {
        int i2 = 0;
        for (int a = 0; a < i; a++) {
            if (mass[a]%2 == 0) {
                printf("%d ", mass[a]);
                mass2[i2] = mass[a];
            }
        }
        printf("\n");
    } else if (strcmp(argv[2], "c") == 0) {
        int val;
        printf("Enter a value: ");
        if (getInt(stdin, &val) == -1) {
            printf("\n Your value isn't a number\n");
            return -1;
        }
        if (val < 0 || val >= i) {
            printf("\nInvalid index\n");
            return -1;
        }
        if (i == 1) {
            mass2[0] = mass[0];
            printf("\n%d\n", mass[0]);
            return 0;
        }
        int diff = abs(mass[val] - mass[0]), index = 0;
        for (int a = 1; a < i; a++) {
            if (abs(mass[val]-mass[a]) > diff) {
                index = a;
                diff = abs(mass[val]-mass[a]);
            }
        }
        mass2[0] = mass[index];
        printf("\n%d\n", mass[index]);
    } else if (strcmp(argv[2], "d") == 0) {
        int val;
        printf("Enter a value: ");
        if (getInt(stdin, &val) == -1) {
            printf("\n Your value isn't a number");
            return -1;
        }
        if (val < 0 || val >= i) {
            printf("\nInvalid index\n");
            return -1;
        }
        if (i == 1) {
            mass2[0] = 0;
            printf("\n0\n");
            return 0;
        }
        long sum = 0;
        for (int a = 0; a < val; a++) {
            sum += mass[a];//я надеюсь, что мы гарантируем, что сумма не выйдет за пределы лонга. Писать предпоследнюю сумму и следить за её изменением не хочу (((
        }
        mass2[0] = sum;
        printf("\n%ld\n", mass2[0]);
    } else if (strcmp(argv[2], "e") == 0) {
        int val;
        printf("Enter a value: ");
        if (getInt(stdin, &val) == -1) {
            printf("\n Your value isn't a number");
            return -1;
        }
        if (val < 0 || val >= i) {
            printf("\nInvalid index\n");
            return -1;
        }
        long sum = 0;
        for (int a = 0; a < i; a++) {
            if (mass[a] < mass[val]) {
                sum += mass[a];
            }
        }
        mass2[0] = sum;
        printf("\n%ld\n", mass2[0]);
    } else {
        printf("Invalid code\n");
        return -1;
    }
    fclose(f);
    return 0;
}
