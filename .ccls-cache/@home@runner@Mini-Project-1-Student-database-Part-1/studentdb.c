#include <stdio.h>
#include <string.h>
#include "studentdb.h"
#include "studentdb.h"

student studentList[20]; // Gloabal array is not good to use. We use it here so that we don't pass it all the function calls. This issue will be resolved when we use pointers and linked lists in the part 2 of this project.

void addTestData() {
  for (int i = 0; i < TEST_DATA_NUM; i++) {
    strcpy(studentList[i].personalNumber, "12345");
  }
}

void displayHelp() {
    printf("- `help`, shows the list of commands and what they do.\n");
    printf("- `add`, will add a new Student. Please see how the Student structure should look like in below\n");
    printf("- `show`, shows a list of all the Students\n");
    printf("- `showasc`, show list of all Students sorted in ascending order.\n");
    printf("- `showdesc`, show list of all Students sorted in descending order.\n");
    printf("- `search`, searches the list of Students by first name.\n");
    printf("- `count`, shows the number of valid students in the database.\n");
    printf("- `exit`, to exit\n\n");
}

_Bool isPersonalNumberValid(char personalNumber[10]) {
    _Bool success = TRUE;
    //check if personalNumber exists in the studentList
    
    return success;
}

_Bool add(student newStudent) {
    _Bool success = FALSE;
    //Adds a new student to the studentListArray, this function will check if the personal number already exists, it it does, it returns FALSE.
    studentList[0].valid = FALSE;
    
    return success;
}

int count() {
    int noOfStudents = 0;
    //Counts the nuber of students, in other words, it will count how many valid entries are in the studentList
    //count number of valid entries
    return noOfStudents;
}

