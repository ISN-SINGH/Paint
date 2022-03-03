#include <stdlib.h>
#include <string.h>
#include "edit.h"

void Write(template* boardObj, LineD lineObj) {
  for (int i = 0; i <= (lineObj.row1 - lineObj.row2); i++) {
    for (int j = 0; j <= abs(lineObj.col1 - lineObj.col2); j++) {
      if (lineObj.dir_state == NONE) {
        char* charAtCell = &(boardObj->board[lineObj.row1].line[lineObj.col1]);
        if (*charAtCell == '*') {
          *charAtCell = '-';
        } else {
          *charAtCell = '+';
        }
      } else if (lineObj.dir_state == UP) {
        char* charAtCell = &(boardObj->board[lineObj.row1 - i].line[lineObj.col1]);
        if (*charAtCell == '*') {
          *charAtCell = '|';
        } else if (*charAtCell != '|') {
          *charAtCell = '+';
        }
      } else if (lineObj.dir_state == UP_L) {
        if (i == j) {
          char* charAtCell = &(boardObj->board[lineObj.row1 - i].line[lineObj.col1 + j]);
          if (*charAtCell == '*') {
            *charAtCell = '\\';
          } else if (*charAtCell != '\\') { // overlapping line found
            *charAtCell = '+';
          }
        }
      } else if (lineObj.dir_state == LEFT) {
        char* charAtCell = &(boardObj->board[lineObj.row1].line[lineObj.col1 - j]);
        if (*charAtCell == '*') {
          *charAtCell = '-';
        } else if (*charAtCell != '-') { // overlapping line found
          *charAtCell = '+';
        }
      } else if(lineObj.dir_state == UP_R) {
        if (i == j) {
          char* charAtCell = &(boardObj->board[lineObj.row1 - i].line[lineObj.col1 - j]);
          if (*charAtCell == '*') {
            *charAtCell = '/';
          } else if (*charAtCell != '/') { // overlapping line found
            *charAtCell = '+';
          }
        }
      }
    }
  }
}

LineD MakeLine(int row1, int col1, int row2, int col2) {
  LineD lineObj;
  if (row1 == row2 && col1 == col2) {
    lineObj.dir_state = NONE;
    lineObj.row1 = row1;
    lineObj.row2 = row2;
    lineObj.col1 = col1;
    lineObj.col2 = col2;
  } else if (col1 == col2) {
    lineObj.dir_state = UP;
    lineObj.col1 = col1;
    lineObj.col2 = col2;
    if (row1 < row2) {
      lineObj.row1 = row2;
      lineObj.row2 = row1;
    } else {
      lineObj.row1 = row1;
      lineObj.row2 = row2;
    }
  } else if (row1 == row2) {
    lineObj.dir_state = LEFT;
    lineObj.row1 = row1;
    lineObj.row2 = row2;
    if (col1 > col2) {
      lineObj.col1 = col1;
      lineObj.col2 = col2;
    } else {
      lineObj.col1 = col2;
      lineObj.col2 = col1;
    }
  } else if ((row1 > row2 && col1 > col2) || (row1 < row2 && col1 < col2)) {
    lineObj.dir_state = UP_R;
    if (row1 > row2) {
      lineObj.row1 = row1;
      lineObj.row2 = row2;
      lineObj.col1 = col1;
      lineObj.col2 = col2;
    } else {
      lineObj.row1 = row2;
      lineObj.row2 = row1;
      lineObj.col1 = col2;
      lineObj.col2 = col1;
    }
  } else { //UP_L, makes sure row must be decremented when writing
    lineObj.dir_state = UP_L;
    if (row1 > row2) {
      lineObj.row1 = row1;
      lineObj.row2 = row2;
      lineObj.col1 = col1;
      lineObj.col2 = col2;
    } else {
      lineObj.row1 = row2;
      lineObj.row2 = row1;
      lineObj.col1 = col2;
      lineObj.col2 = col1;
    }
  }
  return lineObj;
}

void Add(template* boardObj, char identifier, int position) {
  if (identifier == 'r') {
    if (position == boardObj->numRows + 1) {
      position--;
    }
    boardObj->board = (row*)realloc(boardObj->board, (boardObj->numRows+1) * sizeof(row)); // create new row
    boardObj->board[boardObj->numRows].line = (char*)malloc((boardObj->board[0].numCols + 1) * sizeof(char)); // create space for line
    boardObj->board[boardObj->numRows].numCols = boardObj->board[0].numCols; // set line length
    for (int i = boardObj->numRows - 1; i >= position; i--) { // row becomes what was above it
      strcpy(boardObj->board[i+1].line, boardObj->board[i].line); // copy line without copying pointer
    }
    for (int i = 0; i < boardObj->board[position].numCols; i++) { // clear added line
      boardObj->board[position].line[i] = '*';
    }
    boardObj->numRows = boardObj->numRows + 1;
  } else if (identifier == 'c') {
    for (int i = 0; i < boardObj->numRows; i++) {
      boardObj->board[i].numCols = boardObj->board[i].numCols + 1;
      boardObj->board[i].line = (char*)realloc(boardObj->board[i].line, (boardObj->board[i].numCols+1) * sizeof(char));
      for (int j = boardObj->board[i].numCols - 1; j >= position; j--) {
        boardObj->board[i].line[j+1] = boardObj->board[i].line[j];
      }
      boardObj->board[i].line[position] = '*';
    }
  }
}
