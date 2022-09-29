#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int generateRandomMass(int mass[], int count, int minimumValue, int maximumValue) {
    //Пусть и простая, но зато своя цаца https://foxford.ru/wiki/informatika/generatsiya-psevdosluchaynyh-chisel
    unsigned long long seed;
    time(&seed);
    for (int i = 0; i < count; ++i) {
        seed = 69069LU*seed + 5LU;
        mass[i] = (int)(seed%(maximumValue-minimumValue)) + minimumValue;
    }
    return 0;
}

int strToNatInt(char str[]) {
    int result = 0;
    for (int i = 0; i < strlen(str); i++) {
        if ((int)str[i] >= 48 && (int)str[i] <= 57) {
            result = result * 10 + (str[i] - 48);
        } else {
            return -1;
        }
    }
    if (result == 0) {
        return -1;
    } else {
        return result;
    }
}

int main(int argc, char *argv[]) {
    //Меняйте как хотите, в пределах диапазона.
    int minimumValue = -1000, maximumValue = 1000, count;
    if (argc != 2) {
        printf("Invalid count of arguments\n");
        return -1;
    }
    if ((count = strToNatInt(argv[1])) == -1) {
        printf("Entered value isn't notNegative\n");
        return -1;
    }
    int *mass = malloc(sizeof(int)*count);
    if (!mass) {
        printf("Give me a memory, please\n");
        return -1;
    }
    generateRandomMass(mass, count, minimumValue, maximumValue);
    if (count == 1) {
        printf("Am I joke for you? Your mass is %d", mass[0]);
    }
    int min = mass[0], max = mass[0], minIndex = 0, maxIndex = 0;

    printf("Start massive is: %d ", mass[0]);
    for (int i = 1; i < count; ++i) {
        if (mass[i] < min) {
            min = mass[i];
            minIndex = i;
        } else if (mass[i] > max) {
            max = mass[i];
            maxIndex = i;
        }
        printf("%d ", mass[i]);
    }
    printf("\n");
    int temp = mass[minIndex];
    mass[minIndex] = mass[maxIndex];
    mass[maxIndex] = temp;
    printf("Minimum elem is %d, maximum element is %d. New array is: ", min, max);
    for (int i = 0; i < count; ++i) {
        printf("%d ", mass[i]);
    }
    printf("\n");
    free(mass);
    return 0;
}
