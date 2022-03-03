#include <stdio.h>
#include <stdlib.h>
#include "fileuse.h"

void LoadTemplate(char* fileName, template* boardObj) { //broken
  char curr_char = '?';
  int numRows = 0;

  FILE* inFile = fopen(fileName, "r");
  if (inFile == NULL) {
    printf("Failed to open file: %s\n", fileName);
    return;
  }
  Quit(boardObj); // start with fresh template

  fscanf(inFile, "%c", &curr_char);
  while (!feof(inFile)) {
    int numCols = 0;
    numRows++;
    if (numRows == 1) {
      boardObj->board = (row*)malloc(numRows * sizeof(row));
    } else {
      boardObj->board = (row*)realloc(boardObj->board, numRows * sizeof(row));
    }
    while (curr_char != '\n') {
      numCols++;
      if (numCols == 1) {
        boardObj->board[numRows-1].line = (char*)malloc(numCols * sizeof(char));
      } else {
        boardObj->board[numRows-1].line = (char*)realloc(boardObj->board[numRows-1].line, numCols * sizeof(char));
      }
      boardObj->board[numRows-1].line[numCols-1] = curr_char;
      fscanf(inFile, "%c", &curr_char);
    }
    boardObj->board[numRows-1].numCols = numCols;
    boardObj->board[numRows-1].line = (char*)realloc(boardObj->board[numRows-1].line, (numCols+1) * sizeof(char)); // add null char
    boardObj->board[numRows-1].line[numCols] = '\0';
    fscanf(inFile, "%c", &curr_char); // catches EOF
  }
  boardObj->numRows = numRows;
  fclose(inFile);
}

/* Prints template upside down into file
*  Row[0] which is normally at bottom of template is printed at top
*  Implemented this way so that loading starts at row[0] at top of file */
void SaveTemplate(char* fileName, template* boardObj) {
  FILE* outFile = fopen(fileName, "w");
  if (outFile == NULL) {
    printf("Improper save command or file could not be created.\n");
    return;
  }
  for (int i = 0; i < boardObj->numRows; i++) {
    for (int j = 0; j < boardObj->board[0].numCols; j++) {
      fprintf(outFile, "%c", boardObj->board[i].line[j]); // space between elements not needed
    }
    fprintf(outFile, "\n");
  }
  fclose(outFile);
}
