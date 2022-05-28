#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Structures.h"
#include "Prototypes.h"
#define START_SIZE 1
#define MALLOC 1
#define REALLOC 2
#define DEFAULT_LINE 50
#define FIRST_NAME 21
#define DEFAULT_BUFFER 150
#define DEFAULT_FULL_NAME 3
#define NAME 0
#define INSTRUMENT 1
#define PRICE 2
#define INSTRUMENTSFILE "Instruments.txt"
#define MUSICIANSFILE "Musicians.txt"
#define DAY 1
#define MONTH 1
#define YEAR 2
#define HOUR 60
#define FAIL -1
#define SUCCEED 1
#define IS ==
#define RESULT(y) y > 0 ? SUCCEED : FAIL
#define PRINT(last,first) (last > 10 && first > 10) ? printf("%d:%d: ", first, last) : (last > 10 && first < 10) ? printf("0%d:%d: ", first, last) : (last < 10 && first > 10) ? printf("%d:0%d: ", first, last) : printf("0%d:0%d: ", first, last)
#define PRINTDATE(x)(x > 10) ? printf("%d ", x) : printf("0%d ", x);
#define CONDITION(x,y,z,w) (x==y) ?  printf("- %s (%d). ",z,w) : printf("- %s (%d), ",z,w)