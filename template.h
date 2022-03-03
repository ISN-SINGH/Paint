#ifndef TEMPLATE_H
  #define TEMPLATE_H

  typedef struct row_struct {
    int numCols;
    char* line;
  } row;

  typedef struct template_struct {
    int numRows;
    row* board;
  } template;

  void CreateTemplate(template* boardObj, int colSize);
  void PrintTemplate(template boardObj);
  void Quit(template* boardObj);
  void Resize(template* boardObj, int rowSize, int colSize);

#endif
