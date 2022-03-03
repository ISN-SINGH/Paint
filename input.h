#ifndef INPUT_H
  #define INPUT_H

  void CommandLineArgValidation(int argc, char *argv[], int* rowSize, int* colSize);
  char* GetFileName(char* userInput);
  char* GetCommand();
  int IsNum(char* str);

#endif
