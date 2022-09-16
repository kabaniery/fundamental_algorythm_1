#include <stdio.h>
#include <string.h>
#include <math.h>

int isDigit(int len, char str[])
{
    //Определить является ли строка целым положительным числом, иначе вернуть -1
    int result = 0;
    int i;
    for (i = 0; i < len; i++) {
        if ((str[i] >= 48 && str[i] <= 57)) {
            result = result * 10 + str[i] - '0';
        } else {
            return -1;
        }
    }
    return result;
}


int main(int argc, char *argv[]) {
    int number;
    if (argc != 3) {
        printf("Invalid value of arguments\n");
        return -1;
    } else {
        if (argv[2][0] != '-' && argv[2][0] != '/') {
            printf("Invalid flag. Any flag starts with symbol '-' or symbol '/'\n");
            return -1;
        }
        if ((number = isDigit(strlen(argv[1]), argv[1])) == -1) {
            printf("Introduced number isn't positive whole number\n");
            return -1;
        }
        if (strcmp(argv[2], "-h") == 0 || strcmp(argv[2],"/h") == 0) {
            //Вывести числа в пределах ста, кратные ввёденному. Отсутствие их обработать
            if (number > 50) {
                printf("There are no multiples of this\n");
            } else {
                for (int i = 1; i <= 100/number; i++) {
                    printf("%d ", number * i);
                }
                printf("\n");
            }
        } else if (strcmp(argv[2], "-p") == 0 || strcmp(argv[2], "/p") == 0) {
            //Определить, является ли ввёденное число простым или составным
            //Если перебор слишком медленный, то пробовать теорему Миллера https://ru.wikipedia.org/wiki/Тест_Миллера_(теория_чисел)
            //пов могут не одобрить!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if (number % 2 == 0) {
                printf("%d is composite number\n", number);
            } else {
                for (int i = 3; i <= (int)floor(sqrt(number)); i += 2) {
                    if (number % i == 0) {
                        number = -1;
                        break;
                    }
                }
                if (number == -1) {
                    printf("%s is composite number\n", argv[1]);
                } else {
                    printf("%d is simple number\n", number);
                }
            }
        } else if (strcmp(argv[2], "-s") == 0 || strcmp(argv[2], "/s") == 0) {
            //Вывести все цифры числа через пробел
            for (int i = 0; i < strlen(argv[1]); i++) {
                printf("%c ", argv[1][i]);
            }
            printf("\n");
        } else if (strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "/e") == 0) {
            //Вывести числа от 1 до 10 и их степени от одного до числа (если оно не больше 10)
            if (number > 10) {
                printf("Number is too big (more than 10)\n");
            } else {
                long long value;
                for (int i = 1; i <= 10; i++) {
                    printf("%d: ", i);
                    value = 1;
                    for (int j = 1; j < number; j++) {
                        value = value * i;
                        printf("%d, ", value);
                    }
                    value = value * i;
                    printf("%lld", value);
                    printf("\n");
                }
            }
        } else if (strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "/a") == 0) {
            //Суммировать все числа от 1 до указанного (уложиться в uint)
            printf("%d", (number * number + number) / 2);
        } else if (strcmp(argv[2], "-f") == 0 || strcmp(argv[2], "/f") == 0) {
            //Вывести факториал числа (уложиться в uint)
            unsigned long long result = 1;
            if (number > 22) {
                printf("Result is too big, please write number less 23");
            } else {
                for (int i = 2; i <= number; i++) {
                    result *= i;
                }
                printf("%llu\n", result);
            }
        } else {
            printf("Invalid command\n");
            return -1;
        }
    }
}
