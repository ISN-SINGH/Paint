#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"

void CommandLineArgValidation(int argc, char *argv[], int* rowSize, int* colSize) {
  if (argc == 1) {
    *rowSize = 10;
    *colSize = 10;
  } else if (argc == 3) {
    int rowIsNum = IsNum(argv[1]);
    int colIsNum = IsNum(argv[2]);
    if(rowIsNum != 0) {
      *rowSize = 10;
      if (rowIsNum == 1 || rowIsNum == 4) { // negative number
        printf("The number of rows is less than 1.\n");
      }
      if (rowIsNum == 2 || rowIsNum == 4) { // decimal number
        printf("The number of rows is not an integer.\n");
      }
      if (rowIsNum == 3) {
        printf("The number of rows is not an integer.\n");
      }
      *colSize = 10;
      printf("Making default board of 10 X 10.\n");
      return;
    } else {
      int temp = atoi(argv[1]);
      if (temp == 0) {
        printf("The number of rows is less than 1.\n");
        *rowSize = 10;
        *colSize = 10;
        printf("Making default board of 10 X 10.\n");
        return;
      } else {
        *rowSize = temp;
      }
    }

    if(colIsNum != 0) {
      *colSize = 10; // if not number no print statement
      if (colIsNum == 1 || colIsNum == 4) { // negative number
        printf("The number of columns is less than 1.\n");
      }
      if (colIsNum == 2 || colIsNum == 4) { // decimal number
        printf("The number of columns is not an integer.\n");
      }
      if (colIsNum == 3) {
        printf("The number of columns is not an integer.\n");
      }
      *rowSize = 10;
      printf("Making default board of 10 X 10.\n");
      return;
    } else {
      int temp = atoi(argv[2]);
      if (temp == 0) {
        printf("The number of columns is less than 1.\n");
        *colSize = 10;
        *rowSize = 10;
        printf("Making default board of 10 X 10.\n");
        return;
      } else {
        *colSize = temp;
      }
    }
  } else {
    printf("Wrong number of command line arguements entered.\n");
    printf("Usage: ./paint.out [num_rows num_cols]\n");
    printf("Making default board of 10 X 10.\n");
    *rowSize = 10;
    *colSize = 10;
  }
}

// Grab fileName from user input without command and without spaces before/after
char* GetFileName(char* userInput) {
  char* fileName;
  unsigned int indexOfCommand;
  unsigned int indexOfFileName;
  unsigned int indexOfSpace;

  for (indexOfCommand = 0; userInput[indexOfCommand] != '\0'; indexOfCommand++) { // find command
    unsigned char u_indexOfCommand = userInput[indexOfCommand];
    if (!isspace(u_indexOfCommand)) {
      break;
    }
  }
  unsigned char u_indexOfCommand1 = userInput[indexOfCommand+1];
  if (!isspace(u_indexOfCommand1)) { // invalid input
    return NULL;
  }

  fileName = (char*)malloc((strlen(userInput) - indexOfCommand) * sizeof(char)); // don't need (indexOfCommand+1) because need space for \0
  bool fileNameFound = false;
  indexOfCommand++;
  indexOfFileName = indexOfCommand; // starts at space after command
  for (; userInput[indexOfCommand] != '\0'; indexOfCommand++) { // put contents of userInput into fileName without command
    unsigned char u_indexOfCommand = userInput[indexOfCommand];
    if (fileNameFound == false && !isspace(u_indexOfCommand)) {
      fileNameFound = true;
      indexOfFileName = indexOfCommand;
      fileName = (char*)realloc(fileName, (strlen(userInput) - indexOfFileName) * sizeof(char));
      fileName[0] = userInput[indexOfFileName];
    } else if (fileNameFound == true) {
      fileName[indexOfCommand-indexOfFileName] = userInput[indexOfCommand];
    }
  } // fileName now starts with file name but ends with unknown chars
  unsigned char u_indexOfCommand = userInput[indexOfCommand];
  fileName[indexOfCommand-indexOfFileName] = u_indexOfCommand; // put in \0

  for (indexOfSpace = 0; fileName[indexOfSpace] != '\0'; indexOfSpace++) { // found space after fileName
    unsigned char u_indexOfSpace = fileName[indexOfSpace];
    if (isspace(u_indexOfSpace)) {
      break;
    }
  }
  for (int i = indexOfSpace; fileName[i] != '\0'; i++) {
    unsigned char u_index = fileName[i];
    if (!isspace(u_index) && u_index != '~') {
      free(fileName);
      return NULL;
    }
  }
  fileName = (char*)realloc(fileName, (indexOfSpace+1) * sizeof(char));
  fileName[indexOfSpace] = '\0';
  return fileName;
}

char* GetCommand() {
  char* fullCommand = NULL;
  int size = 0;
  char shouldBeNewline;
  printf("Enter your command: ");
  do {
    size++;
    scanf("%c", &shouldBeNewline);
    fullCommand = (char*)realloc(fullCommand, size * sizeof(char));
    fullCommand[size - 1] = shouldBeNewline;
  } while(shouldBeNewline != '\n');
  fullCommand[size - 1] = ' ';
  fullCommand = (char*)realloc(fullCommand, (size+1) * sizeof(char));
  fullCommand[size] = '~'; // newline converted to make sure only whitespace chars after scan
  fullCommand = (char*)realloc(fullCommand, (size+2) * sizeof(char));
  fullCommand[size+1] = '\0';
  return fullCommand;
}

// Given command line argument, categorizes argument to be negative and/or decimal and/or non-numeric
int IsNum(char* str) {
  bool notNum = false;
  bool notNat = false;
  bool notPos = false;
  for (int i = 0; str[i] != '\0'; i++) {
    unsigned char u_currchar = str[i];
    if(!isdigit(u_currchar) && u_currchar != '-' && u_currchar != '.') {
      notNum = true;
      break;
    }
    if (str[i] == '.') {
      notNat = true;
    }
    if (str[i] == '-') {
      notPos = true;
    }
  }
  if (!notNum && !notNat && !notPos) { // 0: is natural number
    return 0;
  } else if (notNum) { // 3: is not number
    return 3;
  } else if (notNat && notPos) { // 4: negative decimal number
    return 4;
  } else if (notNat) { // 2: decimal number
    return 2;
  } else { // 1: negative number
    return 1;
  }
}
