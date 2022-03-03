#include <stdio.h>
#include <stdlib.h>
#include "template.h"

void CreateTemplate(template* boardObj, int colSize) {
  boardObj->board = (row*)malloc(boardObj->numRows * sizeof(row));

  for (int i = 0; i < boardObj->numRows; i++) {
    row rowObj;
    rowObj.numCols = colSize;
    rowObj.line = (char*)malloc((rowObj.numCols+1) * sizeof(char));
    // set all cells to default value * and set null character
    for (int i = 0; i < rowObj.numCols; i++) {
      rowObj.line[i] = '*';
    }
    rowObj.line[rowObj.numCols] = '\0';

    boardObj->board[i] = rowObj;
  }
}

void PrintTemplate(template boardObj) {
  for (int i = boardObj.numRows; i > 0; i--) {
    printf("%d ", i-1);
    for (int j = 0; j < boardObj.board[i-1].numCols; j++) {
      printf("%c ", boardObj.board[i-1].line[j]);
    }
    printf("\n");
  }
  printf("  ");
  for (int i = 0; i < boardObj.board[0].numCols; i++) {
    printf("%d ", i);
  }
  printf("\n");
}

void Quit(template* boardObj) {
  for (int i = 0; i < boardObj->numRows; i++) {
    free(boardObj->board[i].line);
    boardObj->board[i].numCols = 0;
  }
  free(boardObj->board);
  boardObj->numRows = 0;
  boardObj->board = NULL;
}

void Resize(template* boardObj, int rowSize, int colSize) {
  int origRowSize = boardObj->numRows;
  int origColSize = boardObj->board[0].numCols;
  boardObj->numRows = rowSize;
  boardObj->board = (row*)realloc(boardObj->board, boardObj->numRows * sizeof(row));
  for (int i = 0; i < boardObj->numRows; i++) {
    boardObj->board[i].numCols = colSize;
    boardObj->board[i].line = (char*)realloc(boardObj->board[i].line, (colSize+1) * sizeof(char));
    boardObj->board[i].line[colSize] = '\0';
  }
  for (int i = origRowSize; i < boardObj->numRows; i++) {
    for (int j = 0; j < boardObj->board[i].numCols; j++) {
      boardObj->board[i].line[j] = '*';
    }
  }
  for (int i = 0; i < boardObj->numRows; i++) {
    for (int j = origColSize; j < boardObj->board[i].numCols; j++) {
      boardObj->board[i].line[j] = '*';
    }
    boardObj->board[i].line[colSize] = '\0';
  }
}
