#ifndef PAINT_H
  #define PAINT_H

  #include <stdbool.h>
  #include "template.h"
  void Paint(template* boardObj);
  void print_help();
  bool WithinBoundary(template boardObj, int row_coord, int col_coord);

#endif
