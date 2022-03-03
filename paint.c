#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "input.h"
#include "edit.h"
#include "paint.h"
#include "fileuse.h"

void Paint(template* boardObj) {
  char command = '?';
  char* userInput;
  char* fileName;
  bool executeQuit = false;

  do {
    PrintTemplate(*boardObj);
    userInput = GetCommand();
    sscanf(userInput, " %c", &command);

    if (command == 'h') {
      int argsScanned;
      char shouldBeNewline;
      argsScanned = sscanf(userInput, " %c %c", &command, &shouldBeNewline);
      if (argsScanned != 2 || shouldBeNewline != '~') {
        printf("Unrecognized command. Type h for help.\n");
      } else {
        print_help();
      }
    } else if (command == 'w') {
      int row1, row2, col1, col2;
      char shouldBeNewline;
      int argsScanned;
      argsScanned = sscanf(userInput, " %c %d %d %d %d %c", &command, &row1, &col1, &row2, &col2, &shouldBeNewline);

      if (argsScanned != 6 || !WithinBoundary(*boardObj, row1, col1) || !WithinBoundary(*boardObj, row2, col2) || shouldBeNewline != '~') {
        printf("Improper draw command.\n");
      } else if (abs(row1 - row2) - abs(col1 - col2) != 0 && abs(row1 - row2) != 0 && abs(col1 - col2) != 0) {
        printf("Cannot draw the line as it is not straight.\n");
      } else {
        LineD lineObj = MakeLine(row1, col1, row2, col2);
        Write(boardObj, lineObj);
      }
    } else if (command == 'e') {
      int row, col;
      char shouldBeNewline;
      int argsScanned;
      argsScanned = sscanf(userInput, " %c %d %d %c", &command, &row, &col, &shouldBeNewline);

      if (argsScanned != 4 || !WithinBoundary(*boardObj, row, col) || shouldBeNewline != '~') {
        printf("Improper erase command.\n");
      } else {
        Erase(boardObj, row, col);
      }
    } else if (command == 'r') {
      int numRows, numCols;
      int argsScanned;
      char shouldBeNewline;
      argsScanned = sscanf(userInput, " %c %d %d %c", &command, &numRows, &numCols, &shouldBeNewline);

      if (argsScanned != 4 || numRows < 1 || numCols < 1 || shouldBeNewline != '~') {
        printf("Improper resize command.\n");
      } else {
        Resize(boardObj, numRows, numCols);
      }
    } else if (command == 'a') {
      char identifier;
      int position, argsScanned;
      char shouldBeNewline;
      argsScanned = sscanf(userInput, " %c %c %d %c", &command, &identifier, &position, &shouldBeNewline);

      if (argsScanned != 4 || (identifier == 'r' && (position < 0 || position > boardObj->numRows)) ||
      (identifier == 'c' && (position < 0 || position > boardObj->board[0].numCols)) || !(identifier == 'r' || identifier == 'c') ||
      shouldBeNewline != '~') {
        printf("Improper add command.\n");
      } else {
        Add(boardObj, identifier, position);
      }
    } else if (command == 'd') {
      char identifier;
      int position, argsScanned;
      char shouldBeNewline;
      argsScanned = sscanf(userInput, " %c %c %d %c", &command, &identifier, &position, &shouldBeNewline);

      if (argsScanned != 4 || (identifier == 'r' && (position < 0 || position >= boardObj->numRows)) ||
      (identifier == 'c' && (position < 0 || position >= boardObj->board[0].numCols)) || !(identifier == 'r' || identifier == 'c') ||
      shouldBeNewline != '~') {
        printf("Improper delete command.\n");
      } else {
        Delete(boardObj, identifier, position);
      }
    } else if (command == 's') {
      fileName = GetFileName(userInput);

      if (fileName == NULL) {
        free(fileName);
        printf("Improper save command or file could not be created.\n");
      } else {
        SaveTemplate(fileName, boardObj);
        free(fileName);
      }
    } else if (command == 'l') {
      fileName = GetFileName(userInput); // also makes sure input is valid
      if (fileName == NULL) {
        free(fileName);
        printf("Improper load command or file could not be opened.\n");
      } else {
        LoadTemplate(fileName, boardObj);
        free(fileName);
      }
    } else if (command != 'q') {
      printf("Unrecognized command. Type h for help.\n");
    } else {
      int argsScanned;
      char shouldBeNewline;
      argsScanned = sscanf(userInput, " %c %c", &command, &shouldBeNewline);
      if (argsScanned != 2 || shouldBeNewline != '~') {
        printf("Unrecognized command. Type h for help.\n");
      } else {
        executeQuit = true;
      }
    }
  } while(command != 'q' || !executeQuit);
  free(userInput);
  Quit(boardObj);
}

void print_help() {
  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

bool WithinBoundary(template boardObj, int row_coord, int col_coord) {
  return boardObj.numRows > row_coord && boardObj.board[0].numCols > col_coord && !(row_coord < 0) && !(col_coord < 0);
}
