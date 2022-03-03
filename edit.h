#ifndef EDIT_H
  #define EDIT_H

  enum Direction{
    NONE,
    UP,
    UP_R,
    LEFT,
    UP_L
  };

  typedef struct LineD_struct {
    int row1;
    int col1;
    int row2;
    int col2;
    enum Direction dir_state;
  } LineD;

  #include "template.h"
  void Write(template* boardObj, LineD lineObj);
  LineD MakeLine(int row1, int col1, int row2, int col2);
  void Add(template* boardObj, char identifier, int position);
  void Erase(template* boardObj, int row, int col);
  void Delete(template* boardObj, char identifier, int position);

#endif
