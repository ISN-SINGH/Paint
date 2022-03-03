#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "template.h"
#include "input.h"
#include "paint.h"

int main(int argc, char *argv[]) {
  int rowSize, colSize;
  template boardObj;
  CommandLineArgValidation(argc, argv, &rowSize, &colSize);
  boardObj.numRows = rowSize;
  CreateTemplate(&boardObj, colSize);
  Paint(&boardObj);
  return 0;
}
















void Erase(template* boardObj, int row, int col) {
  boardObj->board[row].line[col] = '*';
}



void Delete(template* boardObj, char identifier, int position) {
  if (identifier == 'r') {
    for (int i = position; i < boardObj->numRows - 1; i++) {
      boardObj->board[i] = boardObj->board[i+1];
    }
    boardObj->numRows = boardObj->numRows - 1;
    boardObj->board = (row*)realloc(boardObj->board, boardObj->numRows * sizeof(row));
  } else {
    for (int i = 0; i < boardObj->numRows; i++) {
      for (int j = position; j < boardObj->board[0].numCols; j++) { // dont need numCols - 1 so we also get null char at end
        boardObj->board[i].line[j] = boardObj->board[i].line[j+1];
      }
      boardObj->board[i].numCols = boardObj->board[i].numCols - 1;
      boardObj->board[i].line = (char*)realloc(boardObj->board[i].line, (boardObj->board[i].numCols+1) * sizeof(char));
    }
  }
}
