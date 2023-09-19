#ifndef _INC_STUDENT_DB
#define _INC_STUDENT_DB
#define MAX_CHAR_FNAME 32
#define MAX_CHAR_LNAME 64
#define TEST_DATA_NUM 5
#include "stdbool.h"

#define FALSE 0
#define TRUE 1

struct student {
  char personalNumber[11]; //The last character in a string must be '\0', YYMMDD1234
  _Bool valid;
};

typedef struct student student;

void displayHelp();

_Bool isPersonalNumberValid(char personalNumber[10]);

_Bool add(student newStudent);

int count();

void addTestData();

#endif