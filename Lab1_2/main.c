#include <stdio.h>
#include <string.h>
#include <math.h>

void getX(double a, double b, double c) {
    double d = b*b - 4*a*c;
    if (a == 0 && b != 0) {
        if (-1*c/b == 0) {
            printf("for a = %f, b = %f, c = %f x1 is 0\n", a, b, c);
        } else {
            printf("for a = %f, b = %f, c = %f x1 is %f\n", a, b, c, -1 * c / b);
        }
    } else if (a == 0){
        printf("for a = %f, b = %f, c = %f there is no solutions\n", a, b, c);
    } else {
        if (d > 0) {
            printf("for a = %f, b = %f, c = %f x1 is %f and x2 is %f\n", a, b, c, (-1 * b + sqrt(d)) / (2 * a),
                   (-1 * b - sqrt(d)) / (2 * a));
            if ((-1 * b + sqrt(d)) / (2 * a) == 0 || (-1 * b - sqrt(d)) / (2 * a) == 0) {
                printf("Pozhaluysta ne ubivayte za -0.000...; eto ne ya, eto c s ego otobrazheniem double\n");
            }
        } else if (d == 0) {
            if ((-1 * b ) / (2 * a) == 0) {
                printf("for a = %f, b = %f, c = %f x1 is 0\n", a, b, c);
            } else {
                printf("for a = %f, b = %f, c = %f x1 is %f\n", a, b, c, (-1 * b) / (2 * a));
            }
        } else {
            printf("for a = %f, b = %f, c = %f there is no solutions\n", a, b, c);
        }
    }
}

void isTriangle(double a, double b, double c) {
    if (a*a + b*b == c*c) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}

int strToDouble(char val[], double *number) {
    int length = (int) strlen(val), isNegative = 0, getDot = 0, afterDot = 0, counter = 0;
    for (int i = 0; i < length; i++) {
        if ((int)val[i] == 45 && i == 0) {
            isNegative = 1;
        } else if (((int)val[i] == 46 && i != 0 && i != length - 1 && getDot == 0 && isNegative == 0) || ((int)val[i] == 46 && i != 1 && i != length - 1 && getDot == 0 && isNegative == 1)) {
            getDot = 1;
        } else if ((int)val[i] >= 48 && (int)val[i] <= 57) {
            if (getDot == 0) {
                *number = *number * 10.0 + val[i] - '0';
            } else {
                afterDot = afterDot * 10 + val[i] - '0';
                counter++;
            }
        } else {
            return -1;
        }
    }
    if (getDot == 1) {
        double addition = afterDot / pow(10, counter);
        *number += addition;
    }
    if (isNegative == 1) {
        *number = *number*-1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    double val1 = 0.0, val2 = 0.0, val3 = 0.0;
    if (argc <= 2) {
        printf("Invalid count of command\n");
        return -1;
    }
    if (strcmp(argv[1], "-q") == 0 || strcmp(argv[1], "/q") == 0) {
        //Найти корни квадратного уравнения для всех перестановок его коэффициентов
        if (argc != 5) {
            printf("Invalid count of arguments\n");
            return -1;
        }
        if (strToDouble(argv[2], &val1) == -1 || strToDouble(argv[3], &val2) == -1 || strToDouble(argv[4], &val3) == -1) {
            printf("One of entered arguments isn't number\n");
            return -1;
        }
        getX(val1, val2, val3);
        getX(val1, val3, val2);
        getX(val2, val1, val3);
        getX(val2, val3, val1);
        getX(val3, val1, val2);
        getX(val3, val2, val1);
    }
    else if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "/m") == 0) {
        //Определить кратность первого числа второму
        if (argc != 4) {
            printf("Invalid count of arguments\n");
            return -1;
        }
        if (strToDouble(argv[2], &val1) == -1 || strToDouble(argv[3], &val2) == -1) {
            printf("One of entered arguments isn't number\n");
            return -1;
        }
        //Вычесть из прямого частного, частное, приведенное к инту
        if (val1/val2 - floor(val1/val2) != 0.0) {
            printf("No\n");
        } else {
            printf("Yes\n");
        }
    }
    else if (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "/t") == 0) {
        //Определить, являются ли 3 введённых значения сторонами прямоугольного треугольника
        if (strToDouble(argv[2], &val1) == -1 || strToDouble(argv[3], &val2) == -1 || strToDouble(argv[4], &val3) == -1) {
            printf("One of entered arguments isn't number\n");
            return -1;
        }
        if (val1 > val2 && val1 > val3) {
            isTriangle(val2, val3, val1);
        } else if (val2 > val1 && val2 > val3) {
            isTriangle(val1, val3, val2);
            } else {
            isTriangle(val1, val2, val3);
        }
    }
    else {
        printf("Invalid command\n");
        return -1;
    }
    return 0;
}
